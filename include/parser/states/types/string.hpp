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

#include "parser/states/state.hpp"

namespace parser::states::types
{
/**
 * @brief A "String" state of the parser, used to parse strings
 * 
 */
class String : public State
{
public:
	/**
     * @brief Construct a new String object
     * 
     * @param parser - the associated parser
     */
	explicit String(Parser* parser);

public:
	/**
     * @brief Process the input from the lexer
     * 
     * @param lexer - the lexer which handles tokenization of the input file
     */
	void Process(lexer::Lexer& lexer);

	/**
      * @brief Get the string's value
      * 
      * @return std::string 
      */
	std::string GetValue() const;

	/**
       * @brief Clear the internal value
       * 
       */
	void Clear();

private:
	/**
      * @brief The value of the string
      * 
      */
	std::string value_;
};
} // namespace parser::states::types