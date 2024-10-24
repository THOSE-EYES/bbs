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

#include "sys/tools/compilerfactory.hpp"

#include "sys/exceptions/unsupportedcompilerexception.hpp"
#include "sys/tools/compilers/gnuplusplus.hpp"

namespace sys::tools
{
std::unique_ptr<Compiler>
CompilerFactory::Create(const std::string& value,
						std::string flags,
						std::vector<std::filesystem::path> include_directories)
{
	return std::unique_ptr<Compiler>{
		new compilers::GNUPlusPlus(std::move(flags), std::move(include_directories))};
}
} // namespace sys::tools