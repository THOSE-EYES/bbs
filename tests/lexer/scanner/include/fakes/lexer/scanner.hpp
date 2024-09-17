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

#include "lexer/scanner.hpp"

namespace fakes::lexer
{
/**
 * @brief The a fake class that is used to wrap the handler of I/O operations 
 * 
 */
class Scanner : public ::lexer::Scanner
{
public:
	/**
     * @brief Construct a new Scanner object
     * 
     * @param path - the path to the file to scan
     */
	explicit Scanner(const std::filesystem::path& path);

public:
	using ::lexer::Scanner::context_;
	using ::lexer::Scanner::file_;
};
} // namespace fakes::lexer