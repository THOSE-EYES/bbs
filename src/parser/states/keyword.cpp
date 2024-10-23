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
#include "parser/states/keywords/cflags.hpp"
#include "parser/states/keywords/deps.hpp"
#include "parser/states/keywords/files.hpp"
#include "parser/states/keywords/inc.hpp"
#include "parser/states/keywords/let.hpp"
#include "parser/states/keywords/post.hpp"
#include "parser/states/keywords/pre.hpp"
#include "parser/states/keywords/project.hpp"

namespace parser::states
{
Keyword::Keyword(Mediator& mediator)
	: State{mediator}
{}

void Keyword::Process(lexer::Lexer& lexer)
{
	// Check if the next token exists
	const auto token = lexer.Next();
	if(!token)
	{
		throw exceptions::UnexpectedEndOfFileException(lexer.GetContext());
	}

	// Process the correct keyword
	const auto& keyword = token->GetValue();
	if(keyword == "cflags")
	{
		mediator_.SetState(std::make_unique<keywords::CFlags>(mediator_));
		return;
	}
	else if(keyword == "deps")
	{
		mediator_.SetState(std::make_unique<keywords::Deps>(mediator_));
		return;
	}
	else if(keyword == "files")
	{
		mediator_.SetState(std::make_unique<keywords::Files>(mediator_));
		return;
	}
	else if(keyword == "prj")
	{
		mediator_.SetState(std::make_unique<keywords::Project>(mediator_));
		return;
	}
	else if(keyword == "pre")
	{
		mediator_.SetState(std::make_unique<keywords::Pre>(mediator_));
		return;
	}
	else if(keyword == "post")
	{
		mediator_.SetState(std::make_unique<keywords::Post>(mediator_));
		return;
	}
	else if(keyword == "let")
	{
		mediator_.SetState(std::make_unique<keywords::Let>(mediator_));
		return;
	}
	else if(keyword == "inc")
	{
		mediator_.SetState(std::make_unique<keywords::Inc>(mediator_));
		return;
	}

	throw exceptions::UnexpectedKeywordException(lexer.GetContext(), token->GetValue());
}
} // namespace parser::states