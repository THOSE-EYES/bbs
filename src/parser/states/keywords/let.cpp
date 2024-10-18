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
#include "parser/tokens/word.hpp"

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

	// The first element is a word
	const auto ptr = dynamic_cast<tokens::Word*>(token.get());
	if(!ptr)
	{
		// FIXME: use context
		throw exceptions::UnexpectedTokenException("");
	}

	std::string id = token->GetValue();

	// Check if the assignment symbol is there
	token = State::SkipSeparators(lexer);
	Match(token.get(), tokens::Operator::Type::kEqualitySign);

	// Process variable's value
	String::Process(lexer);

	// Update the data inside the mediator
	mediator_.DeclareVariable(std::move(id), std::move(GetValue()));
	mediator_.SetState(std::make_unique<Statement>(mediator_));
}

void Let::Match(tokens::Token* token, tokens::Operator::Type value)
{
	if(!token)
	{
		// FIXME: replace with the UnexpectedEndOfFile exceptions
		throw exceptions::UnexpectedTokenException("EOF");
	}

	const auto ptr = dynamic_cast<tokens::Operator*>(token);
	if(!ptr || ptr->type != value)
	{
		// FIXME: use context
		throw exceptions::UnexpectedTokenException("");
	}
}
} // namespace parser::states::keywords