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

#include "parser/states/keywords/let.hpp"

#include "parser/exceptions/unexpectedtokenexception.hpp"
#include "parser/states/statement.hpp"
#include "parser/tokens/separator.hpp"

namespace parser::states::keywords
{
Let::Let(Mediator& mediator)
	: String{mediator}
{}

void Let::Process(lexer::Lexer& lexer)
{
	// Skip the trailing spaces
	auto token = State::SkipSeparators(lexer);
	if(!token)
	{
		throw exceptions::UnexpectedTokenException("");
	}

	// Process the variable's name (identifier)
	std::string id{};
	do
	{
		const auto value = std::move(token->value);

		// If the space is met, expect a "string"
		const auto ptr = dynamic_cast<tokens::Separator*>(token.get());
		if(ptr && ptr->type == tokens::Separator::Type::kSpace)
		{
			break;
		}

		// Add the token to the whole value
		id += value;
	} while((token = lexer.Next()));

	// Check if the assignment symbol is there
	token = State::SkipSeparators(lexer);
	Match(std::move(token), tokens::Operator::Type::kEqualitySign);

	// Process variable's value
	String::Process(lexer);

	// Return to the Statement state
	mediator_.SetState(std::make_unique<Statement>(mediator_));
}

void Let::Match(std::unique_ptr<tokens::Token> token, tokens::Operator::Type value)
{
	// Token might be nullptr, handle this case
	if(!token)
	{
		throw std::runtime_error("Let::Match() was called with nullptr.");
	}

	const auto ptr = dynamic_cast<tokens::Operator*>(token.get());
	if(!ptr || ptr->type != value)
	{
		throw exceptions::UnexpectedTokenException(std::move(token->value));
	}
}
} // namespace parser::states::keywords