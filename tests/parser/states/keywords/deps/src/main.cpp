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

#include <filesystem>

#include "lexer/lexer.hpp"
#include "parser/mediator.hpp"
#include "parser/states/keywords/deps.hpp"

namespace fs = std::filesystem;

/**
 * @brief A text fixture to test parser::states::keywords::Deps component
 * 
 */
class DepsTest : public ::testing::Test
{
protected:
	/**
	 * @brief The default file path, used by the test suite
	 * 
	 */
	static const fs::path kFilePath;

	/**
	 * @brief A mediator instance
	 * 
	 */
	parser::Mediator mediator_;

	/**
	 * @brief The instance to test
	 * 
	 */
	parser::states::keywords::Deps instance_{mediator_};
};

const fs::path DepsTest::kFilePath{""};

/**
 * @brief Check if the Process() method correctly handles abscence of the leading bracket
 * 
 */
TEST_F(DepsTest, TestProcess)
{
	lexer::Lexer lexer{kFilePath};
	EXPECT_NO_THROW(instance_.Process(lexer));
}
