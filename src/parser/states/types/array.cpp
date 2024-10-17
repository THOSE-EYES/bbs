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
#include "parser/states/types/string.hpp"

namespace parser::states::types
{
Array::Array(Mediator& mediator)
	: State{mediator}
{}

void Array::Process(lexer::Lexer& lexer)
{
	// Skip separators in between the keyword and the
	auto token = SkipSeparators(lexer);

	// Expect the bracket at the start of the string
	Match(token.get(), tokens::Punctuator::Type::kLeftSquareBracket);

	// Process the tokens
	String string_handler{mediator_};
	do
	{
		// Get the next string
		string_handler.Process(lexer);
		value_.push_back(string_handler.GetValue());
		string_handler.Clear();

		// Get the terminator token
		token = SkipSeparators(lexer);

		// Try to match any punctuator
		try
		{
			Match(token.get(), tokens::Punctuator::Type::kRightSquareBracket);
			return;
		}
		catch(const exceptions::UnexpectedTokenException&)
		{
			Match(token.get(), tokens::Punctuator::Type::kComma);
		}
	} while(token);

	throw exceptions::UnexpectedEndOfFileException(lexer.GetContext());
}

std::vector<std::string> Array::GetValue() const
{
	return value_;
}
} // namespace parser::states::types