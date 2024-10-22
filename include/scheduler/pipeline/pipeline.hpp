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
	 * @brief Run the compilation for the given files
	 * 
	 * @param folder - the folder where to store the output
	 * @param files - a vector of files
	 * @return std::vector<std::filesystem::path> - a vector of object files names
	 */
	std::vector<std::filesystem::path> Compile(const std::filesystem::path& folder,
											   std::vector<std::filesystem::path> files) const;

	/**
	 * @brief Link everything into one executable
	 * 
	 * @param folder - the folder where to put the executable
	 * @param files - the files to use
	 */
	void Link(const std::filesystem::path& folder, std::vector<std::filesystem::path> files) const;

	/**
	 * @brief Execute preprocessing commands
	 * 
	 */
	void ExecutePreprocessingCommands() const;

	/**
	 * @brief Execute postprocessing commands
	 * 
	 */
	void ExecutePostprocessingCommands() const;

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