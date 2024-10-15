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
#include "parser/exceptions/unexpectedkeywordexception.hpp"
#include "parser/parser.hpp"
#include "parser/states/keywords/deps.hpp"
#include "parser/states/keywords/files.hpp"
#include "parser/states/keywords/let.hpp"
#include "parser/states/keywords/pre.hpp"
#include "parser/states/keywords/project.hpp"

#include "aux/handlers/dummyhandler.hpp"
#include "fakes/lexer/lexer.hpp"
#include "fakes/parser/parser.hpp"
#include "fakes/parser/states/keyword.hpp"

namespace fs = std::filesystem;

using Token = parser::tokens::Token;

/**
 * @brief The default file path
 * 
 */
const fs::path kFilePath{""};

/**
 * @brief A text fixture to test parser::states::Keyword component
 * 
 */
class KeywordTest : public ::testing::Test
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
	fakes::parser::states::Keyword instance_{mediator_};
};

/**
 * @brief Check if the Process() method correctly handles abscence any
 *        symbol, meaning there is no other things to process.
 * 
 */
TEST_F(KeywordTest, TestProcessNoToken)
{
	std::vector<std::unique_ptr<Token>> tokens{};

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedEndOfFileException);
}

/**
 * @brief Check if the Process() method correctly handles unknown keywords
 * 
 */
TEST_F(KeywordTest, TestProcessUnknownKeyword)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Token>("A"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_THROW(instance_.Process(lexer), parser::exceptions::UnexpectedKeywordException);
}

/**
 * @brief Check if the Process() method correctly handles the "Project" keyword
 * 
 */
TEST_F(KeywordTest, TestProcessProjectKeyword)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Token>("prj"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));

	EXPECT_TRUE(
		dynamic_cast<parser::states::keywords::Project*>(instance_.mediator_.GetState().get()));
}

/**
 * @brief Check if the Process() method correctly handles the "Files" keyword
 * 
 */
TEST_F(KeywordTest, TestProcessFilesKeyword)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Token>("files"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_TRUE(
		dynamic_cast<parser::states::keywords::Files*>(instance_.mediator_.GetState().get()));
}

/**
 * @brief Check if the Process() method correctly handles the "Deps" keyword
 * 
 */
TEST_F(KeywordTest, TestProcessDepsKeyword)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Token>("deps"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_TRUE(
		dynamic_cast<parser::states::keywords::Deps*>(instance_.mediator_.GetState().get()));
}

/**
 * @brief Check if the Process() method correctly handles the "Pre" keyword
 * 
 */
TEST_F(KeywordTest, TestProcessPreKeyword)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Token>("pre"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_TRUE(dynamic_cast<parser::states::keywords::Pre*>(instance_.mediator_.GetState().get()));
}

/**
 * @brief Check if the Process() method correctly handles the "!let" keyword
 * 
 */
TEST_F(KeywordTest, TestProcessLetKeyword)
{
	std::vector<std::unique_ptr<Token>> tokens{};
	tokens.emplace_back(std::make_unique<Token>("let"));

	auto handler = std::make_unique<handlers::DummyHandler>(std::move(tokens));
	fakes::lexer::Lexer lexer{kFilePath, std::move(handler)};

	EXPECT_NO_THROW(instance_.Process(lexer));
	EXPECT_TRUE(dynamic_cast<parser::states::keywords::Let*>(instance_.mediator_.GetState().get()));
}