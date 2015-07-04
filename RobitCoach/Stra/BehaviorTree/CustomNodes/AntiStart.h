/*********************************************************************
 *	@file		AntiStart.h
 *	@brief		等待直到对方开球阶段结束
 *
 *
 *	Date        Name        Description
 *	21/04/15	MYLS		Creation
 *
 *********************************************************************/
#pragma once

#include <vector>
#include <sstream>

#include "Stra/Common/Common.h"

#include "../Nodes.h"
#include "../CustomData.h"
#include "../LeafData.h"


namespace BehaviorTree {
	
	class Condition_IsAntiStart : public Condition 
	{
	private:

		virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			if (input.GetGameStatus() == GAME_ANTI_START)
				return NODE_STATUS_SUCCEED;
			else
				return NODE_STATUS_FAILED;
		}

	};
	

	class Action_AntiStart_Assignment : public Action {

	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput&) override 
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			_Timer.Start();
			_StartPoint = input.GetBall()._Loacion;
		}

		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/* 检查状态是否异常改变 */
			if (input.GetGameStatus() != GAME_ANTI_START) {
				return NODE_STATUS_FAILED;
			}
			
			/* 检查等待时间是否达到10s */
			if (_Timer.GetElapsedTime() >= MAX_WAIT_TIME) {
				output.SetGameStatus(GAME_AUTO);
				return NODE_STATUS_FAILED;
			}

			/* 判断球是否移动 */
			if (_StartPoint.Distance(input.GetBall()._Loacion) >= DISTANCE_THRESHOLD) {
				output.SetGameStatus(GAME_AUTO);
				return NODE_STATUS_FAILED;
			}

			return NODE_STATUS_RUNNING;
		}
		
		virtual void OnExit() override 
		{
			_Timer.Stop();
		}

	private:

		static const unsigned int MAX_WAIT_TIME = 10000;	/**< 最大等待时间为10s */
		static const unsigned int DISTANCE_THRESHOLD = 50;	/**< 球移动距离达到50cm，即判定球开始动 */

		Vec2D<float> _StartPoint;								/**< 发球点 */
		Timer _Timer;										/**< 计时器，记录发球过程经过的时间 */
	};


	class Action_AntiStart : public Action {
	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput&) override{}
		
		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();
			
			/* do nothing */

			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}

	};


}
