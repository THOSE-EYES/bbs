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

#include "parser/states/statement.hpp"

namespace fakes::parser::states
{
/**
 * @brief A "Statement" state of the parser, used to parse statements
 * 
 */
class Statement : public ::parser::states::Statement
{
public:
	/**
     * @brief Construct a new Statement object
     * 
     * @param mediator - the associated parser's mediator
     */
	explicit Statement(::parser::Mediator& mediator)
		: ::parser::states::Statement{mediator}
	{
		// noop
	}

public:
	using ::parser::states::Statement::mediator_;
};
} // namespace fakes::parser::states