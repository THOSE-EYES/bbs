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

#include <stack>

#include "scheduler/exceptions/compilationerrorexception.hpp"
#include "scheduler/exceptions/linkerrorexception.hpp"
#include "scheduler/exceptions/nofilesspecifiedexception.hpp"
#include "scheduler/pipeline/job.hpp"
#include "scheduler/pipeline/pipeline.hpp"

extern std::stack<bool> result;

/**
 * @brief Check if the Run() method works correctly
 * 
 */
TEST(PipelineTest, TestRun)
{
	scheduler::pipeline::Job job{"test"};
	job.SetProjectPath(std::filesystem::path{"test"});
	job.AddFile(std::filesystem::path{"main.cpp"});

	scheduler::pipeline::Pipeline pipeline{std::move(job)};
	EXPECT_NO_THROW(pipeline.Run());
}

/**
 * @brief Check if the Run() method throws an exception when the compilation fails
 * 
 */
TEST(PipelineTest, TestCompileFail)
{
	scheduler::pipeline::Job job{"test"};
	job.SetProjectPath(std::filesystem::path{"test"});
	job.AddFile(std::filesystem::path{"main.cpp"});

	result.push(false);
	scheduler::pipeline::Pipeline pipeline{std::move(job)};
	EXPECT_THROW(pipeline.Run(), scheduler::exceptions::CompilationErrorException);
}

/**
 * @brief Check if the Run() method throws an exception when the linking fails
 * 
 */
TEST(PipelineTest, TestLinkFail)
{
	// Make the compilation "succeed"
	result.push(false);
	result.push(true);

	scheduler::pipeline::Job job{"test"};
	job.SetProjectPath(std::filesystem::path{"test"});
	job.AddFile(std::filesystem::path{"file"}); // Needed to do not cause NoFilesSpecifiedException

	scheduler::pipeline::Pipeline pipeline{std::move(job)};
	EXPECT_THROW(pipeline.Run(), scheduler::exceptions::LinkErrorException);
}

/**
 * @brief Check if the Run() method throws an exception when the there are no files
 * 
 */
TEST(PipelineTest, TestNoFilesFail)
{
	scheduler::pipeline::Job job{"test"};
	job.SetProjectPath(std::filesystem::path{"test"});

	scheduler::pipeline::Pipeline pipeline{std::move(job)};
	EXPECT_THROW(pipeline.Run(), scheduler::exceptions::NoFilesSpecifiedException);
}