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

#include "sys/exceptions/unsupportedcompilerexception.hpp"
#include "sys/tools/compilerfactory.hpp"
#include "sys/tools/compilers/gnuplusplus.hpp"

/**
 * @brief Check if the GNU Compiler for C++ is recognized as a possible compiler to use
 * 
 */
TEST(CompilerFactoryTest, TestCreateGnuCompiler)
{
	const auto compiler = "g++";
	const std::vector<std::filesystem::path> include_directories{};
	const auto instance =
		sys::tools::CompilerFactory::Create(compiler, "", std::vector<std::filesystem::path>{});
	EXPECT_TRUE(dynamic_cast<sys::tools::compilers::GNUPlusPlus*>(instance.get()));
}

/**
 * @brief Check if the factory correctly throws an exception if the compiler was not recognized
 * 
 */
TEST(CompilerFactoryTest, TestCreateUnsupportedCompiler)
{
	const auto compiler = "some_unknown_compiler";
	EXPECT_THROW(
		sys::tools::CompilerFactory::Create(compiler, "", std::vector<std::filesystem::path>{}),
		sys::exceptions::UnsupportedCompilerException);
}