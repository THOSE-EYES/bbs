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

#include <filesystem>

#include <gtest/gtest.h>

#include "lexer/handlers/wordhandler.hpp"

#include "mocks/lexer/handlers/handler.hpp"

namespace fs = std::filesystem;
namespace lex = ::lexer;

/**
 * @brief Test fixture class for the WordHandlerTest component testing
 * 
 */
class WordHandlerTest : public ::testing::Test
{
protected:
	/**
	 * @brief Set up the test fixture
	 * 
	 */
	void SetUp() override
	{
		if(fs::exists(kFilePath) && !fs::is_regular_file(kFilePath))
		{
			FAIL() << "The node " << kFilePath << " is not a regular file.";
		}

		file.open(kFilePath, std::ofstream::trunc);
		if(!file.is_open())
		{
			FAIL() << "Couldn't open the file " << kFilePath << ".";
		}
	}

	/**
	 * @brief Tear down the test fixture
	 * 
	 */
	void TearDown() override
	{
		file.close();
	}

protected:
	/**
	 * @brief The default file path, used by the test suite
	 * 
	 */
	static const fs::path kFilePath;

	/**
	 * @brief The test file handle
	 * 
	 */
	std::ofstream file;

	/**
	 * @brief The instance to test
	 * 
	 */
	lex::handlers::WordHandler instance_;
};

const fs::path WordHandlerTest::kFilePath{"build.bbs"};

/**
 * @brief Check if the end of the file is handled properly by the handler
 * 
 */
TEST_F(WordHandlerTest, TestProcessNullopt)
{
	using ::testing::_;

	// Create a mock to check if the next handler is called
	const auto mock = new mocks::lexer::handlers::Handler();
	instance_.SetNext(std::unique_ptr<lex::handlers::Handler>(mock));

	// Expect the mock to be called
	lex::Scanner scanner{kFilePath};
	EXPECT_NO_THROW(instance_.Process(scanner));
	EXPECT_CALL(*mock, Process(_));

	// Allow leak since the pointer will be deleted by the unique_ptr wrapper
	testing::Mock::AllowLeak(mock);
}

/**
 * @brief Check if the valid character triggers a call to the next handler's Process() function
 * 
 */
TEST_F(WordHandlerTest, TestProcess)
{
	const std::string data{"Hello"};

	// Add some valid text to the file plus non-alphabetical symbol
	file << data << '0' << std::endl;

	// Check every punctuator from the map
	lex::Scanner scanner{kFilePath};
	EXPECT_EQ(instance_.Process(scanner)->GetValue(), data);
}