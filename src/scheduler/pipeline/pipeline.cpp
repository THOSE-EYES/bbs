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

#include "sys/tools/compilers/gnuplusplus.hpp" // FIXME: Will be hardcoded untill !cmplr keyword is introduced
#include "exceptions/filenotfoundexception.hpp"
#include "scheduler/exceptions/linkerrorexception.hpp"
#include "scheduler/exceptions/nofilesspecifiedexception.hpp"
#include "scheduler/exceptions/postcompilationcommandexception.hpp"
#include "scheduler/exceptions/precompilationcommandexception.hpp"
#include "sys/tools/compilerfactory.hpp"

namespace scheduler::pipeline
{
Pipeline::Pipeline(Job job)
	: job_{std::move(job)}
{
	using namespace sys::tools;
	using namespace sys::tools::compilers;

	compiler_ =
		std::move(CompilerFactory::Create(GNUPlusPlus::kCompiler, job_.GetCompilationFlags()));
}

void Pipeline::Run() const
{
	// Create the directory for the output
	const std::filesystem::path folder{job_.GetProjectName()};
	std::filesystem::create_directory(folder);

	// Execute pre-compilation commands
	for(const auto& line : job_.GetPreCompilationCommands())
	{
		Command command{line};
		if(command.Execute())
		{
			throw exceptions::PreCompilationCommandException(line);
		}
	}

	// Check if the project contains files
	const auto& files = job_.GetFiles();
	if(files.empty())
	{
		throw exceptions::NoFilesSpecifiedException();
	}

	std::stringstream parameters{};
	for(const auto& file : files)
	{
		// Check if the specified file exists
		if(!std::filesystem::exists(file))
		{
			throw ::exceptions::FileNotFoundException(file);
		}

		const auto obj = folder / file.filename().replace_extension(".o");

		// Add the object file name to the list of parameters
		parameters << std::move(obj.string()) << " ";

		compiler_->Compile(job_.GetProjectPath() / file, obj);
	}

	// Set the name of the executable
	parameters << "-o" << (folder / job_.GetProjectName()).string();

	// Link all the object files into the executable
	Command command{sys::tools::compilers::GNUPlusPlus::kCompiler, parameters.str()};
	if(!command.Execute())
	{
		throw exceptions::LinkErrorException(job_.GetProjectName());
	}

	// Execute post-compilation commands
	for(const auto& line : job_.GetPostCompilationCommands())
	{
		Command command{line};
		if(command.Execute())
		{
			throw exceptions::PostCompilationCommandException(line);
		}
	}
}
} // namespace scheduler::pipeline