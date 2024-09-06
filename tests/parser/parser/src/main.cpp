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

#include <chrono>
#include <filesystem>
#include <future>

#include "fakes/parser/parser.hpp"

namespace fs = std::filesystem;

/**
 * @brief A text fixture to test parser::Parser component
 * 
 */
class ParserTest : public ::testing::Test
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
	fakes::parser::Parser instance_{kFilePath};
};

const fs::path ParserTest::kFilePath{""};

/**
 * @brief Check if the SetState() method actually changes the state of the parser
 * 
 */
TEST_F(ParserTest, TestSetState)
{
	EXPECT_TRUE(instance_.state_);
	instance_.SetState({});
	EXPECT_FALSE(instance_.state_);
}

/**
 * @brief Check if the nullptr state make the parser end file processing job
 * 
 * @note It is very important to use stubs of the Statement component for this
 *       test, because it doesn't switch the parser to any other states.
 */
TEST_F(ParserTest, TestProcess)
{
	// Run the processing method
	const auto handle = std::async(std::launch::async, [&] { instance_.Process(); });

	// Make the state switch to "nullptr"
	instance_.SetState({});

	// Expect the processing to be stopped
	const auto status = handle.wait_for(std::chrono::seconds(1));
	EXPECT_EQ(status, std::future_status::ready);
}