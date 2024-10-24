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

#include "parser/states/statement.hpp"

#include "parser/states/keyword.hpp"

namespace parser::states
{
Statement::Statement(Mediator& mediator)
	: State{mediator}
{}

void Statement::Process(lexer::Lexer& lexer)
{
	// Check if the token to process is present
	auto token = State::SkipSeparators(lexer);
	if(!token)
	{
		mediator_.SetState({});
		return;
	}

	// Every statement begins with the exclamation mark
	Match(token.get(), tokens::Punctuator::Type::kExclamationMark);

	// By default, statements start with keywords
	mediator_.SetState(std::make_unique<Keyword>(mediator_));
}
} // namespace parser::states