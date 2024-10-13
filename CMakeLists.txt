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
    src/lexer/exceptions/fileemptyexception.cpp
    src/lexer/exceptions/filenotfoundexception.cpp
    src/lexer/exceptions/unexpectedlexemeexception.cpp
    src/lexer/handlers/handler.cpp
    src/lexer/handlers/wordhandler.cpp
    src/lexer/handlers/punctuatorhandler.cpp
    src/lexer/context.cpp
    src/lexer/lexer.cpp
    src/lexer/scanner.cpp
    src/parser/exceptions/existingprojectexception.cpp
    src/parser/exceptions/nonexistentprojectexception.cpp
    src/parser/exceptions/unexpectedendoffileexception.cpp
    src/parser/exceptions/unexpectedkeywordexception.cpp
    src/parser/exceptions/unexpectedtokenexception.cpp
    src/parser/states/keywords/cflags.cpp
    src/parser/states/keywords/deps.cpp
    src/parser/states/keywords/files.cpp
    src/parser/states/keywords/post.cpp
    src/parser/states/keywords/pre.cpp
    src/parser/states/keywords/project.cpp
    src/parser/states/types/array.cpp
    src/parser/states/types/string.cpp
    src/parser/states/keyword.cpp
    src/parser/states/state.cpp
    src/parser/states/statement.cpp
    src/parser/tokens/punctuator.cpp
    src/parser/tokens/token.cpp
    src/parser/mediator.cpp
    src/parser/parser.cpp
    src/scheduler/exceptions/compilationerrorexception.cpp
    src/scheduler/exceptions/linkerrorexception.cpp
    src/scheduler/exceptions/precompilationcommandexception.cpp
    src/scheduler/pipeline/job.cpp
    src/scheduler/pipeline/pipeline.cpp
    src/scheduler/executor.cpp
    src/sys/nix/command.cpp
    src/utils/bufferedlogger.cpp
    src/utils/logger.cpp
    src/application.cpp
    src/main.cpp
)
