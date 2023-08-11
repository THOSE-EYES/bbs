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

#include "utils/bufferedlogger.hpp"

#include <ctime>
#include <iomanip>

namespace utils
{
BufferedLogger BufferedLogger::GetInstance(std::string component_name)
{
	return std::move(BufferedLogger(component_name));
}

void BufferedLogger::SetBufferLogLevel(LogLevel level)
{
	buffer_log_level_ = level;
}

void BufferedLogger::Append(std::string message)
{
	// Append the message to the current buffer
	buffer_ += message;
}

void BufferedLogger::Flush()
{
	Log(buffer_log_level_, buffer_);

	// Clear the buffer and the current log level
	buffer_.clear();
	buffer_log_level_ = LogLevel::kInfo;
}

BufferedLogger::BufferedLogger(std::string component_name)
	: Logger{component_name}
{}

BufferedLogger& operator<<(BufferedLogger& logger, BufferedLogger::LogLevel value)
{
	logger.SetBufferLogLevel(value);
	return logger;
}

BufferedLogger& operator<<(BufferedLogger& logger, std::string value)
{
	logger.Append(value);
	return logger;
}

BufferedLogger& operator<<(BufferedLogger& logger, int value)
{
	logger.Append(std::to_string(value));
	return logger;
}

BufferedLogger& operator<<(BufferedLogger& logger, std::function<void(BufferedLogger&)> func)
{
	func(logger);
	return logger;
}

void End(BufferedLogger& logger)
{
	logger.Flush();
}
} // namespace utils