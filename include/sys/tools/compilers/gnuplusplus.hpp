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
#include <vector>

#include "sys/tools/compiler.hpp"

namespace sys::tools::compilers
{
/**
 * @brief An interface for the compilers that are supported by the application
 * 
 */
class GNUPlusPlus : public Compiler
{
public:
	/**
	 * @brief Construct a new GNUPlusPlus object
	 * 
	 * @param flags - compiler flags
	 * @param include_directories - the directories to include while building the application
	 */
	explicit GNUPlusPlus(std::string&& flags,
						 std::vector<std::filesystem::path>&& include_directories);

public:
	/**
	 * @brief Compile the given file
	 * 
	 * @param file - the file to compile
	 * @param out - the file where to store the output
	 */
	void Compile(const std::filesystem::path& file, const std::filesystem::path& out) override;

	/**
	 * @brief Get the dependencies of the file
	 * 
	 * @param file - the file to inspect
	 * @return std::vector<std::filesystem::path> - a vector of dependencies
	 */
	std::vector<std::filesystem::path>
	GetDependencies(const std::filesystem::path& file) const override;

public:
	/**
	 * @brief The compiler program name
	 * 
	 */
	static const std::string kCompiler;

protected:
	/**
	 * @brief Split the given string
	 * 
	 * @param string - the string to split
	 * @param delimiter - the delimiter to use to split the string
	 * @return std::vector<std::string> - a split string
	 */
	static std::vector<std::string> Split(std::string string, const std::string& delimiter);

protected:
	/**
	 * @brief The flags used during the compilation process
	 * 
	 */
	const std::string kFlags;

	/**
	 * @brief The directories to include while building the application
	 * 
	 */
	const std::vector<std::filesystem::path> kDirectories;
};
} // namespace sys::tools::compilers