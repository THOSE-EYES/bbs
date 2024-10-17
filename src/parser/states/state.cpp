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

#include "parser/states/state.hpp"

#include "parser/exceptions/unexpectedtokenexception.hpp"
#include "parser/tokens/separator.hpp"

namespace parser::states
{
State::State(Mediator& mediator)
	: mediator_{mediator}
{}

std::shared_ptr<tokens::Token> State::SkipSeparators(lexer::Lexer& lexer)
{
	std::shared_ptr<tokens::Token> token;
	while((token = lexer.Next()))
	{
		// Token might be nullptr, handle this case
		if(!token)
		{
			throw std::runtime_error("State::SkipSeparators() was called with nullptr.");
		}

		if(!dynamic_cast<tokens::Separator*>(token.get()))
		{
			break;
		}
	}

	return token;
}

void State::Match(tokens::Token* token, tokens::Punctuator::Type value)
{
	if(!token)
	{
		// FIXME: replace with the UnexpectedEndOfFile exception
		throw exceptions::UnexpectedTokenException("EOF");
	}

	const auto ptr = dynamic_cast<tokens::Punctuator*>(token);
	if(!ptr || ptr->type != value)
	{
		throw exceptions::UnexpectedTokenException(std::move(token->GetValue()));
	}
}
} // namespace parser::states