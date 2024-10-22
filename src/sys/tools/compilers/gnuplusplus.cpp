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

#include "sys/tools/compilers/gnuplusplus.hpp"

// clang-format off
#ifdef __linux__
    #include "sys/nix/command.hpp"

    using SystemCommand = sys::nix::Command;
#endif
// clang-format on

#include <algorithm>
#include <sstream>

#include <iostream>

#include "sys/exceptions/compilationerrorexception.hpp"

namespace sys::tools::compilers
{
const std::string GNUPlusPlus::kCompiler{"g++"};

GNUPlusPlus::GNUPlusPlus(std::string&& flags,
						 std::vector<std::filesystem::path>&& include_directories)
	: kFlags{std::move(flags)}
	, kDirectories{std::move(include_directories)}
{}

void GNUPlusPlus::Compile(const std::filesystem::path& file, const std::filesystem::path& out)
{
	std::stringstream parameters;
	parameters << kFlags << " -c " << file.string() << " -o " << out.string();

	// Add include directories
	for(auto& directory : kDirectories)
	{
		parameters << " -I " << directory.string();
	}

	SystemCommand command{kCompiler, parameters.str()};
	if(!command.Execute())
	{
		throw exceptions::CompilationErrorException(file);
	}
}

std::vector<std::filesystem::path>
GNUPlusPlus::GetDependencies(const std::filesystem::path& file) const
{
	std::stringstream parameters;
	parameters << kFlags << " -MM " << file.string();

	// Add include directories
	for(auto& directory : kDirectories)
	{
		parameters << " -I " << directory.string();
	}

	SystemCommand command{kCompiler, parameters.str()};
	if(!command.Execute())
	{
		throw exceptions::CompilationErrorException(file);
	}

	// Clear the output from the unprintable symbols
	auto output = command.GetOutput();
	output.erase(
		std::remove_if(output.begin(), output.end(), [](auto x) { return std::iscntrl(x); }),
		output.end());

	// Split the output into a vector of files
	auto strings = Split(output, " ");
	std::vector<std::filesystem::path> dependencies;
	for(auto it = strings.begin() + 2; it != strings.end(); ++it)
	{
		dependencies.emplace_back(*it);
	}
	return dependencies;
}

std::vector<std::string> GNUPlusPlus::Split(std::string string, const std::string& delimiter)
{
	std::vector<std::string> tokens;

	size_t pos = 0;
	std::string token;
	while((pos = string.find(delimiter)) != std::string::npos)
	{
		token = string.substr(0, pos);
		if(!token.empty())
		{
			tokens.push_back(token);
		}

		string.erase(0, pos + delimiter.length());
	}
	if(!token.empty())
	{
		tokens.push_back(string);
	}

	return tokens;
}
} // namespace sys::tools::compilers