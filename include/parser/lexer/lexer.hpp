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

#include <string>

#include "parser/lexer/handlers/handler.hpp"
#include "parser/lexer/scanner.hpp"
#include "parser/tokens/token.hpp"

namespace parser::lexer
{
/**
 * @brief Conversion of a text into meaningful lexical tokens
 * 
 */
class Lexer
{
	using Token = parser::tokens::Token;

public:
	/**
     * @brief Construct a new Lexer object
     * 
     * @param path - the path to the file to scan
     */
	explicit Lexer(const std::filesystem::path& path);

public:
	/**
     * @brief Get the next available token
     * 
     * @return std::unique_ptr<Token> - a pointer to the next token or nullptr 
     */
	std::unique_ptr<Token> Next();

protected:
	/**
     * @brief An abstraction used to strip the lexer of I/O operations and comment/empty line handling
     * 
     */
	Scanner scanner_;

	/**
     * @brief A set of handlers, used to distinguish between different types of tokens
     * 
     */
	std::unique_ptr<handlers::Handler> handler_;
};
} // namespace parser::lexer