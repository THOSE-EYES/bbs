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

#include "aux/handlers/dummyhandler.hpp"
#include "fakes/lexer/lexer.hpp"
#include "lexer/lexer.hpp"
#include "parser/exceptions/unexpectedtokenexception.hpp"
#include "parser/states/keywords/let.hpp"
#include "parser/tokens/separator.hpp"
#include "parser/tokens/word.hpp"

namespace fs = std::filesystem;

/**
 * @brief A text fixture to test parser::states::keywords::Let component
 * 
 */
class LetTest : public ::testing::Test
{
protected:
	using Separator = parser::tokens::Separator;
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
	parser::states::keywords::Let instance_{mediator_};
};

const fs::path LetTest::kFilePath{""};

/**
 * @brief Check if the Process() correctly processes the input
 * 
 */
TEST_F(LetTest, TestProcessUnexpectedTokenExceptionNoTokens)
{
	std::vector<std::unique_ptr<Token>> tokens{};

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	try
	{
		instance_.Process(lexer);
	}
	catch(const parser::exceptions::UnexpectedTokenException& e)
	{
		EXPECT_STREQ(e.what(), "");
	}
}

/**
 * @brief Check if an exception is thrown if there is no equals sign encountered
 * 
 */
TEST_F(LetTest, TestProcessRuntimeErrorNoTokenAfterID)
{
	std::vector<std::unique_ptr<Token>> tokens;
	tokens.emplace_back(std::make_unique<Word>("A"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), std::runtime_error);
}