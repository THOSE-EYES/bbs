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

#include "parser/states/keyword.hpp"

#include "parser/exceptions/unexpectedendoffileexception.hpp"
#include "parser/exceptions/unexpectedkeywordexception.hpp"
#include "parser/parser.hpp"
#include "parser/states/keywords/files.hpp"
#include "parser/states/keywords/project.hpp"

namespace parser::states
{
Keyword::Keyword(Parser* parser)
	: State{parser}
{}

void Keyword::Process(lexer::Lexer& lexer)
{
	if(!parser_)
	{
		throw std::runtime_error("Keyword::Process(): Parser is nullptr.");
	}

	// Check if the next token exists
	const auto token = lexer.Next();
	if(!token)
	{
		throw exceptions::UnexpectedEndOfFileException(parser_->GetContext());
	}

	// Process the correct keyword
	if(token->value == "prj")
	{
		parser_->SetState(std::make_unique<keywords::Project>(parser_));
		return;
	}
	else if(token->value == "files")
	{
		parser_->SetState(std::make_unique<keywords::Files>(parser_));
		return;
	}

	throw exceptions::UnexpectedKeywordException(parser_->GetContext(), token->value);
}
} // namespace parser::states