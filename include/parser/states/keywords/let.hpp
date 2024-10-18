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

#include "parser/states/types/string.hpp"
#include "parser/tokens/operator.hpp"

namespace parser::states::keywords
{
/**
 * @brief A "Let" state of the parser, used to parse !let keyword
 * 
 */
class Let : public types::String
{
public:
	/**
     * @brief Construct a new Let object
     * 
     * @param mediator - the associated parser's mediator
     */
	explicit Let(Mediator& mediator);

public:
	/**
     * @brief Process the input from the lexer
     * 
     * @param lexer - the lexer which handles tokenization of the input file
     */
	void Process(lexer::Lexer& lexer);

protected:
	/**
      * @brief Match the token with the given operator type
      * 
      * @param token - the token to check
      * @param value - the value to check the token against
      */
	void Match(tokens::Token* token, tokens::Operator::Type value);
};
} // namespace parser::states::keywords