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
#include "parser/lexer/exceptions/fileemptyexception.hpp"
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
			FAIL() << "The node " << kFilePath << " is not a regular file.";
		}

		file.open(kFilePath, std::ofstream::trunc);
		if(!file.is_open())
		{
			FAIL() << "Couldn't open the file " << kFilePath << ".";
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
 * @brief Check if the constructor throws an exception if the there is a directory with the same name as the file's to parse
 * 
 */
TEST(ScannerTestNoFixture, TestConstructorDirectory)
{
	const std::string name{"folder"};

	// Create a new directory
	fs::create_directory(name);

	EXPECT_THROW(fake::Scanner instance{name}, original::exceptions::FileNotFoundException);

	// Remove the directory
	fs::remove(name);
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

	fake::Scanner instance{kFilePath};
	EXPECT_EQ(instance.GetContext().GetLine(), data);
	EXPECT_EQ(instance.GetContext().GetCharacter().value(), data.at(0));
}

/**
 * @brief Check if the parser's constructor doesn't throw any exceptions if the file is empty
 * 
 */
TEST_F(ScannerTest, TestConstructorEmptyFile)
{
	EXPECT_THROW(fake::Scanner instance{kFilePath}, original::exceptions::FileEmptyException);
}

/**
 * @brief Check if the Scanner component skips whitespaces
 * 
 */
TEST_F(ScannerTest, TestGetWhitespacePrefix)
{
	const std::string data{"Hello World!"};

	// Write some test data to the file with a tab prefix
	file << std::string(10, ' ') << data << std::endl;

	fake::Scanner instance{kFilePath};
	EXPECT_EQ(instance.Get(), data.at(0));
}

/**
 * @brief Check if the Scanner component skips tabs
 * 
 */
TEST_F(ScannerTest, TestGetTabPrefix)
{
	const std::string data{"Hello World!"};

	// Write some test data to the file with a whitespace prefix
	file << std::string(10, '\t') << data << std::endl;

	fake::Scanner instance{kFilePath};
	EXPECT_EQ(instance.Get(), data.at(0));
}

/**
 * @brief Check if the Scanner component reads the next line if it is the end of the current line
 * 
 */
TEST_F(ScannerTest, TestGetNewLine)
{
	const std::string data{"Hello World!"};

	// Write some test data after an empty line
	file << std::endl << data << std::endl;

	fake::Scanner instance{kFilePath};
	EXPECT_EQ(instance.Get(), data.at(0));
	EXPECT_EQ(instance.GetContext().GetLine(), data);
}

/**
 * @brief Check if the Scanner component reads the next line if it sees a comment
 * 
 */
TEST_F(ScannerTest, TestGetСomment)
{
	const std::string data{"Hello World!"};

	// Write some test data after an empty line
	file << "# Goodbye World" << std::endl << data << std::endl;

	fake::Scanner instance{kFilePath};
	EXPECT_EQ(instance.Get(), data.at(0));
	EXPECT_EQ(instance.GetContext().GetLine(), data);
}

/**
 * @brief Check if the Scanner component exits successfull after trying to read past the end of the file
 * 
 */
TEST_F(ScannerTest, TestGetEndOfFileSymbol)
{
	// Write some test data after an empty line
	file << 'a' << std::flush;

	fake::Scanner instance{kFilePath};

	// Skip the character as it is not important
	instance.Move();

	EXPECT_FALSE(instance.Get());
}

/**
 * @brief Check if the Scanner component exits successfull after trying to read past the end of the file
 * 
 */
TEST_F(ScannerTest, TestMoveEndOfFileSymbol)
{
	// Write some test data after an empty line
	file << 'a' << std::flush;

	fake::Scanner instance{kFilePath};

	// Skip the character as it is not important
	instance.Move();

	EXPECT_FALSE(instance.Get());
}

/**
 * @brief Check if the Scanner component exits successfull after trying to read past the end of the file
 * 
 */
TEST_F(ScannerTest, TestGetContext)
{
	const std::string data{"Hello World!"};

	// Write some test data after an empty line
	file << "# Goodbye World" << std::endl << data << std::endl;

	fake::Scanner instance{kFilePath};
	const auto context = instance.GetContext();
	EXPECT_EQ(context.GetLine(), data);
	EXPECT_EQ(context.GetLineIndex(), 2);
}