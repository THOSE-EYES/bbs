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

#include "lexer/handlers/handler.hpp"

#include "lexer/exceptions/unexpectedlexemeexception.hpp"

namespace lexer::handlers
{
std::unique_ptr<Handler::Token> Handler::Process(Scanner& scanner) const
{
	return {};
}

void Handler::SetNext(std::unique_ptr<Handler> next)
{
	next_ = std::move(next);
}
} // namespace lexer::handlers