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

#include "parser/exceptions/undeclaredvariableexception.hpp"

namespace fakes::parser::exceptions
{
/**
 * @brief An fake for the exception, used to notify that the variable's declaration was not found
 * 
 */
class UndeclaredVariableException : public ::parser::exceptions::UndeclaredVariableException
{
public:
	/**
	 * @brief Construct a new UndeclaredVariableException object
	 * 
	 * @param project - the ID that caused the error
	 */
	explicit UndeclaredVariableException(std::string id)
		: ::parser::exceptions::UndeclaredVariableException{std::move(id)}
	{}

public:
	using ::parser::exceptions::UndeclaredVariableException::kMessage;
};
} // namespace fakes::parser::exceptions