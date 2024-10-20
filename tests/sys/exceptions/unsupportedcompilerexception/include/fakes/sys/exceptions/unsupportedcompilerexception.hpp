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

#pragma once

#include "sys/exceptions/unsupportedcompilerexception.hpp"

namespace fakes::sys::exceptions
{
/**
 * @brief A fake for the exception, used to notify that the specified compiler is not supported
 * 
 */
class UnsupportedCompilerException : public ::sys::exceptions::UnsupportedCompilerException
{
public:
	/**
	 * @brief Construct a new UnsupportedCompilerException object
	 * 
	 * @param project - the project that caused the error
	 */
	explicit UnsupportedCompilerException(std::string project)
		: ::sys::exceptions::UnsupportedCompilerException{project}
	{}

public:
	using ::sys::exceptions::UnsupportedCompilerException::kMessage;
};
} // namespace fakes::sys::exceptions