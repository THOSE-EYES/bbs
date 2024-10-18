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
#include "parser/states/types/string.hpp"
#include "parser/tokens/operator.hpp"
#include "parser/tokens/word.hpp"

#include "aux/handlers/dummyhandler.hpp"
#include "fakes/lexer/lexer.hpp"

namespace fs = std::filesystem;

/**
 * @brief A text fixture to test parser::states::types::String component
 * 
 */
class StringTest : public ::testing::Test
{
protected:
	using Operator = parser::tokens::Operator;
	using Punctuator = parser::tokens::Punctuator;
	using Token = parser::tokens::Token;
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
	parser::states::types::String instance_{mediator_};
};

const fs::path StringTest::kFilePath{""};

/**
 * @brief Check if the Process() method correctly handles abscence of the leading quote mark
 * 
 */
TEST_F(StringTest, TestProcessLeadingQuoteMarkAbscence)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Word>("A"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedTokenException);
}

/**
 * @brief Check if the Process() method correctly handles abscence of the closing quote mark
 * 
 */
TEST_F(StringTest, TestProcessClosingQuoteMarkAbscence)
{
	std::vector<std::unique_ptr<Token>> tokens;
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Word>("A"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedTokenException);
}

/**
 * @brief Check if the Process() method correctly handles qoute marks-wrapped strings
 * 
 */
TEST_F(StringTest, TestProcess)
{
	std::vector<std::unique_ptr<Token>> tokens;
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Word>("A"));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_EQ(instance_.GetValue(), "A");
}

/**
 * @brief Check if the Process() method correctly handles qoute marks-wrapped strings with variables
 * 
 */
TEST_F(StringTest, TestProcessVariable)
{
	mediator_.DeclareVariable("A", "B");

	std::vector<std::unique_ptr<Token>> tokens;
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));
	tokens.emplace_back(std::make_unique<Word>("A"));
	tokens.emplace_back(std::make_unique<Operator>(Operator::Type::kDollarSign));
	tokens.emplace_back(std::make_unique<Word>("A"));
	tokens.emplace_back(std::make_unique<Punctuator>(Punctuator::Type::kDoubleQuoteMark));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_EQ(instance_.GetValue(), "AB");
}