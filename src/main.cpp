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

#include <filesystem>
#include <iostream>

#include "application.hpp"

static const std::string help{"Usage: bbs [PATH]\n"
							  "Builds the project, specified by the PATH\n"};

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cout << help << std::endl;
		return 1;
	}

	if(argv[1] == "--help")
	{
		std::cout << help << std::endl;
		return 0;
	}

	// Get the path to the main build file
	std::filesystem::path path{argv[1]};

	// Process the files and build the project
	Application application;
	application.Process(path);
	application.Build();

	return 0;
}