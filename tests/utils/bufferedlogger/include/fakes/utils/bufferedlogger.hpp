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

#include "utils/bufferedlogger.hpp"

namespace fakes::utils
{
/**
 * @brief The class is used to fake the BufferedLogger and give access to it's protected fields
 * 
 */
class BufferedLogger : public ::utils::BufferedLogger
{
public:
	/**
	 * @brief Construct a new BufferedLogger object
	 * 
	 * @param component_name the name of the component to use
	 */
	BufferedLogger(std::string component_name)
		: ::utils::BufferedLogger{component_name}
	{}

public:
	using ::utils::BufferedLogger::buffer_;
	using ::utils::BufferedLogger::buffer_log_level_;
	using ::utils::BufferedLogger::component_name_;
	using ::utils::BufferedLogger::minimum_log_level_;
	using ::utils::BufferedLogger::mutex_;
	using ::utils::BufferedLogger::stream_;
};
} // namespace fakes::utils