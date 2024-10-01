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

#include "parser/states/types/array.hpp"

#include "parser/exceptions/unexpectedendoffileexception.hpp"
#include "parser/exceptions/unexpectedtokenexception.hpp"

namespace parser::states::types
{
Array::Array(Mediator& mediator)
	: String{mediator}
{}

void Array::Process(lexer::Lexer& lexer)
{
	Match(lexer.Next(), tokens::Punctuator::Type::kLeftSquareBracket);

	tokens::Punctuator::Type type;
	std::unique_ptr<tokens::Token> terminator;
	do
	{
		// Get the next string
		String::Process(lexer);
		value_.push_back(String::GetValue());
		String::Clear();

		// Get the terminator token
		terminator = lexer.Next();
		if(!terminator)
		{
			throw exceptions::UnexpectedEndOfFileException(lexer.GetContext());
		}

		// Get the type of the terminator
		auto ptr = dynamic_cast<tokens::Punctuator*>(terminator.get());
		if(!ptr)
		{
			throw exceptions::UnexpectedTokenException(std::move(terminator->value));
		}
		type = ptr->type;

	} while(type == tokens::Punctuator::Type::kComma);

	Match(std::move(terminator), tokens::Punctuator::Type::kRightSquareBracket);
}

std::vector<std::string> Array::GetValue() const
{
	return value_;
}
} // namespace parser::states::types