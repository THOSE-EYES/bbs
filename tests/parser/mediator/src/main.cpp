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

#include "parser/exceptions/existingprojectexception.hpp"
#include "parser/exceptions/nonexistentprojectexception.hpp"
#include "parser/exceptions/undeclaredvariableexception.hpp"
#include "parser/mediator.hpp"
#include "parser/states/state.hpp"

/**
 * @brief A text fixture to test parser::MediatorTest component
 * 
 */
class MediatorTest : public ::testing::Test
{
protected:
	/**
	 * @brief The instance to test
	 * 
	 */
	parser::Mediator instance_{};
};

/**
 * @brief Check if the SetState() method works properly
 * 
 */
TEST_F(MediatorTest, TestSetState)
{
	instance_.SetState({});
	EXPECT_FALSE(instance_.GetState());
}

/**
 * @brief Check if SetJob() throws an exception if the job already exists
 * 
 */
TEST_F(MediatorTest, TestSetJobExistingProjectException)
{
	instance_.SetJob(std::make_unique<scheduler::pipeline::Job>(""));
	EXPECT_THROW(instance_.SetJob(std::make_unique<scheduler::pipeline::Job>("")),
				 parser::exceptions::ExistingProjectException);
}

/**
 * @brief Check if GetJob() returns the job instance if it exists
 * 
 */
TEST_F(MediatorTest, TestGetJobSuccess)
{
	instance_.SetJob(std::make_unique<scheduler::pipeline::Job>(""));
	EXPECT_NO_THROW(instance_.GetJob());
}

/**
 * @brief Check if the GetJob() method throws an exception if the instance does not exist
 * 
 */
TEST_F(MediatorTest, TestGetJobNonExistentProjectException)
{
	instance_.SetJob({});
	EXPECT_THROW(instance_.GetJob(), parser::exceptions::NonExistentProjectException);
}

/**
 * @brief Check if BorrowJob() returns the job instance if it exists
 * 
 */
TEST_F(MediatorTest, TestBorrowJobSuccess)
{
	instance_.SetJob(std::make_unique<scheduler::pipeline::Job>(""));
	EXPECT_NO_THROW(instance_.BorrowJob());
}

/**
 * @brief Check if the BorrowJob() method throws an exception if the instance does not exist
 * 
 */
TEST_F(MediatorTest, TestBorrowJobNonExistentProjectException)
{
	instance_.SetJob({});
	EXPECT_THROW(instance_.BorrowJob(), parser::exceptions::NonExistentProjectException);
}

/**
 * @brief Check if the GetPostComGetVariableValuepilationCommands() method returns a proper value of the variable
 * 
 */
TEST_F(MediatorTest, TestGetVariableValueExists)
{
	const std::string id{"some_id"};
	const std::string value{"some_value"};
	instance_.DeclareVariable(id, value);

	EXPECT_EQ(instance_.GetVariableValue(id), value);
}

/**
 * @brief Check if the GetPostComGetVariableValuepilationCommands() method throws an exception if the variable does not exist
 * 
 */
TEST_F(MediatorTest, TestGetVariableValueNotFound)
{
	const std::string id{"some_id"};
	EXPECT_THROW(instance_.GetVariableValue(id), parser::exceptions::UndeclaredVariableException);
}