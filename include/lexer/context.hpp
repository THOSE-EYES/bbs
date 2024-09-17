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

#include <cstdint>
#include <optional>
#include <string>

namespace lexer
{
/**
 * @brief A struct that holds information about the current line that being processed
 * 
 */
class Context
{
public:
	/**
      * @brief Update the string inside the context
      * 
      * @param value - the value of the string
      */
	void Update(std::string&& value);

	/**
      * @brief Get the internal line
      * 
      * @return std::string - the internal line
      */
	std::string GetLine() const;

	/**
      * @brief Get the current character
      * 
      * @return std::optional<char> - a character that is on the current position or std:nullopt
      */
	std::optional<char> GetCharacter() const;

	/**
      * @brief Get to the next position in the file
      * 
      */
	void Next();

	/**
      * @brief Get the line index
      * 
      * @return std::size_t - the line index inside the file
      */
	std::size_t GetLineIndex() const;

	/**
      * @brief Get the character position
      * 
      * @return std::size_t - the position in the line
      */
	std::size_t GetPosition() const;

protected:
	/**
     * @brief The value of the line
     * 
     */
	std::string line_;

	/**
     * @brief Line's index inside the file
     * 
     */
	std::size_t line_index_{0};

	/**
     * @brief Current position in the line
     * 
     */
	std::string::iterator position_;
};
} // namespace lexer