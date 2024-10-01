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

#include "scheduler/exceptions/linkerrorexception.hpp"

bool is_faulty = false;

namespace scheduler::pipeline
{
Pipeline::Pipeline(Job job)
	: job_{std::move(job)}
{}

void Pipeline::Run() const
{
	if(is_faulty)
	{
		throw exceptions::LinkErrorException("");
	}
}

void Pipeline::Compile(const std::filesystem::path& file) const
{
	// noop
}
} // namespace scheduler::pipeline