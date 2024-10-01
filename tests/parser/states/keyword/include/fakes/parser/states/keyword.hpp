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

#include "parser/states/keyword.hpp"

namespace fakes::parser::states
{
/**
 * @brief A fake for the "Keyword" state of the parser, used to parse keywords
 * 
 */
class Keyword : public ::parser::states::Keyword
{
public:
	/**
     * @brief Construct a new Keyword object
     * 
     * @param mediator - the associated parser's mediator
     */
	explicit Keyword(::parser::Mediator& mediator)
		: ::parser::states::Keyword{mediator}
	{
		// noop
	}

public:
	using ::parser::states::Keyword::mediator_;
};
} // namespace fakes::parser::states