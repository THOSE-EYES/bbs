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

#include "sys/exceptions/compilationerrorexception.hpp"
#include "sys/tools/compilers/gnuplusplus.hpp"

extern bool result;

/**
 * @brief Check if the compilation fails and throws an exception, if the system command returns false
 * 
 */
TEST(GNUPlusPlusTest, TestCompileFail)
{
	sys::tools::compilers::GNUPlusPlus compiler{""};

	result = false;
	const std::filesystem::path file{"main.cpp"};
	EXPECT_THROW(compiler.Compile(file, file), sys::exceptions::CompilationErrorException);

	result = true;
}

/**
 * @brief Check if the Compile() method doesn't throw any exception if the system command is run successfully
 * 
 */
TEST(GNUPlusPlusTest, TestCompileSuccess)
{
	sys::tools::compilers::GNUPlusPlus compiler{""};

	const std::filesystem::path file{"main.cpp"};
	EXPECT_NO_THROW(compiler.Compile(file, file));
}