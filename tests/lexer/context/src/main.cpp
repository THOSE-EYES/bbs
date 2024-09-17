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

#include "lexer/context.hpp"

/**
 * @brief Test fixture class for the Context component testing
 * 
 */
class ContextTest : public ::testing::Test
{
protected:
	/**
	 * @brief The instance to test
	 * 
	 */
	lexer::Context instance_;
};

/**
 * @brief Check if the GetLine() method correctly returns the current string
 * 
 */
TEST_F(ContextTest, TestGetLine)
{
	std::string data = "Hello World";
	instance_.Update(std::move(data));

	EXPECT_EQ(instance_.GetLine(), "Hello World");
}

/**
 * @brief Check if the GetCharacter() method correctly returns the current character
 * 
 */
TEST_F(ContextTest, TestGetCharacter)
{
	std::string data = "Hello World";
	instance_.Update(std::move(data));

	EXPECT_EQ(instance_.GetCharacter().value(), 'H');
}

/**
 * @brief Check if the GetCharacter() method returns std::nullopt, if the end of the line is achieved
 * 
 */
TEST_F(ContextTest, TestGetCharacterEmptyLine)
{
	instance_.Update(std::string());

	EXPECT_FALSE(instance_.GetCharacter());
}

/**
 * @brief Check if the Next() method moves the context's iterator to the next character
 * 
 */
TEST_F(ContextTest, TestNext)
{
	std::string data = "Hello World";
	instance_.Update(std::move(data));
	instance_.Next();

	EXPECT_EQ(instance_.GetCharacter().value(), 'e');
}

/**
 * @brief Check if the GetLineIndex() method returns the correct index of the line
 * 
 */
TEST_F(ContextTest, TestGetLineIndex)
{
	for(int i = 1; i < 10; ++i)
	{
		instance_.Update(std::string());

		EXPECT_EQ(instance_.GetLineIndex(), i);
	}
}

/**
 * @brief Check if the GetPosition() method returns the correct position inside the line
 * 
 */
TEST_F(ContextTest, TestGetPosition)
{
	std::string data = "Hello World";
	instance_.Update(std::move(data));
	instance_.Next();

	EXPECT_EQ(instance_.GetPosition(), 2);
}