/*********************************************************************
 *	@file		Attack.h
 *	@brief		进攻阶段
 *
 *
 *	Date        Name        Description
 *	23/03/15	tom black	Creation
 *	01/05/15	MYLS		Rebuild
 *	30/05/15	TB			Design Action_Attack_Use_Default_Plan
 *
 *********************************************************************/

#pragma once

#include <vector>
#include <sstream>
#include <iostream>

#include "Stra/Common/Common.h"

#include "../Nodes.h"
#include "../CustomData.h"
#include "../LeafData.h"

namespace BehaviorTree {

	///////////////////////////////////////////////////////////////////
	///
	/// 通用部分(进攻状态的判断和维护)
	///
	///////////////////////////////////////////////////////////////////
	class Condition_IsAttacking : public Condition {

		virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			if (input.GetGameStatus() == GAME_ATTACK)
				return NODE_STATUS_SUCCEED;
			else
				return NODE_STATUS_FAILED;
		}
	};

	class Action_Attack_Assignment : public Action {
	public:
		Action_Attack_Assignment()
			: _BallLoc(Ball::NO_LOCATION)
		{}

	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/* [1]首先将持球队员放置在0号位作为主攻队员 */
			if (input.GetBall()._Owner != -1)
				output.SwapAgent(input.GetBall()._Owner, 0);

			/* [2]_BallLoc初始化，初始化为接球时的位置 (需要确保这里是找到球的) */
			if (_BallLoc == Ball::NO_LOCATION)
				_BallLoc = input.GetBall()._Loacion;
		}

		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			const std::vector<Agent> & agents = input.GetAgents();

			/* [1]检查状态是否被外界改变 */
			if (input.GetGameStatus() != GAME_ATTACK) {
				/* 状态被改变 */
				return NODE_STATUS_FAILED;
			}

			/* [2]判断是否丢球了 */
			if (input.GetBall()._Owner == -1) {
				/*变更为找球状态或防守状态*/
				output.SetGameStatus(GAME_AUTO);
				return NODE_STATUS_FAILED;
			}

			/* [3]判断是否运球超过 最大长度 */
			if (_BallLoc.Distance(input.GetBall()._Loacion) > MAX_MOVE_DISTANCE) {
				output.SetGameStatus(GAME_PASS);
				return NODE_STATUS_FAILED;
			}

			/* [4]不满足状态改变，则继续进攻 */
			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override
		{
			_BallLoc = Ball::NO_LOCATION;
		}

	private:

		static const int MAX_MOVE_DISTANCE = 300;	/**< 斯巴达300 */
		Vec2D<float> _BallLoc;						/**< 接球时的位置 */
	};


	///////////////////////////////////////////////////////////////////
	///
	/// 默认阵型
	///
	///	队员位置分配：
	///	[0]持球进攻队员
	/// [1]侧应进攻队员(主要是接传球)
	/// [2]中场接应队员
	/// [3]后场防守队员
	///
	///	PS:整体设计为两进攻队员平行于球门线向前推进，寻找机会传球和射门，另两个机器分布在中场和后场随时根据需要调整(其实就是打酱油……)
	///
	///////////////////////////////////////////////////////////////////

	class Action_Attack_Use_Default_Plan : public Action {
	
	public:
		Action_Attack_Use_Default_Plan() :
			_TargetLocation()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("Attack_Default", "Target2D", _TargetLocation);
		}

	private:
		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();
			
			//最初对角色的分配
			const std::vector<Agent> & agents = input.GetAgents();
			const int n = agents.size();
			auto destination = new Vec2D<float>[n];
			auto score = new int[n * n];

			/*0号以球为准，1号以球的y坐标作少许变化为准，2、3号为定点*/
			for (int i = 0; i < n; i++)
				destination[i] = _TargetLocation[i];
			destination[0] = input.GetBall()._Loacion;
			if (destination[0].GetY() > 0)
				destination[1] += destination[0];
			else
				destination[1] = destination[0] - destination[1];

			for (int i = 0; i < n; i++) {
				for (int task = 0; task < n; task++) {
					score[i * n + task] = (int)agents[i]._Loacion.Distance(destination[task]);
				}
			}

			auto assignment = new int[n];
			Calculation::Kuhn_Munkres(score, n, assignment);

			/* 尝试根据运算结果，进行任务调整 */
			for (int i = 0; i < n; i++)
				if (assignment[i] != i)
					output.SwapAgent(assignment[i], i);

			delete[]score;
			delete[]assignment;
		}

		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/*这里是默认的进攻方式，
		     默认的进攻方式在其它进攻方式都不满足的时候使用，所以希望能万金油一点，不需要针对性*/

			const std::vector<Agent> & agents = input.GetAgents();
			const int n = agents.size();
			auto destination = new Vec2D<float>[n];

			for (int i = 0; i < n; i++)
				destination[i] = _TargetLocation[i];
			destination[0] = agents[0]._Loacion;
			if (destination[0].GetY() > 0)
				destination[1] += destination[0];
			else
				destination[1] = destination[0] - destination[1];

			std::ostringstream oss;
			int task = 0;

			for (auto & agent : input.GetAgents()) {
				if (task == 0){
					oss << "ATTACK" << ' '
						<< agent._ID << ' '
						<< '*' << ' ';

					output.AddCMD(oss.str());
					oss.clear();
				}
				else{
					float distance = agent._Loacion.Distance(destination[task]);

					if (distance > 10){

						oss << "PASSMOVE" << ' '
							<< agent._ID << ' '
							<< destination[task].GetX() << ' '
							<< destination[task].GetY() << ' '
							<< destination[task].AngleTo(input.GetBall()._Loacion) << ' '
							<< '*' << ' ';

						output.AddCMD(oss.str());
						oss.clear();
					}
				}

				task++;
			}


			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}

	private:

		/* 需要预先读取的数据都在这里 */
		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
	};

	//////////////////////////////////////////////////////////////
	//
	//	TODO:在黑障信息完善的情况下或者即使不完整也有好的思路的情况下希望尽量写出各种好的进攻阵型，默认阵型确实过于简陋Orz
	//
	///////////////////////////////////////////////////////////////


	// 暂时废弃
	/////////////////////////////////////////////////////////////////////
	/////
	///// 阵型 A
	/////
	/////////////////////////////////////////////////////////////////////

	//class Condition_Attack_Whether_to_Use_Plan_A : public Condition {
	//
	//private:

	//	virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
	//	{
	//		const InputData & input = inputRef.GetRealData<InputData>();

	//		/* 进入攻击状态A的条件 */

	//		// TODO: 写条件的时候希望区分度高一些

	//		if (false)
	//			return NODE_STATUS_SUCCEED;
	//		else
	//			return NODE_STATUS_FAILED;
	//	}
	//};

	//class Action_Attack_Use_Plan_A : public Action {

	//private:

	//	virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
	//	{
	//		const InputData & input = inputRef.GetRealData<InputData>();
	//		OutputData & output = outputRef.GetRealData<OutputData>();

	//		/* 首次对角色的分配 */
	//		// TODO: 角色分配
	//	}

	//	virtual NodeStatus OnRunning
	//		(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
	//	{
	//		const InputData & input = inputRef.GetRealData<InputData>();
	//		OutputData & output = outputRef.GetRealData<OutputData>();

	//		// TODO: 进攻相关的细节

	//		return NODE_STATUS_RUNNING;
	//	}

	//	virtual void OnExit() override{}
	//};
}
