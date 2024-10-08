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

#include "application.hpp"

#include <iostream>

#include "parser/parser.hpp"
#include "scheduler/pipeline/job.hpp"

const static std::string kBuildFile = "build.bbs";

void Application::Process(std::filesystem::path path)
{
	parser::Parser parser{path / kBuildFile};
	try
	{
		auto job = parser.Process();
		job.SetProjectPath(path);

		// Process dependencies
		for(const auto& dependency : job.GetDependencies())
		{
			Process(path / dependency);
		}

		// Create a new pipeline to build the project
		scheduler::pipeline::Pipeline pipeline{std::move(job)};
		executor_.Add(std::move(pipeline));
	}
	catch(const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return;
	}
}

void Application::Build()
{
	executor_.Run();
}
