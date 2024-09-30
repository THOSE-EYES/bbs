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

#include <string>

#include "sys/command.hpp"

namespace sys::nix
{
/**
 * @brief A UNIX-specific implementation for system command runner
 * 
 */
class Command : public ::sys::Command
{
public:
	/**
     * @brief Construct a new Command object
     * 
     * @param program - the program to run
     * @param parameters - the parameters to pass to the program
     */
	Command(std::string program, std::string parameters);

public:
	/**
     * @brief Execute the command
     * 
     * @return true if the command was run successfully, false otherwise
     */
	bool Execute() override;

protected:
	/**
     * @brief The program to run
     * 
     */
	std::string program_;

	/**
     * @brief The parameters to pass to the program
     * 
     */
	std::string parameters_;
};
} // namespace sys::nix