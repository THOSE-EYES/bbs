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
Scanner::Scanner(const std::string& filename)
{
	file_.open(filename);
	if(!file_.is_open())
	{
		throw exceptions::FileNotFoundException(filename);
	}

	// Get the first line from file and initialize the iterator
	std::getline(file_, line_);
	position_ = line_.begin();
}

Scanner::~Scanner()
{
	// Close the file
	if(file_.is_open())
	{
		file_.close();
	}
}

std::optional<char> Scanner::Next()
{
	// Don't return anything if the file is closed
	if(!file_.is_open())
	{
		return {};
	}

	// Skip while there is a whitespace or a tab
	while(*position_ == ' ' || *position_ == '\t')
	{
		++position_;
	}

	// Read the next line if scanner finds a new line symbol, a comment or an empty line
	if(position_ == std::end(line_) || *position_ == '#')
	{
		std::getline(file_, line_);
		position_ = line_.begin();
	}

	// Check if there is a character to return
	if(file_.fail() || *position_ == '\0')
	{
		file_.close();
		return {};
	}

	return *(position_++);
}
} // namespace parser::lexer