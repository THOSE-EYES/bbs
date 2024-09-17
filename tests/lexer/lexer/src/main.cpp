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

#include "fakes/lexer/lexer.hpp"
#include "mocks/lexer/handlers/handler.hpp"

namespace fs = std::filesystem;

class LexerTest : public ::testing::Test
{
protected:
	/**
	 * @brief The default file path, used by the test suite
	 * 
	 */
	static const fs::path kFilePath;

	/**
	 * @brief The instance to test
	 * 
	 */
	::fakes::lexer::Lexer instance_{kFilePath};
};

const fs::path LexerTest::kFilePath{"build.bbs"};

/**
 * @brief Check if the lexer is calling Process() properly
 * 
 */
TEST_F(LexerTest, TestNext)
{
	using ::testing::_;

	// Create a mock to check if the next handler is called
	const auto mock = new mocks::lexer::handlers::Handler();
	instance_.handler_ = std::unique_ptr<::lexer::handlers::Handler>(mock);

	// Expect the mock to be called
	EXPECT_NO_THROW(instance_.Next());
	EXPECT_CALL(*mock, Process(_));

	// Allow leak since the pointer will be deleted by the unique_ptr wrapper
	testing::Mock::AllowLeak(mock);
}