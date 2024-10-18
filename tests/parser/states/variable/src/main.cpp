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

#include "parser/exceptions/unexpectedendoffileexception.hpp"
#include "parser/exceptions/unexpectedtokenexception.hpp"
#include "parser/parser.hpp"
#include "parser/states/variable.hpp"
#include "parser/tokens/separator.hpp"
#include "parser/tokens/word.hpp"

#include "aux/handlers/dummyhandler.hpp"
#include "fakes/lexer/lexer.hpp"

namespace fs = std::filesystem;

/**
 * @brief A text fixture to test parser::states::types::Variable component
 * 
 */
class VariableTest : public ::testing::Test
{
protected:
	using Token = parser::tokens::Token;
	using Separator = parser::tokens::Separator;
	using Word = parser::tokens::Word;

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
	parser::states::Variable instance_{mediator_};
};

const fs::path VariableTest::kFilePath{""};

/**
 * @brief Check if the Process() method handles correctly defined variables
 * 
 */
TEST_F(VariableTest, TestProcess)
{
	mediator_.DeclareVariable("A", "B");

	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Word>("A"));
	tokens.emplace_back(std::make_unique<Separator>(Separator::Type::kSpace));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_EQ(instance_.GetValue(), "B");
}

/**
 * @brief Check if the Process() method correctly throws an eception if the EOF symbol is encountered
 * 
 */
TEST_F(VariableTest, TestProcessEOF)
{
	std::vector<std::unique_ptr<Token>> tokens{};

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedEndOfFileException);
}