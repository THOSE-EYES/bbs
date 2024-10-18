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

#include "parser/exceptions/unexpectedtokenexception.hpp"
#include "parser/parser.hpp"
#include "parser/states/types/array.hpp"
#include "parser/tokens/word.hpp"

#include "aux/handlers/dummyhandler.hpp"
#include "fakes/lexer/lexer.hpp"

namespace fs = std::filesystem;

/**
 * @brief The default file path, used by the test suite
 * 
 */
const fs::path kFilePath{""};

/**
 * @brief A text fixture to test parser::states::types::String component
 * 
 */
class ArrayTest : public ::testing::Test
{
protected:
	using Word = parser::tokens::Word;

protected:
	/**
	 * @brief An instance of parser
	 * 
	 */
	parser::Parser parser_{kFilePath};

	/**
	 * @brief An instance of mediator
	 * 
	 */
	parser::Mediator mediator_;

	/**
	 * @brief The instance to test
	 * 
	 */
	parser::states::types::Array instance_{mediator_};
};

/**
 * @brief Check if the Process() method correctly handles abscence of the leading bracket
 * 
 */
TEST_F(ArrayTest, TestProcessLeadingBracketAbscence)
{
	using Token = parser::tokens::Token;

	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Word>("A"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedTokenException);
}

/**
 * @brief Check if the Process() method correctly handles abscence of the closing bracket
 * 
 */
TEST_F(ArrayTest, TestProcessClosingBracketAbscence)
{
	using Token = parser::tokens::Token;
	using Punctuator = parser::tokens::Punctuator;

	std::vector<std::unique_ptr<Token>> tokens;
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kLeftSquareBracket));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Word>("A"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedTokenException);
}

/**
 * @brief Check if the Process() method correctly handles abscence of comma between strings
 * 
 */
TEST_F(ArrayTest, TestProcessCommaAbscence)
{
	using Token = parser::tokens::Token;
	using Punctuator = parser::tokens::Punctuator;

	std::vector<std::unique_ptr<Token>> tokens;
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kLeftSquareBracket));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Word>("A"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedTokenException);
}

/**
 * @brief Check if the Process() method correctly processes correctly formed array
 * 
 */
TEST_F(ArrayTest, TestProcess)
{
	using Token = parser::tokens::Token;
	using Punctuator = parser::tokens::Punctuator;

	std::vector<std::unique_ptr<Token>> tokens;
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kLeftSquareBracket));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kRightSquareBracket));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_EQ(instance_.GetValue().size(), 1);
}