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

#include "parser/lexer/scanner.hpp"

#include "parser/lexer/exceptions/filenotfoundexception.hpp"

namespace parser::lexer
{
Scanner::Scanner(const std::filesystem::path& path)
{
	file_.open(path);
	if(!file_.is_open())
	{
		throw exceptions::FileNotFoundException(path);
	}

	// Get the first line from file and initialize the iterator
	std::getline(file_, line_.value);
	position_ = line_.value.begin();
}

Scanner::~Scanner()
{
	// Close the file
	if(file_.is_open())
	{
		file_.close();
	}
}

std::optional<char> Scanner::Get()
{
	if(line_.value.empty())
	{
		return {};
	}
	return *position_;
}

void Scanner::Move()
{
	// noop
}

const Scanner::Line& Scanner::GetLine() const
{
	return line_;
}

void Scanner::Skip()
{
	// noop
}
} // namespace parser::lexer