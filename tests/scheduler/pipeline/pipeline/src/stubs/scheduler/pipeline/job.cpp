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

#include "scheduler/pipeline/job.hpp"

namespace scheduler::pipeline
{
Job::Job(std::string name)
	: name_{std::move(name)}
{
	//noop
}

const std::string& Job::GetProjectName() const
{
	return name_;
}

void Job::SetProjectPath(std::filesystem::path value)
{
	path_ = std::move(value);
}

const std::filesystem::path& Job::GetProjectPath() const
{
	return path_;
}

void Job::AddFile(std::filesystem::path value)
{
	files_.push_back(std::move(value));
}

const std::vector<std::filesystem::path>& Job::GetFiles() const
{
	return files_;
}

void Job::AddDependency(std::filesystem::path value)
{
	// noop
}

const std::vector<std::filesystem::path>& Job::GetDependencies() const
{
	return dependencies_;
}

void Job::SetCompilationFlags(std::string value)
{
	cflags_ = std::move(value);
}

const std::string& Job::GetCompilationFlags() const
{
	return cflags_;
}

void Job::SetPreCompilationCommands(std::vector<std::string> value)
{
	pre_commands_ = std::move(value);
}

const std::vector<std::string>& Job::GetPreCompilationCommands() const
{
	return pre_commands_;
}

void Job::SetPostCompilationCommands(std::vector<std::string> value)
{
	post_commands_ = std::move(value);
}

const std::vector<std::string>& Job::GetPostCompilationCommands() const
{
	return post_commands_;
}

void Job::AddIncludeDirectory(std::filesystem::path value)
{
	include_directories_.push_back(std::move(value));
}

const std::vector<std::filesystem::path>& Job::GetIncludeDirectories() const
{
	return include_directories_;
}
} // namespace scheduler::pipeline