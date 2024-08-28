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

#include <cstdint>

#include "parser/tokens/token.hpp"

namespace parser::tokens
{
/**
 * @brief The token that represents a punctuator
 * 
 */
struct Punctuator : public Token
{
	/**
	 * @brief The punctuator's type
	 * 
	 */
	enum class Type : uint8_t
	{
		kLeftSquareBracket,
		kRightSquareBracket,
		kExclamationMark,
		kDoubleQuoteMark,
		kDot,
		kComma,
		kSlash,
		kBackslash
	};

	/**
	 * @brief Construct a new Punctuator object
	 * 
	 * @param value_ - the string value of the token
	 * @param type_ - punctuator's type
	 */
	explicit Punctuator(std::string value_, Type type_);

	/**
	 * @brief Current punctuator's type
	 * 
	 */
	const Type type;
};
} // namespace parser::tokens