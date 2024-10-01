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

#include "parser/states/types/string.hpp"

#include "parser/exceptions/unexpectedtokenexception.hpp"

namespace parser::states::types
{
String::String(Mediator& mediator)
	: State{mediator}
{}

void String::Process(lexer::Lexer& lexer)
{
	Match(lexer.Next(), ::parser::tokens::Punctuator::Type::kDoubleQuoteMark);

	std::unique_ptr<tokens::Token> token;
	while((token = lexer.Next()))
	{
		const auto value = std::move(token->value);
		try
		{
			Match(std::move(token), tokens::Punctuator::Type::kDoubleQuoteMark);
			return;
		}
		catch(const exceptions::UnexpectedTokenException& e)
		{
			// Add the token to the whole value
			value_ += value;
		}
	}

	throw exceptions::UnexpectedTokenException("");
}

std::string String::GetValue() const
{
	return value_;
}

void String::Clear()
{
	value_.clear();
}
} // namespace parser::states::types