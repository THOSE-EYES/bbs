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

namespace scheduler::pipeline
{
/**
 * @brief A structure that holds information about the job to be done
 * 
 */
class Job
{
public:
	/**
	 * @brief Construct a new Job object
	 * 
	 * @param name - the name of the job
	 */
	Job(std::string name);

	/**
	 * @brief Construct a new Job object
	 * 
	 * @param other - the object to move data from
	 */
	Job(Job&& other) noexcept;

	/**
	 * @brief Deleted copy constructor of a new Job object
	 * 
	 */
	Job(const Job&) = delete;

	/**
	 * @brief Deleted copy assignment operator
	 * 
	 * @return const Job& - another instance of the job
	 */
	Job& operator=(const Job&) = delete;

public:
	/**
	 * @brief Get the project's name
	 * 
	 * @return const std::string& - the name of the project
	 */
	const std::string& GetProjectName() const;

	/**
	 * @brief Set the project path
	 * 
	 * @param value - the path to the project
	 */
	void SetProjectPath(std::filesystem::path value);

	/**
	 * @brief Get the project's path
	 * 
	 * @return std::filesystem::path& - the path to the project
	 */
	const std::filesystem::path& GetProjectPath() const;

	/**
	 * @brief Add a new file to the job
	 * 
	 * @param value - add the file
	 */
	void AddFile(std::filesystem::path value);

	/**
	 * @brief Get the files the job contains
	 * 
	 * @return std::vector<std::filesystem::path>& - the files the job contains
	 */
	const std::vector<std::filesystem::path>& GetFiles() const;

	/**
	 * @brief Add a new dependency to the job
	 * 
	 * @param value - add the dependency
	 */
	void AddDependency(std::filesystem::path value);

	/**
	 * @brief Get the files the job contains
	 * 
	 * @return std::vector<std::filesystem::path>& - the files the job contains
	 */
	const std::vector<std::filesystem::path>& GetDependencies() const;

	/**
	 * @brief Set the compilation flags
	 * 
	 * @param value - the flags
	 */
	void SetCompilationFlags(std::string value);

	/**
	 * @brief Get the compilation flags
	 * 
	 * @return const std::string& - the value of the flags
	 */
	const std::string& GetCompilationFlags() const;

protected:
	/**
	 * @brief Job's name
	 * 
	 */
	const std::string name_;

	/**
	 * @brief The project's path
	 * 
	 */
	std::filesystem::path path_;

	/**
	 * @brief The list of files the job contains
	 * 
	 */
	std::vector<std::filesystem::path> files_;

	/**
	 * @brief The list of dependencies the job contains
	 * 
	 */
	std::vector<std::filesystem::path> dependencies_;

	/**
	 * @brief Compilation flags
	 * 
	 */
	std::string cflags_;
};
} // namespace scheduler::pipeline