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

#include "lexer/scanner.hpp"

#include "exceptions/filenotfoundexception.hpp"

namespace lexer
{
Scanner::Scanner(const std::filesystem::path& path)
{
	file_.open(path);
	if(!file_.is_open())
	{
		throw ::exceptions::FileNotFoundException(path);
	}

	// Get the first line from file and initialize the iterator
	std::string line;
	std::getline(file_, line);
	context_.Update(std::move(line));
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
	// Don't return anything if the file is closed
	if(!file_.is_open())
	{
		return {};
	}

	return context_.GetCharacter();
}

void Scanner::Move()
{
	// Don't return anything if the file is closed
	if(!file_.is_open())
	{
		return;
	}

	context_.Next();
}

const lexer::Context& Scanner::GetContext() const
{
	return context_;
}

void Scanner::Skip()
{
	// noop
}
} // namespace lexer