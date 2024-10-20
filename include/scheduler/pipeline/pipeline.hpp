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
#include <queue>

#include "scheduler/pipeline/job.hpp"
#include "sys/tools/compiler.hpp"

namespace scheduler::pipeline
{
/**
 * @brief Pipeline implementation
 * 
 */
class Pipeline
{
public:
	/**
	 * @brief Construct a new Pipeline object
	 * 
	 * @param job - the associated job
	 */
	Pipeline(Job job);

	/**
	 * @brief Construct a new Pipeline object
	 * 
	 * @param other - the object to move data from
	 */
	Pipeline(Pipeline&& other) = default;

	/**
	 * @brief Deleted copy constructor of a new Pipeline object
	 * 
	 */
	Pipeline(const Pipeline&) = delete;

	/**
	 * @brief Deleted copy assignment operator
	 * 
	 * @return const Pipeline& - another instance of the pipeline
	 */
	Pipeline& operator=(const Pipeline&) = delete;

public:
	/**
	 * @brief Run the pipeline
	 * 
	 */
	void Run() const;

protected:
	/**
	 * @brief Compile the given file
	 * 
	 * @param file - the source file to compile
	 * @param out - the output
	 */
	void Compile(const std::filesystem::path& file, const std::filesystem::path& out) const;

protected:
	/**
	 * @brief The associated job
	 * 
	 */
	Job job_;

	/**
	 * @brief The compiler that is used in the pipeline
	 * 
	 */
	std::unique_ptr<sys::tools::Compiler> compiler_;
};
} // namespace scheduler::pipeline