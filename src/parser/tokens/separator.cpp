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

#include "parser/tokens/separator.hpp"

#include <algorithm>

namespace parser::tokens
{
const std::map<char, Separator::Type> Separator::kSeparatorToTypeMap{{' ', Type::kSpace}};

Separator::Separator(Type type_)
	: Token{}
	, type{type_}
{}

std::string Separator::GetValue() const
{
	const auto iterator = std::find_if(kSeparatorToTypeMap.begin(),
									   kSeparatorToTypeMap.end(),
									   [&](const auto& pair) { return pair.second == type; });
	return std::string(1, iterator->first);
}
} // namespace parser::tokens