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

#include "parser/states/keywords/deps.hpp"

#include "parser/states/statement.hpp"

namespace parser::states::keywords
{
Deps::Deps(Mediator& mediator)
	: Array{mediator}
{}

void Deps::Process(lexer::Lexer& lexer)
{
	Array::Process(lexer);

	// Set the job's files
	auto& job = mediator_.BorrowJob();
	for(auto& name : Array::GetValue())
	{
		job.AddDependency(std::filesystem::path{name});
	}

	// Return to the Statement state
	mediator_.SetState(std::make_unique<Statement>(mediator_));
}
} // namespace parser::states::keywords