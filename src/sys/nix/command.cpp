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

#include "sys/nix/command.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>

namespace sys::nix
{
Command::Command(std::string line)
	: command_{line}
{}

Command::Command(std::string program, std::string parameters)
	: command_{std::move(program + " " + parameters)}
{}

bool Command::Execute()
{
	auto pipe = popen(command_.c_str(), "r");
	if(!pipe)
	{
		return false;
	}

	std::array<char, 128> buffer;
	while(fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr)
	{
		output_ += buffer.data();
	}

	return pclose(pipe) == 0;
}

std::string Command::GetOutput() const
{
	return output_;
}
} // namespace sys::nix