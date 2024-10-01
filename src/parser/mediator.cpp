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

#include "parser/mediator.hpp"

#include "parser/exceptions/existingprojectexception.hpp"
#include "parser/exceptions/nonexistentprojectexception.hpp"
#include "parser/states/statement.hpp"

namespace parser
{
Mediator::Mediator()
	: state_{std::make_unique<states::Statement>(*this)}
{}

void Mediator::SetState(std::unique_ptr<states::State> state)
{
	state_ = std::move(state);
}

std::unique_ptr<states::State> Mediator::GetState()
{
	return std::move(state_);
}

void Mediator::SetJob(std::unique_ptr<scheduler::pipeline::Job> job)
{
	if(job_)
	{
		throw exceptions::ExistingProjectException(job_->GetProjectName());
	}

	job_ = std::move(job);
}

scheduler::pipeline::Job& Mediator::BorrowJob() const
{
	if(!job_)
	{
		throw exceptions::NonExistentProjectException();
	}
	return *job_;
}

scheduler::pipeline::Job Mediator::GetJob()
{
	if(!job_)
	{
		throw exceptions::NonExistentProjectException();
	}

	return std::move(*job_);
}
} // namespace parser