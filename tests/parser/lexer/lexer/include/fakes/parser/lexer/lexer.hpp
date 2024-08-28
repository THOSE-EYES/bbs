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

#include "parser/lexer/lexer.hpp"

namespace fakes::parser::lexer
{
namespace lex = ::parser::lexer;

/**
 * @brief A fake for the tool used for conversion of a text into meaningful lexical tokens
 * 
 */
class Lexer : public lex::Lexer
{
public:
	/**
     * @brief Construct a new Lexer object
     * 
     * @param path - the path to the file to scan
     */
	explicit Lexer(const std::filesystem::path& path)
		: lex::Lexer{path}
	{}

public:
	using lex::Lexer::handler_;
};
} // namespace fakes::parser::lexer