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

#include "parser/lexer/context.hpp"

#include <iterator>

namespace parser::lexer
{
void Context::Update(std::string&& value)
{
	line_ = std::move(value);
	position_ = line_.begin();
}

std::string Context::GetLine() const
{
	return {};
}

std::optional<char> Context::GetCharacter() const
{
	if(position_ == line_.end())
	{
		return {};
	}
	return *position_;
}

void Context::Next()
{
	++position_;
}

std::size_t Context::GetLineIndex() const
{
	return {};
}

std::size_t Context::GetPosition() const
{
	return {};
}
} // namespace parser::lexer