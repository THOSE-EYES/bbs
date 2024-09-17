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

#include "parser/tokens/punctuator.hpp"

namespace parser::tokens
{
const std::map<char, Punctuator::Type> Punctuator::kPunctuatorToTypeMap{
	{'[', Type::kLeftSquareBracket},
	{']', Type::kRightSquareBracket},
	{'!', Type::kExclamationMark},
	{'\"', Type::kDoubleQuoteMark},
	{'.', Type::kDot},
	{',', Type::kComma},
	{'/', Type::kSlash},
	{'\\', Type::kBackslash},
};

Punctuator::Punctuator(std::string value_, Type type_)
	: Token{std::move(value_)}
	, type{type_}
{}
} // namespace parser::tokens