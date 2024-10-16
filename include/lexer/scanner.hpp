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

#include <filesystem>
#include <fstream>
#include <optional>

#include "lexer/context.hpp"

namespace lexer
{
/**
 * @brief The class is used to handle file I/O operations and lift the weight
 *        of processing whitespaces, tabs and comments off the lexer
 * 
 */
class Scanner
{
public:
	/**
     * @brief Construct a new Scanner object
     * 
     * @param path - the path to the file to scan
     */
	explicit Scanner(const std::filesystem::path& path);

	/**
     * @brief Destroy the Scanner object
     * 
     */
	~Scanner();

public:
	/**
     * @brief Get the available character
     * 
     * @return std::optional<char> - the current character in the file
     */
	std::optional<char> Get();

	/**
     * @brief Move to the next available character
     * 
     */
	void Move();

	/**
      * @brief Get the current context
      * 
      * @return const Context& - a reference to the context instance
      */
	const Context& GetContext() const;

protected:
	/**
      * @brief Makes the iterator skip empty lines, spaces and comments
      * 
      */
	void Skip();

protected:
	/**
     * @brief The file which is processed
     * 
     */
	std::ifstream file_;

	/**
     * @brief The current context
     * 
     */
	Context context_;
};
} // namespace lexer