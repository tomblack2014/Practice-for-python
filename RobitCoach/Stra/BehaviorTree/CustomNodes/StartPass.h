/*********************************************************************
 *	@file		StaratPass.h
 *	@brief		控制开球时候的传球的分支
 *
 *
 *	Date        Name        Description
 *	23/03/15	MYLS		Creation
 *	15/04/15	MYLS		Rename.
 *
 *********************************************************************/
#pragma once

#include <sstream>

#include "Stra/Common/Common.h"

#include "../Nodes.h"
#include "../CustomData.h"
#include "../LeafData.h"


namespace BehaviorTree {
	
	class Condition_IsStartPass : public Condition {
		virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			if (input.GetGameStatus() == GAME_START_PASS)
				return NODE_STATUS_SUCCEED;
			else
				return NODE_STATUS_FAILED;
		}
	};
	

	class Action_StartPass_Assignment : public Action {
	public:

		Action_StartPass_Assignment()
			: _BallSamples(NUMBER_OF_SAMPLES_MAX)
			, _CatcherSamples(NUMBER_OF_SAMPLES_MAX)
		{};

	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{}

		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/* 检查状态是否改变 */
			if (input.GetGameStatus() != GAME_START_PASS) {
				return NODE_STATUS_FAILED;
			}
			 
			/* 确认是否已经接到球 */
			if (input.GetBall()._Owner >= 0 && input.GetAgents()[0]._ID != input.GetBall()._Owner) {
				output.SetGameStatus(GAME_ATTACK);
				return NODE_STATUS_FAILED;
			}
			
			/* 未接到球时，采样NUMBER_OF_SAMPLES_MAX帧，检查球和接球者的位置变化 */

			auto & ballLocation = input.GetBall()._Loacion;
			if (ballLocation == Ball::NO_LOCATION) {
				/* 没有找到球 */
				/*这里变更为[搜球]状态*/
				output.SetGameStatus(GAME_AUTO);
				return NODE_STATUS_FAILED;
			}

			/* 上一帧，<球,接球者> 平均距离 */
			int oldDistanceCatcher2Ball = 
				(int)_BallSamples.GetAverage().Distance(_CatcherSamples.GetAverage());
			
			_BallSamples.Push(ballLocation);
			_CatcherSamples.Push(input.GetAgents()[1]._Loacion);

			if (_BallSamples.IsReady()) {

				/* 这一帧，<球,接球者> 平均距离 */
				int distanceCatcher2Ball = 
					(int)_BallSamples.GetAverage().Distance(_CatcherSamples.GetAverage());

				if (oldDistanceCatcher2Ball < distanceCatcher2Ball + DISTANCE_THRESHOLD) {
					// TODO: 疑问，如果球移动很慢，可能会误判？需要测试
					/*  认为[接球失败]，需要变更为[抢球]状态； */
					output.SetGameStatus(GAME_AUTO);
					return NODE_STATUS_FAILED;
				}
			}

			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override
		{
			_BallSamples.Clear();
			_CatcherSamples.Clear();
		}

	private:

		static const int DISTANCE_THRESHOLD = 20;			// TODO: 不知这个数据最优值
		static const int NUMBER_OF_SAMPLES_MAX = 10;		// TODO: 不知这个数据最优值
		DataCollector<Vec2D<float>> _BallSamples;
		DataCollector<Vec2D<float>> _CatcherSamples;
	};


	class Action_StartPass : public Action {
	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput&) override{}
		
		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();
			
			auto passer = input.GetAgents()[0];
			auto catcher = input.GetAgents()[1];

			std::ostringstream oss;
			/*针对传球者的设定*/
			oss	<< "PASS"				<< ' '
				<< passer._ID				<< ' ' 
				<< catcher._Loacion.GetX()	<< ' '
				<< catcher._Loacion.GetY()  << ' '
				<< '*'						<< ' ';
			output.AddCMD(oss.str());
			oss.clear();

			/*针对接球者的设定*/
			oss	<< "CATCH"					   << ' '
				<< catcher._ID					   << ' ' 
				<< input.GetBall()._Loacion.GetX() << ' '
				<< input.GetBall()._Loacion.GetY() << ' '
				<< '*'							   << ' ';
			output.AddCMD(oss.str());
			oss.clear();

			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}

	};




}
