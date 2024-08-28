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

#include <stdexcept>

#include "parser/lexer/scanner.hpp"

namespace parser::lexer::exceptions
{
namespace lex = ::parser::lexer;

/**
 * @brief An exception, used to notify that the given lexeme is unexpected
 * 
 */
class UnexpectedLexemeException : public std::runtime_error
{
public:
	/**
	 * @brief Construct a new UnexpectedLexemeException object
	 * 
	 * @param line - the line that caused the error
	 */
	explicit UnexpectedLexemeException(const lex::Scanner::Line& line);

protected:
	/**
	 * @brief The message, seeing on the exception occurence
	 * 
	 */
	static const std::string kMessage;
};
} // namespace parser::lexer::exceptions