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

#include "parser/parser.hpp"
#include "parser/states/keywords/files.hpp"
#include "parser/states/keywords/project.hpp"

namespace parser::states
{
Statement::Statement(Parser* parser)
	: State{parser}
{}

void Statement::Process(lexer::Lexer& lexer)
{
	if(!parser_)
	{
		throw std::runtime_error("Statement::Process(): Parser is nullptr.");
	}

	std::unique_ptr<State> state;

	// Check if the token to process is present
	auto start = lexer.Next();
	if(!start)
	{
		parser_->SetState(std::move(state));
		return;
	}

	// Every statement begins with the exclamation mark
	Match(std::move(start), tokens::Punctuator::Type::kExclamationMark);

	// Process the correct keyword
	const auto token = lexer.Next();
	if(token->value == "prj")
	{
		state = std::make_unique<keywords::Project>(parser_);
	}
	else if(token->value == "files")
	{
		state = std::make_unique<keywords::Files>(parser_);
	}

	parser_->SetState(std::move(state));
}
} // namespace parser::states