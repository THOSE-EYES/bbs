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
 * @brief A text fixture to test scheduler::pipeline::Job component
 * 
 */
class JobTest : public ::testing::Test
{
protected:
	/**
	 * @brief The instance to test
	 * 
	 */
	scheduler::pipeline::Job instance_{""};
};

/**
 * @brief Check if the contructor sets project's name
 * 
 */
TEST(JobTestNoFixture, TestConstructor)
{
	std::string name{"name"};
	scheduler::pipeline::Job job{name};
	EXPECT_EQ(job.GetProjectName(), name);
}

/**
 * @brief Check if the GetFiles() method returns a reference to the correctly filled vector
 * 
 */
TEST_F(JobTest, TestAddFile)
{
	const std::filesystem::path file{"some_file.txt"};
	instance_.AddFile(file);

	const auto& files = instance_.GetFiles();
	EXPECT_EQ(files.size(), 1);
	EXPECT_EQ(files.at(0), file);
}

/**
 * @brief Check if the SetCompilationFlags() method correctly sets the flags
 * 
 */
TEST_F(JobTest, TestSetCompilationFlags)
{
	const std::string flags{"flags"};
	instance_.SetCompilationFlags(flags);

	EXPECT_EQ(instance_.GetCompilationFlags(), flags);
}

/**
 * @brief Check if the GetDependencies() method returns a reference to the correctly filled vector
 * 
 */
TEST_F(JobTest, TestAddDependency)
{
	const std::filesystem::path path{"some_path"};
	instance_.AddDependency(path);

	const auto& dependencies = instance_.GetDependencies();
	EXPECT_EQ(dependencies.size(), 1);
	EXPECT_EQ(dependencies.at(0), path);
}

/**
 * @brief Check if the SetProjectPath() method correctly sets the project's path
 * 
 */
TEST_F(JobTest, TestSetProjectPath)
{
	const std::filesystem::path path{"some_path"};
	instance_.SetProjectPath(path);

	EXPECT_EQ(instance_.GetProjectPath(), path);
}

/**
 * @brief Check if the GetPreCompilationCommands() method returns a reference to the correctly filled vector
 * 
 */
TEST_F(JobTest, TestSetPreCompilationCommands)
{
	const std::vector<std::string> commands{"some_command"};
	instance_.SetPreCompilationCommands(commands);

	EXPECT_EQ(instance_.GetPreCompilationCommands(), commands);
}

/**
 * @brief Check if the GetPostCompilationCommands() method returns a reference to the correctly filled vector
 * 
 */
TEST_F(JobTest, TestSetPostCompilationCommands)
{
	const std::vector<std::string> commands{"some_command"};
	instance_.SetPostCompilationCommands(commands);

	EXPECT_EQ(instance_.GetPostCompilationCommands(), commands);
}

/**
 * @brief Check if the GetIncludeDirectories() method returns a reference to the correctly filled vector
 * 
 */
TEST_F(JobTest, TestAddIncludeDirectory)
{
	const std::filesystem::path path{"some_path"};
	instance_.AddIncludeDirectory(path);

	EXPECT_EQ(instance_.GetIncludeDirectories().at(0), path);
}