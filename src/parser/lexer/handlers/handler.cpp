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

#include "parser/lexer/handlers/handler.hpp"

#include "parser/lexer/exceptions/unexpectedlexemeexception.hpp"

namespace parser::lexer::handlers
{
std::unique_ptr<Handler::Token> Handler::Process(Scanner& scanner) const
{
	// If the character is unavailable, then the end of the file reached
	const auto character = scanner.Get();
	if(!character)
	{
		return {};
	}

	// If there are no handlers, then the lexeme can't be processed
	if(!next_)
	{
		throw parser::lexer::exceptions::UnexpectedLexemeException(scanner.GetContext());
	}

	return next_->Process(scanner);
}

void Handler::SetNext(std::unique_ptr<Handler> next)
{
	next_ = std::move(next);
}
} // namespace parser::lexer::handlers