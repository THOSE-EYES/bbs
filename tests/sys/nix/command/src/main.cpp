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

#include "fakes/sys/nix/command.hpp"

/**
 * @brief Check if the constructor poperly fills all the fields
 * 
 */
TEST(CommandTest, TestConstructor)
{
	const std::string program{"program"};
	const std::string parameters{"program"};
	const fakes::sys::nix::Command command{program, parameters};

	EXPECT_EQ(command.command_, program + " " + parameters);
}

/**
 * @brief Check if baasic OS commands are executed successfully
 * 
 */
TEST(CommandTest, TestExecuteSuccess)
{
	fakes::sys::nix::Command command{"echo", ""};
	EXPECT_TRUE(command.Execute());
}

/**
 * @brief Check if the command correctly fails when incorrect command is executed
 * 
 */
TEST(CommandTest, TestExecuteFail)
{
	fakes::sys::nix::Command command{"totally-existing-command", "some-parameters"};
	EXPECT_FALSE(command.Execute());
}