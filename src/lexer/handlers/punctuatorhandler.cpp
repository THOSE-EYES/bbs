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

#include "lexer/handlers/punctuatorhandler.hpp"

#include "lexer/exceptions/unexpectedlexemeexception.hpp"

namespace lexer::handlers
{

std::unique_ptr<PunctuatorHandler::Token> PunctuatorHandler::Process(Scanner& scanner) const
{
	// Let the default handler do the job if the character is not available
	const auto character = scanner.Get();
	if(!character)
	{
		return Handler::Process(scanner);
	}

	// Check if the character is in the map
	const auto iterator = Punctuator::kPunctuatorToTypeMap.find(character.value());
	if(iterator != Punctuator::kPunctuatorToTypeMap.end())
	{
		scanner.Move();
		return std::make_unique<Punctuator>(std::string(1, character.value()), iterator->second);
	}

	return Handler::Process(scanner);
}
} // namespace lexer::handlers