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

#include "parser/exceptions/unexpectedtokenexception.hpp"
#include "parser/parser.hpp"

#include "fakes/parser/states/state.hpp"

/**
 * @brief A text fixture to test parser::states::State component
 * 
 */
class StateTest : public ::testing::Test
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
	fakes::parser::states::State instance_{mediator_};
};

/**
 * @brief Check if the Match() method correctly handles "nullptr" tokens
 * 
 */
TEST_F(StateTest, TestMatchNullptr)
{
	using Punctuator = parser::tokens::Punctuator;
	using Type = Punctuator::Type;

	EXPECT_THROW(instance_.Match(nullptr, Type::kDoubleQuoteMark), std::runtime_error);
}

/**
 * @brief Check if the Match() method correctly handles unexpected tokens
 * 
 */
TEST_F(StateTest, TestMatchNotPunctuator)
{
	using Punctuator = parser::tokens::Punctuator;
	using Type = Punctuator::Type;

	auto token = std::make_unique<parser::tokens::Token>("");
	EXPECT_THROW(instance_.Match(std::move(token), Type::kDoubleQuoteMark),
				 parser::exceptions::UnexpectedTokenException);
}