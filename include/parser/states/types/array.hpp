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
#include <vector>

#include "parser/states/state.hpp"

namespace parser::states::types
{
/**
 * @brief A "Array" state of the parser, used to parse arrays
 * 
 */
class Array : public State
{
public:
	/**
     * @brief Construct a new Array object
     * 
     * @param mediator - the associated parser's mediator
     */
	explicit Array(Mediator& mediator);

public:
	/**
     * @brief Process the input from the lexer
     * 
     * @param lexer - the lexer which handles tokenization of the input file
     */
	void Process(lexer::Lexer& lexer) override;

	/**
      * @brief Get the array's value
      * 
      * @return std::vector<std::string> 
      */
	std::vector<std::string> GetValue() const;

private:
	/**
      * @brief The value of the array
      * 
      */
	std::vector<std::string> value_;
};
} // namespace parser::states::types