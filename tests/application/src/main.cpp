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

#include <filesystem>

#include "application.hpp"
#include "scheduler/exceptions/linkerrorexception.hpp"

extern bool is_faulty;

/**
 * @brief A text fixture to test ApplicationTest component
 * 
 */
class ApplicationTest : public ::testing::Test
{
protected:
	/**
	 * @brief The instance to test
	 * 
	 */
	Application instance_{};
};

/**
 * @brief Check if Process() method correctly works
 * 
 */
TEST_F(ApplicationTest, TestProcessSuccess)
{
	EXPECT_NO_THROW(instance_.Process(std::filesystem::path{""}));
}

/**
 * @brief Check if Process() method catches exceptions
 * 
 */
TEST_F(ApplicationTest, TestProcessExceptionCaught)
{
	is_faulty = true;

	EXPECT_NO_THROW(instance_.Process(std::filesystem::path{""}));

	// Restore the flag
	is_faulty = false;
}

/**
 * @brief Check if the Build() method correctly works
 * 
 */
TEST_F(ApplicationTest, TestBuildSuccess)
{
	EXPECT_NO_THROW(instance_.Build());
}
