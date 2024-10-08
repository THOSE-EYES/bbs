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

#include <memory>

#include "lexer/context.hpp"
#include "lexer/lexer.hpp"
#include "parser/mediator.hpp"
#include "parser/states/state.hpp"

namespace parser
{
/**
 * @brief The class is used to process the tokens, found by lexer
 * 
 */
class Parser
{
public:
	/**
     * @brief Construct a new Parser object
     * 
     * @param path - the path to the file to scan
     */
	explicit Parser(const std::filesystem::path& path);

public:
	/**
      * @brief Get the current context
      * 
      * @return const Context& - a reference to the context instance
      */
	const lexer::Context& GetContext() const;

	/**
     * @brief Process the given script
     *
     * @return A filled job instance
     */
	scheduler::pipeline::Job Process();

protected:
	/**
     * @brief The lexer to use to process the script
     * 
     */
	lexer::Lexer lexer_;

	/**
      * @brief The object used to reduce dependencies between the parser and it's states
      * 
      */
	Mediator mediator_;
};
} // namespace parser