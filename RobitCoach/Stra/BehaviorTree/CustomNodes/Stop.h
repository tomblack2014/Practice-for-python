/*********************************************************************
*	@file		Stop.h
*	@brief		控制全体队员停止动作的分支
*
*
*	Date        Name        Description
*   19/06/15	TB			Creation
*
*********************************************************************/
#pragma once

#include <sstream>

#include "Stra/Common/Common.h"

#include "../Nodes.h"
#include "../CustomData.h"
#include "../LeafData.h"


namespace BehaviorTree {

	class Condition_IsStop : public Condition {
		virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			if (input.GetGameStatus() == GAME_STOP)
				return NODE_STATUS_SUCCEED;
			else
				return NODE_STATUS_FAILED;
		}
	};

	class Action_AllStop : public Action {
	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput&) override{}

		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			std::ostringstream oss;

			/*对所有队员发送停止指令*/
			for (auto & agent : input.GetAgents()){
				oss << "STOP" << ' '
					<< agent._ID << ' '
					<< '*' << ' ';
			}
			output.AddCMD(oss.str());
			oss.clear();

			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}

	};

}
