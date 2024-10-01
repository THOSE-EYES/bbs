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
#include "parser/states/keyword.hpp"

#include "aux/handlers/dummyhandler.hpp"
#include "fakes/lexer/lexer.hpp"
#include "fakes/parser/parser.hpp"
#include "fakes/parser/states/statement.hpp"

namespace fs = std::filesystem;

using Token = parser::tokens::Token;
using Punctuator = parser::tokens::Punctuator;

/**
 * @brief The default file path
 * 
 */
const fs::path kFilePath{""};

/**
 * @brief A text fixture to test parser::states::Statement component
 * 
 */
class StatementTest : public ::testing::Test
{
protected:
	/**
	 * @brief A mediator instance
	 * 
	 */
	parser::Mediator mediator_;

	/**
	 * @brief The instance to test
	 * 
	 */
	fakes::parser::states::Statement instance_{mediator_};
};

/**
 * @brief Check if the Process() method correctly handles abscence any
 *        symbol, meaning there is no other things to process.
 * 
 */
TEST_F(StatementTest, TestProcessNoToken)
{
	std::vector<std::unique_ptr<Token>> tokens{};

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
}

/**
 * @brief Check if the Process() method correctly handles abscence of the
 *        leading exclamation mark
 * 
 */
TEST_F(StatementTest, TestProcessLeadingExclamationMarkAbscence)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Token>("A"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedTokenException);
}

/**
 * @brief Check if the Process() method correctly handles the transition to the
 *        "keyword" state
 * 
 */
TEST_F(StatementTest, TestProcessProjectKeyword)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Punctuator>("!", Punctuator::Type::kExclamationMark));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_TRUE(dynamic_cast<parser::states::Keyword*>(instance_.mediator_.GetState().get()));
}