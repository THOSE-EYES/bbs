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
#include <string>
#include <vector>

namespace sys::tools
{
/**
 * @brief An interface for the compilers that are supported by the application
 * 
 */
struct Compiler
{
	/**
	 * @brief Compile the given file
	 * 
	 * @param file - the file to compile
	 * @param out - the file where to store the output
	 */
	virtual void Compile(const std::filesystem::path& file, const std::filesystem::path& out) = 0;

	/**
	 * @brief Get the dependencies of the file
	 * 
	 * @param file - the file to inspect
	 * @return std::vector<std::filesystem::path> - a vector of dependencies
	 */
	virtual std::vector<std::filesystem::path>
	GetDependencies(const std::filesystem::path& file) const = 0;
};
} // namespace sys::tools