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

#include "utils/logger.hpp"

namespace utils
{
std::ofstream Logger::stream_{};
std::mutex Logger::mutex_;
Logger::LogLevel Logger::minimum_log_level_{};

void Logger::SetFile(std::string_view file) {}

void Logger::SetMinimumLogLevel(LogLevel level) noexcept {}

Logger Logger::GetInstance(std::string_view component_name)
{
	return std::move(Logger(component_name));
}

void Logger::Log(LogLevel level, std::string_view message) const {}

Logger::Logger(std::string_view component_name)
	: component_name_{component_name}
{}
} // namespace utils