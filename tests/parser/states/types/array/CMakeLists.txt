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

project("array")

set(SOURCES 
    ${CMAKE_SOURCE_DIR}/src/parser/states/types/array.cpp
)

set(STUBS
    ${STUBS_FOLDER}/lexer/handlers/handler.cpp
    ${STUBS_FOLDER}/lexer/scanner.cpp
    ${STUBS_FOLDER}/parser/exceptions/unexpectedendoffileexception.cpp
    ${STUBS_FOLDER}/parser/exceptions/unexpectedtokenexception.cpp
    ${STUBS_FOLDER}/parser/tokens/punctuator.cpp
    ${STUBS_FOLDER}/parser/tokens/separator.cpp
    ${STUBS_FOLDER}/parser/tokens/word.cpp
    ${STUBS_FOLDER}/parser/mediator.cpp
    ${STUBS_FOLDER}/parser/parser.cpp
    ${STUBS_FOLDER}/scheduler/pipeline/job.cpp

    src/stubs/lexer/lexer.cpp
    src/stubs/parser/states/types/string.cpp
    src/stubs/parser/states/state.cpp
)

add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${STUBS}

    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})