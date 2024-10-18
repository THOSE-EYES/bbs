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
#include "parser/states/variable.hpp"
#include "parser/tokens/operator.hpp"

namespace parser::states::types
{
String::String(Mediator& mediator)
	: State{mediator}
{}

void String::Process(lexer::Lexer& lexer)
{
	// Skip separators in between the keyword and the
	auto token = State::SkipSeparators(lexer);

	// Expect the double quote mark at the start of the string
	Match(token.get(), ::parser::tokens::Punctuator::Type::kDoubleQuoteMark);

	// Add tokens one by one to the internal buffer
	while((token = lexer.Next()))
	{
		try
		{
			Match(token.get(), tokens::Punctuator::Type::kDoubleQuoteMark);
			return;
		}
		catch(const exceptions::UnexpectedTokenException&)
		{
			auto ptr = dynamic_cast<tokens::Operator*>(token.get());
			if(ptr && ptr->type == tokens::Operator::Type::kDollarSign)
			{
				Variable variable{mediator_};
				variable.Process(lexer);

				// Add variable's value to the result
				value_ += variable.GetValue();

				continue;
			}

			// Add the token to the whole value
			value_ += token->GetValue();
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