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

#include <filesystem>

#include <gtest/gtest.h>

#include "fakes/parser/lexer/scanner.hpp"
#include "parser/lexer/exceptions/filenotfoundexception.hpp"

namespace original = parser::lexer;
namespace fake = fakes::parser::lexer;
namespace fs = std::filesystem;

/**
 * @brief Test fixture class for the Scanner component testing
 * 
 */
class ScannerTest : public ::testing::Test
{
protected:
	/**
	 * @brief Set up the test fixture
	 * 
	 */
	void SetUp() override
	{
		if(fs::exists(kFilePath) && !fs::is_regular_file(kFilePath))
		{
			FAIL() << "The node " << kFilePath.string() << " is not a regular file.";
		}

		file.open(kFilePath, std::ofstream::trunc);
		if(!file.is_open())
		{
			FAIL() << "Couldn't open the file " << kFilePath.string() << ".";
		}
	}

	/**
	 * @brief Tear down the test fixture
	 * 
	 */
	void TearDown() override
	{
		file.close();
	}

protected:
	/**
	 * @brief The default file path, used by the test suite
	 * 
	 */
	static const fs::path kFilePath;

	/**
	 * @brief The test file handle
	 * 
	 */
	std::ofstream file;
};

const fs::path ScannerTest::kFilePath{"build.bbs"};

/**
 * @brief Check if the constructor throws an exception if the file is not found
 * 
 */
TEST(ScannerTestNoFixture, TestConstructorFileNotFound)
{
	const std::string filename{""};
	EXPECT_THROW(fake::Scanner instance{filename}, original::exceptions::FileNotFoundException);
}

/**
 * @brief Check if the constructor correctly reads the first line of the file
 * 
 */
TEST_F(ScannerTest, TestConstructorGetLine)
{
	const std::string data{"Hello World!"};

	// Write some test data to the file
	file << data << std::endl;

	fake::Scanner instance{kFilePath.string()};
	EXPECT_EQ(instance.line_, data);
	EXPECT_EQ(*instance.position_, data.at(0));
}

/**
 * @brief Check if the parser's constructor doesn't throw any exceptions if the file is empty
 * 
 */
TEST_F(ScannerTest, TestConstructorEmptyFile)
{
	fake::Scanner instance{kFilePath.string()};
	EXPECT_TRUE(instance.line_.empty());
	EXPECT_TRUE(instance.line_.empty());
}

/**
 * @brief Check if the parser doesn't throw any exceptions if the file is empty
 * 
 */
TEST_F(ScannerTest, TestNextEmptyFile)
{
	fake::Scanner instance{kFilePath.string()};
	EXPECT_FALSE(instance.Next());
}

/**
 * @brief Check if the Scanner component skips whitespaces
 * 
 */
TEST_F(ScannerTest, TestNextWhitespacePrefix)
{
	const std::string data{"Hello World!"};

	// Write some test data to the file with a tab prefix
	file << std::string(10, ' ') << data << std::endl;

	fake::Scanner instance{kFilePath.string()};
	EXPECT_EQ(instance.Next(), data.at(0));
}

/**
 * @brief Check if the Scanner component skips tabs
 * 
 */
TEST_F(ScannerTest, TestNextTabPrefix)
{
	const std::string data{"Hello World!"};

	// Write some test data to the file with a whitespace prefix
	file << std::string(10, '\t') << data << std::endl;

	fake::Scanner instance{kFilePath.string()};
	EXPECT_EQ(instance.Next(), data.at(0));
}

/**
 * @brief Check if the Scanner component reads the next line if it is the end of the current line
 * 
 */
TEST_F(ScannerTest, TestNextNewLine)
{
	const std::string data{"Hello World!"};

	// Write some test data after an empty line
	file << std::endl << data << std::endl;

	fake::Scanner instance{kFilePath.string()};
	EXPECT_EQ(instance.Next(), data.at(0));
	EXPECT_EQ(instance.line_, data);
}

/**
 * @brief Check if the Scanner component reads the next line if it sees a comment
 * 
 */
TEST_F(ScannerTest, TestNextСomment)
{
	const std::string data{"Hello World!"};

	// Write some test data after an empty line
	file << "# Goodbye World" << std::endl << data << std::endl;

	fake::Scanner instance{kFilePath.string()};
	EXPECT_EQ(instance.Next(), data.at(0));
	EXPECT_EQ(instance.line_, data);
}

/**
 * @brief Check if the Scanner component exits successfull after trying to read past the end of the file
 * 
 */
TEST_F(ScannerTest, TestNextEndOfFileSymbol)
{
	// Write some test data after an empty line
	file << 'a';

	fake::Scanner instance{kFilePath.string()};

	// Skip the character as it is not important
	instance.Next();

	EXPECT_FALSE(instance.Next());
}