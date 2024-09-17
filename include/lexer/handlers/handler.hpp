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

#pragma once

#include <memory>

#include "lexer/scanner.hpp"
#include "parser/tokens/token.hpp"

namespace lexer::handlers
{
/**
 * @brief A default Lexer input handler, an implementation of the CoR pattern
 * 
 */
class Handler
{
	using Token = parser::tokens::Token;

public:
	/**
	 * @brief Process the input and return the token if possible
	 * 
	 * @param scanner - the source of characters to process
	 * @return std::unique_ptr<Token> - a pointer to the token or nullptr 
	 */
	virtual std::unique_ptr<Token> Process(Scanner& scanner) const;

	/**
	 * @brief Set the next handler to be called to process the input
	 * 
	 * @param next - a pointer to the next handler to be called
	 */
	void SetNext(std::unique_ptr<Handler> next);

protected:
	/**
	 * @brief A pointer to the handler, next on the line to process the input
	 * 
	 */
	std::unique_ptr<Handler> next_;
};
} // namespace lexer::handlers