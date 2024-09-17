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

project("tests")

set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS  "-O0 -fno-inline ${GCC_COVERAGE_COMPILE_FLAGS}")

# Add constants for folder access
set(FAKES_FOLDER "${PROJECT_SOURCE_DIR}/fakes")
set(STUBS_FOLDER "${PROJECT_SOURCE_DIR}/stubs")

# Add some definitions for accessing important folders from the code
add_compile_definitions(TESTS_FOLDER="${PROJECT_SOURCE_DIR}/")
add_compile_definitions(FILES_FOLDER="${PROJECT_SOURCE_DIR}/files/")

# Enable unit tests
enable_testing()

include_directories(
    ${PROJECT_SOURCE_DIR}
)

link_libraries(
    gtest
    gtest_main
    gcov
)

add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(utils)