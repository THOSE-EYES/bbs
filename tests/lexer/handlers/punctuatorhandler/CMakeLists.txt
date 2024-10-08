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

project("punctuatorhandler")

set(SOURCES 
    ${CMAKE_SOURCE_DIR}/src/lexer/handlers/punctuatorhandler.cpp
)

set(STUBS
    ${STUBS_FOLDER}/lexer/exceptions/fileemptyexception.cpp
    ${STUBS_FOLDER}/lexer/exceptions/filenotfoundexception.cpp
    ${STUBS_FOLDER}/lexer/exceptions/unexpectedlexemeexception.cpp
    ${STUBS_FOLDER}/lexer/context.cpp

    src/stubs/lexer/handlers/handler.cpp
    src/stubs/lexer/scanner.cpp
    src/stubs/parser/tokens/token.cpp
    src/stubs/parser/tokens/punctuator.cpp
)

add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${STUBS}

    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME} 
    gmock
    gmock_main
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})