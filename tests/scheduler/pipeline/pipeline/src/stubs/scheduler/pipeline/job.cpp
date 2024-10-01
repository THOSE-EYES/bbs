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
{
	//noop
}

Job::Job(Job&& other) noexcept
	: name_{std::move(other.name_)}
	, files_{std::move(other.files_)}
{
	//noop
}

const std::string& Job::GetProjectName() const
{
	return name_;
}

void Job::AddFile(std::filesystem::path value)
{
	files_.push_back(std::move(value));
}

const std::vector<std::filesystem::path>& Job::GetFiles() const
{
	return files_;
}
} // namespace scheduler::pipeline