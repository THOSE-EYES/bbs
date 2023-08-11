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

#include <ctime>
#include <iomanip>

namespace utils
{
std::ofstream Logger::stream_{};
std::mutex Logger::mutex_;
Logger::LogLevel Logger::minimum_log_level_{LogLevel::kDebug};

void Logger::SetFile(std::string file)
{
	std::lock_guard<std::mutex> lock{mutex_};

	// If the previous file was opened, close it
	if(stream_.is_open())
	{
		stream_.close();
	}

	stream_.open(file);
	if(!stream_.is_open())
	{
		return;
	}
}

void Logger::SetMinimumLogLevel(LogLevel level)
{
	minimum_log_level_ = level;
}

Logger Logger::GetInstance(std::string component_name)
{
	return std::move(Logger(component_name));
}

void Logger::Close()
{
	// Don't do anything if the stream is already closed
	if(!stream_.is_open())
	{
		return;
	}

	stream_.close();
}

void Logger::Log(LogLevel level, std::string message)
{
	// Don't add the entry, if it's level is less than minimum
	if(level < minimum_log_level_ || !stream_.is_open())
	{
		return;
	}

	std::lock_guard<std::mutex> lock{mutex_};

	// Get the current time
	auto time = std::time(nullptr);
	auto local_time = *std::localtime(&time);

	// Put the log entry into the file
	stream_ << std::put_time(&local_time, "%d.%m.%Y %H:%M:%S") << " [" << component_name_ << "] "
			<< message << std::endl
			<< std::flush;
}

Logger::Logger(std::string component_name)
	: component_name_{component_name}
{}
} // namespace utils