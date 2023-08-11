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

#include "utils/logger.hpp"

namespace fakes::utils
{
/**
 * @brief The class is used to fake the Logger and give access to it's protected fields.
 * 
 */
class Logger : public ::utils::Logger
{
public:
	/**
	 * @brief Construct a new FakeLogger object
	 * 
	 * @param component_name the name of the component to use
	 */
	Logger(std::string component_name)
		: ::utils::Logger{component_name}
	{}

public:
	using ::utils::Logger::component_name_;
	using ::utils::Logger::minimum_log_level_;
	using ::utils::Logger::mutex_;
	using ::utils::Logger::stream_;
};
} // namespace fakes::utils