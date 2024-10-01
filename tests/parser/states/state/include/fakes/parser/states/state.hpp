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

#include "parser/states/state.hpp"

namespace fakes::parser::states
{
/**
 * @brief An fake for the interface of states of the parser
 * 
 */
class State : public ::parser::states::State
{
public:
	/**
     * @brief Construct a new State object
     * 
     * @param parser - the associated parser
     */
	explicit State(::parser::Mediator& mediator)
		: ::parser::states::State{mediator}
	{}

public:
	/**
     * @brief Process the input from the lexer
     * 
     * @param lexer - the lexer which handles tokenization of the input file
     */
	void Process(::lexer::Lexer& lexer) override
	{
		// noop
	}

public:
	using ::parser::states::State::Match;
	using ::parser::states::State::mediator_;
};

} // namespace fakes::parser::states