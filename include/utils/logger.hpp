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

#include <fstream>
#include <mutex>
#include <string>

namespace utils
{
/**
 * @brief The class is used to store user-defined entries into the log file
 * 
 */
class Logger
{
public:
	/**
	 * @brief The log level, which is used when the global log level is set
	 * 
	 */
	enum class LogLevel
	{
		kDebug,
		kWarning,
		kError,
		kFatal,
		kInfo
	};

public:
	/**
	 * @brief Deleted copy constructor
	 * 
	 */
	Logger(const Logger&) = delete;

	/**
	 * @brief Deleted copy assignment operator
	 * 
	 */
	Logger& operator=(const Logger&) = delete;

	/**
	 * @brief Move constructor
	 * 
	 * @param rhs another instance to move data from
	 */
	Logger(Logger&& rhs) = default;

	/**
	 * @brief Move asssignment operator overloading
	 * 
	 * @param rhs another instance to move data from
	 * @return Logger& the updated instance with the new data
	 */
	Logger& operator=(Logger&& rhs) = default;

public:
	/**
	 * @brief Set the log file
	 * 
	 * @param file the name of the file to use
	 */
	static void SetFile(std::string file);

	/**
	 * @brief Set the minimum level for the logs
	 * 
	 * @param level the minumum level of the entry to be added to the file
	 */
	static void SetMinimumLogLevel(LogLevel level);

	/**
	 * @brief Get the instance of the logger for the specified component
	 * 
	 * @param component_name the name of the component to use
	 * @return the instance, which was created for the given component
	 */
	static Logger GetInstance(std::string component_name);

	/**
	 * @brief Close the stream, used for the logging
	 * 
	 */
	static void Close();

public:
	/**
	 * @brief Put the message into the log file
	 * 
	 * @param level the log level of the message
	 * @param message the message to log
	 */
	void Log(LogLevel level, std::string message);

protected:
	/**
	 * @brief Construct a new Logger object
	 * 
	 * @param component_name the name of the component to use
	 */
	explicit Logger(std::string component_name);

protected:
	/**
	 * @brief The file stream to log the messages into
	 * 
	 */
	static std::ofstream stream_;

	/**
	 * @brief The mutex which allows to do one thing at a time in this component
	 * 
	 */
	static std::mutex mutex_;

	/**
	 * @brief Minimum accepted log level
	 * 
	 */
	static LogLevel minimum_log_level_;

protected:
	/**
	 * @brief The name of the component, which is added to the message
	 * 
	 */
	const std::string component_name_;
};
} // namespace utils