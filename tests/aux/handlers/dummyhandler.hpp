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
#include <vector>

#include "parser/lexer/handlers/handler.hpp"
#include "parser/tokens/token.hpp"

namespace handlers
{
/**
 * @brief A dummy handler that returns the next token from the given vector
 * 
 */
class DummyHandler : public ::parser::lexer::handlers::Handler
{
	using Token = parser::tokens::Token;
	using Tokens = std::vector<std::unique_ptr<Token>>;

public:
	/**
	 * @brief Construct a new DummyHandler object
	 * 
	 * @param tokens - the tokens to return after "processing"
	 */
	DummyHandler(Tokens tokens)
		: tokens_{std::move(tokens)}
		, iterator_{tokens_.begin()}
	{}

public:
	/**
	 * @brief Process the input and return the token if possible
	 * 
	 * @param scanner - the source of characters to process
	 * @return std::unique_ptr<Token> - a pointer to the token or nullptr 
	 */
	std::unique_ptr<Token> Process(::parser::lexer::Scanner& scanner) const override
	{
		if(iterator_ == tokens_.end())
		{
			return {};
		}

		// Get the data and advance the iterator
		auto token = std::move(*iterator_);
		iterator_++;

		return token;
	}

protected:
	/**
	 * @brief A vector of tokens to return
	 * 
	 */
	Tokens tokens_;

	/**
	 * @brief An iterator, pointing to the position of the next token to read
	 * 
	 */
	mutable Tokens::iterator iterator_;
};
} // namespace handlers