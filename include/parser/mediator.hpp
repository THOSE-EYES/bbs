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

#include "scheduler/pipeline/job.hpp"

namespace parser::states
{
class State;
}

namespace parser
{
class Mediator
{
public:
	/**
     * @brief Construct a new Mediator object
     * 
     */
	Mediator();

public:
	/**
     * @brief Set the new state
     * 
     * @param state - the state to set
     */
	void SetState(std::unique_ptr<states::State> state);

	/**
     * @brief Get the parser's state
     * 
     * @return std::unique_ptr<states::State> - current parser's state
     */
	std::unique_ptr<states::State> GetState();

	/**
      * @brief Set the job after it's creation
      * 
      * @param job - the job to use
      */
	void SetJob(std::unique_ptr<scheduler::pipeline::Job> job);

	/**
     * @brief Get reference to the job to make changes
     * 
     * @return scheduler::pipeline::Job& - a reference to the job sutable for updates
     */
	scheduler::pipeline::Job& BorrowJob() const;

	/**
     * @brief Get the internal job
     * 
     * @return scheduler::pipeline::Job - the internal job instance
     */
	scheduler::pipeline::Job GetJob();

	/**
	 * @brief Add a declaration of a variable to the job
	 * 
	 * @param id - variable's name
	 * @param value - variable's value
	 */
	void DeclareVariable(std::string id, std::string value);

	/**
	 * @brief Get the variable's value
	 * 
	 * @param id - variable's name
	 * @return std::string - the value of the variable, if it exists
	 */
	std::string GetVariableValue(std::string id) const;

protected:
	/**
     * @brief The current Parser's state
     * 
     */
	std::unique_ptr<states::State> state_;

	/**
      * @brief The job that is filled
      * 
      */
	std::unique_ptr<scheduler::pipeline::Job> job_;

	/**
	 * @brief The declared variables
	 * 
	 */
	std::map<std::string, std::string> variables_;
};
} // namespace parser