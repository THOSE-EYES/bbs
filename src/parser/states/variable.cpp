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

#include "parser/states/variable.hpp"

#include "parser/exceptions/unexpectedendoffileexception.hpp"
#include "parser/tokens/word.hpp"

namespace parser::states
{
Variable::Variable(Mediator& mediator)
	: State{mediator}
{}

void Variable::Process(lexer::Lexer& lexer)
{
	std::string id{};
	std::shared_ptr<tokens::Token> token{};
	while((token = lexer.Next()))
	{
		auto ptr = dynamic_cast<tokens::Word*>(token.get());
		if(!ptr)
		{
			value_ = mediator_.GetVariableValue(id);
			return;
		}

		// Add the token to the whole ID
		id += std::move(token->GetValue());
	}

	throw exceptions::UnexpectedEndOfFileException(lexer.GetContext());
}

std::string Variable::GetValue() const
{
	return value_;
}

void Variable::Clear()
{
	value_.clear();
}
} // namespace parser::states