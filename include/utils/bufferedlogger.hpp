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

#include <functional>

#include "utils/logger.hpp"

namespace utils
{
/**
 * @brief The class is used to store user-defined entries into the log file using stream operations
 * 
 */
class BufferedLogger : public Logger
{
public:
	/**
	 * @brief Get the instance of the logger for the specified component
	 * 
	 * @param component_name the name of the component to use
	 * @return the instance, which was created for the given component
	 */
	static BufferedLogger GetInstance(std::string component_name);

public:
	/**
	 * @brief Set the log level for the current buffered message
	 * 
	 * @param level the log level to use for the current message
	 */
	void SetBufferLogLevel(LogLevel level);

	/**
	 * @brief Append the given string to the buffer
	 * 
	 * @param message the string to append
	 */
	void Append(std::string message);

	/**
	 * @brief Flush the buffer, sending it's value to the log file as an entry
	 * 
	 */
	void Flush();

protected:
	/**
	 * @brief Construct a new BufferedLogger object
	 * 
	 * @param component_name the name of the component to use
	 */
	BufferedLogger(std::string component_name);

protected:
	/**
	 * @brief The buffer of entries for the stream operations
	 * 
	 */
	std::string buffer_;

	/**
	 * @brief The log level, set for the stream operations (until the Flush() operation)
	 * 
	 */
	LogLevel buffer_log_level_{LogLevel::kInfo};
};

/**
 * @brief Overloaded operator "<<" for stream operations on the logger for the log level
 * 
 * @param logger the logger to put the data into
 * @param value the value of the log level to use
 * @return the logger instance
 */
BufferedLogger& operator<<(BufferedLogger& logger, BufferedLogger::LogLevel value);

/**
 * @brief Overloaded operator "<<" for stream operations on the logger for strings
 * 
 * @param logger the logger to put the string into
 * @param value the value to put into the log entry
 * @return the logger instance
 */
BufferedLogger& operator<<(BufferedLogger& logger, std::string value);

/**
 * @brief Overloaded operator "<<" for stream operations on the logger for integers
 * 
 * @param logger the logger to put the integer into
 * @param value the value to put into the log entry
 * @return the logger instance
 */
BufferedLogger& operator<<(BufferedLogger& logger, int value);

/**
 * @brief Overloaded operator "<<" for stream operations on the logger for instance-manipulation functions
 * 
 * @param logger the logger instance to update
 * @param value the function to run on the logger instance
 * @return the logger instance
 */
BufferedLogger& operator<<(BufferedLogger& logger, std::function<void(BufferedLogger&)> func);

/**
 * @brief An std::endl equivalent for the logger
 * 
 * @param logger the logger instance to update
 */
void End(BufferedLogger& logger);
} // namespace utils