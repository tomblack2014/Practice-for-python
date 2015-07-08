/*********************************************************************
 *	@file		Kick.h
 *	@brief		行为树中，用于管理全部的开球
 *
 *
 *	Date        Name        Description
 *	15/04/15	MYLS		Creation.
 *	30/05/15	TB			Edit _Evaluator
 *
 *********************************************************************/

#pragma once

#include <sstream>  
#include <iostream>
#include <map>
#include <vector>
#include <functional>

#include "Stra/Common/Common.h"

#include "../Nodes.h"
#include "../CustomData.h"
#include "../LeafData.h"

#include "EvaluatorForKick.h"


namespace BehaviorTree {
	

	/************************************************
	 * 包含11种类型的开球(和对方开球):
	 * KickOff
	 * FreeKick
	 * GoalKick
	 * CornerKick
	 * ThrowIn
	 * AntiKickOff
	 * AntiFreeKick
	 * AntiGoalKick
	 * AntiCornerKick
	 * AntiThrowIn
	 * DropBall
	 ***********************************************/

	class Condition_IsKick : public Condition {

	private:

		virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			auto currentStatus = input.GetGameStatus();
			if (currentStatus == GAME_DROP_BALL
				|| currentStatus == GAME_KICK_OFF
				|| currentStatus == GAME_FREE_KICK
				|| currentStatus == GAME_GOAL_KICK
				|| currentStatus == GAME_CORNER_KICK
				|| currentStatus == GAME_THROW_IN
				|| currentStatus == GAME_ANTI_KICK_OFF
				|| currentStatus == GAME_ANTI_FREE_KICK
				|| currentStatus == GAME_ANTI_GOAL_KICK
				|| currentStatus == GAME_ANTI_CORNER_KICK
				|| currentStatus == GAME_ANTI_THROW_IN)
				return NODE_STATUS_SUCCEED;
			else
				return NODE_STATUS_FAILED;
		}

	};
	
	class Action_Kick_Assignment : public Action {
	public:

		Action_Kick_Assignment() : 
			_CurrentStatus(GAME_STOP),
			_Evaluator()
		{
			_Evaluator[GAME_KICK_OFF] = new KickOff();
			_Evaluator[GAME_CORNER_KICK] = new CornerKick();
			_Evaluator[GAME_FREE_KICK] = new FreeKick();
			_Evaluator[GAME_GOAL_KICK] = new GoalKick();
			_Evaluator[GAME_THROW_IN] = new ThrowIn();

			_Evaluator[GAME_ANTI_THROW_IN] = new AntiThrowIn();
			_Evaluator[GAME_ANTI_KICK_OFF] = new AntiKickOff();
			_Evaluator[GAME_ANTI_FREE_KICK] = new AntiFreeKick();
			_Evaluator[GAME_ANTI_GOAL_KICK] = new AntiGoalKick();
			_Evaluator[GAME_ANTI_CORNER_KICK] = new AntiCornerKick();

			_Evaluator[GAME_DROP_BALL] = new DropBall();
		};

		~Action_Kick_Assignment()
		{
			for (auto &it : _Evaluator) {
				delete it.second;
				it.second = nullptr;
			}
		}

	private:

		virtual void OnEnter
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			_CurrentStatus = input.GetGameStatus();
		}

		/* 它只返回Running(继续执行)或者Failed(退出这个分支) */
		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/* 检查状态是否改变 */
			if (input.GetGameStatus() != _CurrentStatus) {
				auto nextStatus = input.GetGameStatus();
				if (nextStatus == GAME_START) {
					/* 此时状态变更为 START，则根据上一帧的状态，修改为对应的状态 */
					if (_CurrentStatus == GAME_KICK_OFF
						|| _CurrentStatus == GAME_FREE_KICK
						|| _CurrentStatus == GAME_GOAL_KICK
						|| _CurrentStatus == GAME_CORNER_KICK
						|| _CurrentStatus == GAME_THROW_IN
						) {
						output.SetGameStatus(GAME_START_PASS);
					} else if(_CurrentStatus == GAME_ANTI_KICK_OFF
						|| _CurrentStatus == GAME_ANTI_FREE_KICK
						|| _CurrentStatus == GAME_ANTI_GOAL_KICK
						|| _CurrentStatus == GAME_ANTI_CORNER_KICK
						|| _CurrentStatus == GAME_ANTI_THROW_IN
						) {
						//对方开球的一些处理
						output.SetGameStatus(GAME_ANTI_START);
						;
					} else if (_CurrentStatus == GAME_DROP_BALL) {
						//针对DropBall的处理
						output.SetGameStatus(GAME_AUTO);
					}
				} else {
					// 被切换成其它状态，属于异常。
					output.SetGameStatus(GAME_AUTO);
				}

				/* 退出这个分支 */
				return NODE_STATUS_FAILED;
			}
			
			/* 状态没有改变, 开始维护任务分配 */
			const std::vector<Agent> & agents = input.GetAgents();
            const int n = static_cast<int>(agents.size());
			auto score = new int [n * n];

			/* 获取对应状态的任务分配评估函数 */
			auto evalutor = _Evaluator.find(_CurrentStatus);
			if (evalutor == _Evaluator.end()) {

				/*没有这个状态对应的操作*/
				std::cerr << "Kick::No such evaluator!" << std::endl;
				delete []score;
				return NODE_STATUS_FAILED;
			}

			for (int i = 0; i < n; i++) {
				for (int task = 0; task < n; task++) {
					score[i * n + task] = (evalutor->second)->Assignment(input, i, task);
				}
			}

			auto assignment = new int [n];
			Calculation::Kuhn_Munkres(score, n, assignment);
			delete []score;

			/* 尝试根据运算结果，进行任务调整 */
			for (int i = 0; i < n; i++)
				if (assignment[i] != i)
					output.SwapAgent(assignment[i], i);

			delete []assignment;

			/* 下一次继续维护 */
			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}

	private:

		GameStatus _CurrentStatus;
		std::map<GameStatus, EvaluatorForKick *> _Evaluator;
	};


	class Action_Kick_KeepInPosition : public Action {

	public:
		
		Action_Kick_KeepInPosition() :
			_Evaluator()
		{
			_Evaluator[GAME_KICK_OFF] = new KickOff();
			_Evaluator[GAME_FREE_KICK] = new FreeKick();
			_Evaluator[GAME_GOAL_KICK] = new GoalKick();
			_Evaluator[GAME_CORNER_KICK] = new CornerKick();
			_Evaluator[GAME_THROW_IN] = new ThrowIn();

			_Evaluator[GAME_ANTI_KICK_OFF] = new AntiKickOff();
			_Evaluator[GAME_ANTI_FREE_KICK] = new AntiFreeKick();
			_Evaluator[GAME_ANTI_GOAL_KICK] = new AntiGoalKick();
			_Evaluator[GAME_ANTI_CORNER_KICK] = new AntiCornerKick();
			_Evaluator[GAME_ANTI_THROW_IN] = new AntiThrowIn();

			_Evaluator[GAME_DROP_BALL] = new DropBall();
		}
		
	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput&) override{}
		
		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			int task = 0;
			std::ostringstream oss;
			/* 这个状态的存在已经在Action_Kick_Assignment被验证, 所以不检查evalutor是否有效 */
			auto evalutor = _Evaluator[input.GetGameStatus()]; 

			for (auto & agent : input.GetAgents()) {

				auto angleAndLocation = evalutor->KeepInPosition(input, task); /* .first为弧度，.second为位置 */
				int distance = (int)agent._Loacion.Distance(angleAndLocation.second);

				if (distance > 10){

					oss	<< "PASSMOVE"					<< ' '
						<< agent._ID					<< ' ' 
						<< angleAndLocation.second.GetX() << ' '
						<< angleAndLocation.second.GetY() << ' '
						<< angleAndLocation.first		<< ' '
						//<< distance						<< ' ' 
						<< '*'							<< ' ';

					output.AddCMD(oss.str());
					oss.clear();
				}

				task++;
			}

			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}
	
	private:

		std::map<GameStatus, EvaluatorForKick *> _Evaluator;
	};

}
