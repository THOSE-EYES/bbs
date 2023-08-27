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

#include <gtest/gtest.h>

#include "fakes/utils/bufferedlogger.hpp"

/**
 * @brief Test fixture class for the BufferedLogger component testing
 * 
 */
class BufferedLoggerTest : public ::testing::Test
{
protected:
	fakes::utils::BufferedLogger object_{""};
};

/**
 * @fn BufferedLoggerTestStandalone.TestConstructor
 * @brief Check if the constructor works correctly and sets the name of the component
 * 
 */
TEST(BufferedLoggerTestStandalone, TestConstructor)
{
	const std::string name{"Test"};
	auto object = fakes::utils::BufferedLogger{name};

	EXPECT_EQ(object.component_name_, name);
}

/**
 * @fn BufferedLoggerTestStandalone.TestGetInstance
 * @brief Check if the GetInstance() method works OK
 * 
 */
TEST(BufferedLoggerTestStandalone, TestGetInstance)
{
	const std::string name{"Test"};
	EXPECT_NO_THROW(fakes::utils::BufferedLogger::GetInstance(name));
}

/**
 * @fn BufferedLoggerTest.TestSetBufferLogLevel
 * @brief Check if the method SetBufferLogLevel() sets the buffer's log level
 * 
 */
TEST_F(BufferedLoggerTest, TestSetBufferLogLevel)
{
	const auto level{fakes::utils::BufferedLogger::LogLevel::kInfo};
	object_.SetBufferLogLevel(level);

	EXPECT_EQ(object_.buffer_log_level_, level);
}

/**
 * @fn BufferedLoggerTest.TestAppend
 * @brief Check if the Append() method adds the message to the buffer
 * 
 */
TEST_F(BufferedLoggerTest, TestAppend)
{
	const std::string message{"Hello world!"};
	object_.Append(message);

	EXPECT_EQ(object_.buffer_, message);
}

/**
 * @fn BufferedLoggerTest.TestFlush
 * @brief Check if the Flush() operation clears the buffer and the log level after passing it to the file
 * 
 */
TEST_F(BufferedLoggerTest, TestFlush)
{
	// Set the log level to non-default
	const auto level{fakes::utils::BufferedLogger::LogLevel::kDebug};
	object_.SetBufferLogLevel(level);

	// Add something to the buffer
	const std::string message{"Hello world!"};
	object_.Append(message);

	// Call the method under testing
	object_.Flush();

	EXPECT_EQ(object_.buffer_log_level_, fakes::utils::BufferedLogger::LogLevel::kInfo);
	EXPECT_TRUE(object_.buffer_.empty());
}

/**
 * @fn BufferedLoggerTest.TestStreamOperatorLogLevel
 * @brief Check if the stream operation updates the log level of the message, stored in the buffer
 * 
 */
TEST_F(BufferedLoggerTest, TestStreamOperatorLogLevel)
{
	const auto level{fakes::utils::BufferedLogger::LogLevel::kDebug};
	object_ << level;

	EXPECT_EQ(object_.buffer_log_level_, level);
}

/**
 * @fn BufferedLoggerTest.TestStreamOperatorString
 * @brief Check if the stream operation updates the buffer
 * 
 */
TEST_F(BufferedLoggerTest, TestStreamOperatorString)
{
	const std::string message{"Hello world!"};
	object_ << message;

	EXPECT_EQ(object_.buffer_, message);
}

/**
 * @fn BufferedLoggerTest.TestStreamOperatorInteger
 * @brief Check if the stream operation converts the integer to a valid string and updates the buffer
 * 
 */
TEST_F(BufferedLoggerTest, TestStreamOperatorInteger)
{
	const int integer{5};
	object_ << integer;

	EXPECT_EQ(object_.buffer_, std::to_string(integer));
}

/**
 * @fn BufferedLoggerTest.TestStreamOperatorFunctionEnd
 * @brief Check if the stream operation calls the supplied End() function
 * 
 */
TEST_F(BufferedLoggerTest, TestStreamOperatorFunctionEnd)
{
	const auto level{fakes::utils::BufferedLogger::LogLevel::kDebug};
	const std::string message{"Hello world!"};
	object_ << level << message << utils::End;

	// Check if the End() flushes the buffer
	EXPECT_EQ(object_.buffer_log_level_, fakes::utils::BufferedLogger::LogLevel::kInfo);
	EXPECT_TRUE(object_.buffer_.empty());
}