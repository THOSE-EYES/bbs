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

#include "lexer/lexer.hpp"
#include "parser/mediator.hpp"
#include "parser/tokens/punctuator.hpp"

namespace parser::states
{
/**
 * @brief An interface of states of the parser
 * 
 */
class State
{
public:
	/**
     * @brief Construct a new State object
     * 
     * @param mediator - the associated parser's mediator
     */
	explicit State(Mediator& mediator);

public:
	/**
     * @brief Process the input from the lexer
     * 
     * @param lexer - the lexer which handles tokenization of the input file
     */
	virtual void Process(lexer::Lexer& lexer) = 0;

protected:
	/**
      * @brief Skip the separator tokens
      * 
      * @param lexer - the lexer to get tokens from
      * @return std::unique_ptr<tokens::Token> - the token next to the separator
      */
	static std::unique_ptr<tokens::Token> SkipSeparators(lexer::Lexer& lexer);

	/**
      * @brief Match the token with the given punctuator type
      * 
      * @param token - the token to check
      * @param value - the value to check the token against
      */
	void Match(tokens::Token* token, tokens::Punctuator::Type value);

protected:
	/**
     * @brief The associated parser
     * 
     */
	Mediator& mediator_;
};

} // namespace parser::states