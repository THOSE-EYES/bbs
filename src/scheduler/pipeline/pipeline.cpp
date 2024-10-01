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

#include "scheduler/pipeline/pipeline.hpp"

// clang-format off
#ifdef __linux__
    #include "sys/nix/command.hpp"

    using Command = sys::nix::Command;
#endif
// clang-format on

#include "scheduler/exceptions/compilationerrorexception.hpp"
#include "scheduler/exceptions/linkerrorexception.hpp"

namespace scheduler::pipeline
{
namespace
{
const std::string kCompiler = "g++";
}

Pipeline::Pipeline(Job job)
	: job_{std::move(job)}
{}

void Pipeline::Run() const
{
	std::stringstream parameters{};
	for(const auto& file : job_.GetFiles())
	{
		Compile(file);

		// Add the object file name to the list of parameters
		const auto obj = file.filename().replace_extension(".o");
		parameters << std::move(obj.string()) << " ";
	}

	// Link all the object files into the executable
	Command command{kCompiler, parameters.str()};
	if(!command.Execute())
	{
		throw exceptions::LinkErrorException(job_.GetProjectName());
	}
}

void Pipeline::Compile(const std::filesystem::path& file) const
{
	std::stringstream parameters;
	parameters << "-c" << " " << file.string();

	Command command{kCompiler, parameters.str()};
	if(!command.Execute())
	{
		throw exceptions::CompilationErrorException(file);
	}
}
} // namespace scheduler::pipeline