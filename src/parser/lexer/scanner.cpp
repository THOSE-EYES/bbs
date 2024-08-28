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

#include "parser/lexer/exceptions/fileemptyexception.hpp"
#include "parser/lexer/exceptions/filenotfoundexception.hpp"

namespace parser::lexer
{
Scanner::Scanner(const std::filesystem::path& path)
{
	namespace fs = std::filesystem;

	// If the file doesn't exist or it is not a regular file, throw an exception
	if(!fs::exists(path) || !fs::is_regular_file(path))
	{
		throw exceptions::FileNotFoundException(path);
	}

	// Throw an exception if the file is empty
	if(fs::is_empty(path))
	{
		throw exceptions::FileEmptyException(path);
	}

	file_.open(path);
	if(!file_.is_open())
	{
		throw exceptions::FileNotFoundException(path);
	}

	// Get the first line from file and initialize the iterator
	std::getline(file_, line_.value);
	position_ = line_.value.begin();

	// Skip empty lines, spaces and comments
	Skip();
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
	if(!file_.is_open() || position_ == line_.value.end())
	{
		return {};
	}

	return *position_;
}

void Scanner::Move()
{
	// Don't return anything if the file is closed
	if(!file_.is_open())
	{
		return;
	}

	++position_;

	// Skip empty lines, spaces and comments
	Skip();
}

const Scanner::Line& Scanner::GetLine() const
{
	return line_;
}

void Scanner::Skip()
{
	// Don't return anything if the file is closed
	if(!file_.is_open())
	{
		return;
	}

	// Read the next line if scanner finds a new line symbol, a comment or an empty line
	while(position_ == std::end(line_.value) || *position_ == '#' || *position_ == '\r')
	{
		std::getline(file_, line_.value);
		position_ = line_.value.begin();

		// Increment the index of the line
		++line_.index;
	}

	// Skip while there is a whitespace or a tab
	while(*position_ == ' ' || *position_ == '\t')
	{
		++position_;
	}

	// Check if the line still has anything to read
	if(file_.fail() || *position_ == '\0')
	{
		file_.close();
	}
}
} // namespace parser::lexer