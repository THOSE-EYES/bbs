#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#

cmake_minimum_required(VERSION 3.0)

project("BBS")

include_directories(${PROJECT_NAME}
    include
)

# Check if it is desired to build the unit tests
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(tests)
endif()

add_executable(${PROJECT_NAME} 
    src/parser/lexer/exceptions/fileemptyexception.cpp
    src/parser/lexer/exceptions/filenotfoundexception.cpp
    src/parser/lexer/scanner.cpp
    src/utils/bufferedlogger.cpp
    src/utils/logger.cpp
    src/main.cpp
)
