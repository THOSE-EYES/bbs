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

#include <gtest/gtest.h>

#include "scheduler/pipeline/job.hpp"

/**
 * @brief Check if the contructor sets project's name
 * 
 */
TEST(JobTest, TestConstructor)
{
	std::string name{"name"};
	scheduler::pipeline::Job job{name};
	EXPECT_EQ(job.GetProjectName(), name);
}

/**
 * @brief Check if the AddFile() method returns a reference to the correctly filled vector
 * 
 */
TEST(JobTest, TestAddFile)
{
	const std::filesystem::path file{"some_file.txt"};
	scheduler::pipeline::Job job{"project"};
	job.AddFile(file);

	const auto& files = job.GetFiles();
	EXPECT_EQ(files.size(), 1);
	EXPECT_EQ(files.at(0), file);
}