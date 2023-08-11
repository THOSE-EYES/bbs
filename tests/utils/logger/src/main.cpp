/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <cstdio>

#include <gtest/gtest.h>

#include "fakes/utils/logger.hpp"

/**
 * @brief Test fixture class for the Logger component testing (only for the functions that deal with the file stream 
 * 		  itself).
 * 
 */
class LoggerTestWithFile : public ::testing::Test
{
protected:
	void SetUp() override
	{
		// Create a file and check if it was really created
		std::ofstream stream(filename_);
		if(!stream.is_open())
		{
			FAIL() << "File was not opened, so the test can't be run.";
		}

		// Close the stream
		stream.close();

		// Supply the logger with the newly created file
		fakes::utils::Logger::SetFile(filename_);
		EXPECT_TRUE(fakes::utils::Logger::stream_.is_open());
	}

	void TearDown() override
	{
		// Make the logger close it's stream before deleting the file
		fakes::utils::Logger::Close();

		// Remove the file as it won't be needed anymore
		std::remove(filename_.c_str());
	}

protected:
	const std::string filename_{"file.txt"};
	fakes::utils::Logger object_{"test"};
};

/**
 * @fn LoggerTest.TestSetFileNegative
 * @brief Check if the file setter works as expected when the specified file is not correct
 * 
 */
TEST(LoggerTest, TestSetFileNegative)
{
	fakes::utils::Logger::SetFile("");
	EXPECT_FALSE(fakes::utils::Logger::stream_.is_open());
}

/**
 * @fn LoggerTestWithFile.TestSetFilePositiveOpenedFile
 * @brief Check if the logger correctly reacts on reopening the file
 * 
 */
TEST_F(LoggerTestWithFile, TestSetFilePositiveOpenedFile)
{
	// Try to open the file again
	fakes::utils::Logger::SetFile(filename_);
	EXPECT_TRUE(fakes::utils::Logger::stream_.is_open());
}

/**
 * @fn LoggerTest.TestSetMinimumLogLevel
 * @brief Check if setting the minimum log level works correctly
 * 
 */
TEST(LoggerTest, TestSetMinimumLogLevel)
{
	const auto log_level = fakes::utils::Logger::LogLevel::kError;
	fakes::utils::Logger::SetMinimumLogLevel(log_level);

	EXPECT_EQ(fakes::utils::Logger::minimum_log_level_, log_level);
}

/**
 * @fn LoggerTestWithFile.TestLogNegativeLowLogLevel
 * @brief check if the logger rejects entries that have the level lower that minimum
 * 
 */
TEST_F(LoggerTestWithFile, TestLogNegativeLowLogLevel)
{
	// Set the instance
	const auto minimum_log_level = fakes::utils::Logger::LogLevel::kError;
	fakes::utils::Logger::SetMinimumLogLevel(minimum_log_level);

	// Expect the file to be empty
	const auto log_level = fakes::utils::Logger::LogLevel::kDebug;
	const std::string message{"Hello world!"};
	object_.Log(log_level, message);

	// Check if the log level of the entry is lover that the minimum one
	EXPECT_LT(log_level, fakes::utils::Logger::minimum_log_level_);

	// Open a checker stream to read the log file
	std::ifstream checker(filename_);
	if(!checker.is_open())
	{
		FAIL() << "File was not opened, can't verify if the log is there.";
	}

	// Check if the file is empty (as it should be)
	EXPECT_EQ(checker.peek(), std::ifstream::traits_type::eof());

	// Close the checker stream
	checker.close();
}

/**
 * @fn LoggerTest.TestLogNegativeInvalidStream
 * @brief Check if the logger operates correctly, when the stream is not OK
 * 
 */
TEST(LoggerTest, TestLogNegativeInvalidStream)
{
	// Expect the object to do not throw any exception about the invalid stream
	const auto log_level = fakes::utils::Logger::LogLevel::kError;
	const std::string message{"Hello world!"};
	fakes::utils::Logger object{"test"};

	EXPECT_FALSE(fakes::utils::Logger::stream_.is_open());
	EXPECT_NO_THROW(object.Log(log_level, message));
}

/**
 * @fn LoggerTestWithFile.TestLogPositive
 * @brief Check if the logger correctly logs entries under the defined conditions
 * 
 */
TEST_F(LoggerTestWithFile, TestLogPositive)
{
	const auto log_level = fakes::utils::Logger::LogLevel::kError;
	const std::string message{"Hello world!"};
	object_.Log(log_level, message);

	// Expect that the log level is appropriate
	EXPECT_GE(log_level, fakes::utils::Logger::minimum_log_level_);

	// Open an uinput stream to check if the log exists
	std::ifstream checker(filename_);
	if(!checker.is_open())
	{
		FAIL() << "File was not opened, can't verify if the log is there.";
	}

	// Verify that the log entry has the string we put there
	std::string log_entry;
	std::getline(checker, log_entry);
	EXPECT_TRUE(log_entry.find(message) != std::string::npos);

	// Close the checker stream
	checker.close();
}