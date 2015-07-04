/*********************************************************************
 *	@file		Defend.h
 *	@brief		防守阶段相关的节点
 *
 *
 *	Date        Name        Description
 *	22/05/15	MYLS		Creation
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
	/// 通用部分
	///
	///////////////////////////////////////////////////////////////////

	class Condition_IsDefending : public Condition {
		virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			if (input.GetGameStatus() == GAME_DEFEND)
				return NODE_STATUS_SUCCEED;
			else
				return NODE_STATUS_FAILED;
		}
	};

	class Action_Defend_Assignment : public Action {
		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override {}

		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/* [1]检查状态是否被外界改变 */
			if (input.GetGameStatus() != GAME_DEFEND) {
				/* 状态被改变 */
				return NODE_STATUS_FAILED;
			}

			/* [2]判断是否已经抢到球了 */
			if (input.GetBall()._Owner > -1) {
				/*变更为找球状态或防守状态*/
				output.SetGameStatus(GAME_AUTO);
				return NODE_STATUS_FAILED;
			}

			/* [3]继续防守 */
			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}
	};


	///////////////////////////////////////////////////////////////////
	///
	/// 默认阵型
	/// 1号位（离球最近）贴身防守球
	/// 2, 3，4号位 防止传球 
	///
	///////////////////////////////////////////////////////////////////

	class Action_Defend_Use_Default_Plan : public Action {

	public:

		Action_Defend_Use_Default_Plan() :
			tempDoor(),
			_TargetLocation()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("Defend_Default", "Target2D", _TargetLocation);
			tempDoor = Vec2D<float>(-_TargetLocation[3].GetX(), 0);
		}

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();
			int tempGoalDefendID; // 用来存储防守持球地方队员ID
			for (int i = 0; i < 4; i++)
			{
				float tempLength = _TargetLocation[0].GetX(); //任意设置的最大距离
				if (input.GetAgents()[i]._Loacion.Distance(input.GetBall()._Loacion) < tempLength)
				{
					tempLength = input.GetAgents()[i]._Loacion.Distance(input.GetBall()._Loacion);
					output.SwapAgent(0, i);
					tempGoalDefendID = input.GetAgents()[i]._ID;
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (input.GetAgents()[i]._ID == tempGoalDefendID)
					continue;
				double tempLength = _TargetLocation[0].GetX();
				if (input.GetAgents()[i]._Loacion.GetX() + _TargetLocation[3].GetX() < tempLength)
				{
					tempLength = input.GetAgents()[i]._Loacion.GetX() + _TargetLocation[3].GetX();
					output.SwapAgent(1, i);
				}
			}
			/*最初对角色的分配*/
		}
		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			//默认防守策略
			std::ostringstream oss;

			//一号位设置
			Vec2D<float> tempDoorVector = Vec2D<float>(input.GetBall()._Loacion - tempDoor);
			int tempHoldBallEnemy = -1;
			for (int i = 0; i < 4; i++)
			{
				if (Vec2D<float>(input.GetEnemies()[i]._Loacion - input.GetBall()._Loacion).Length() < _TargetLocation[0].GetY())
				{
					tempHoldBallEnemy = i;
					break;
				}
			}
			double tempMemberToEnemtAngle =
				tempDoorVector.AngleTo(input.GetEnemies()[tempHoldBallEnemy]._Loacion - input.GetBall()._Loacion);
			if (tempHoldBallEnemy == -1
				|| tempMemberToEnemtAngle > -Calculation::PI / _TargetLocation[1].GetX()
				|| tempMemberToEnemtAngle < Calculation::PI / _TargetLocation[1].GetX())
			{
				oss << "ATTACK" << ' '
					<< input.GetAgents()[0]._ID << ' '
					<< '*' << ' ';
				output.AddCMD(oss.str());
				oss.clear();
			}
			else
			{
				Vec2D<float> tempDefendLocation
					= Vec2D<float>(input.GetBall()._Loacion + tempDoorVector * _TargetLocation[1].GetY() / tempDoorVector.Length());
				tempDefendLocation = tempDefendLocation + input.GetBall()._Loacion;

				oss << "PASSMOVE" << ' '
					<< input.GetAgents()[0]._ID << ' '
					<< tempDefendLocation.GetX() << ' '
					<< tempDefendLocation.GetY() << ' '
					<< -tempDefendLocation.Angle() << ' '
					//<< _TargetLocation[1].GetY() << ' '
					<< '*' << ' ';
				output.AddCMD(oss.str());
				oss.clear();
			}
			//防守持球敌人策略：当可以抢到球时采用ATTACK策略，不能抢到球时挡在球与门之间

			//二,三，四号位设置		
			FindMostImportantEnemys(input);
			Vec2D<float> tempVector[3];
			for (int i = 0; i < 3; i++)
			{
				bool tempSign[4] = { true, false, false, false };
				tempVector[i] = Vec2D<float>(input.GetBall()._Loacion - input.GetEnemies()[importantEnemy[i]]._Loacion);

				if (tempVector[i].Length() > _TargetLocation[2].GetX())
					tempVector[i] = tempVector[i] * _TargetLocation[2].GetY() / tempVector[i].Length(); //设置离球距离
				else tempVector[i] /= 2;

				tempVector[i] = input.GetBall()._Loacion + tempVector[i]; //计算最终坐标

				/*边界处理*/
				if (tempVector[i].GetX() < -_TargetLocation[3].GetX())
					tempVector[i].SetX(-_TargetLocation[3].GetX());
				if (tempVector[i].GetX() > _TargetLocation[3].GetX())
					tempVector[i].SetX(_TargetLocation[3].GetX());
				if (tempVector[i].GetY() < -_TargetLocation[3].GetY())
					tempVector[i].SetX(-_TargetLocation[3].GetY());
				if (tempVector[i].GetX() > _TargetLocation[3].GetY())
					tempVector[i].SetX(_TargetLocation[3].GetY());
				/*边界处理*/

				double minLength = _TargetLocation[0].GetX();
				for (int j = 1; j < 4; j++)
				{
					if (tempSign[j] == true)
						continue;
					if (minLength > tempVector[i].Distance(input.GetAgents()[j]._Loacion))
						minLength = tempVector[i].Distance(input.GetAgents()[j]._Loacion);
					output.SwapAgent(i + 1, j);
				}
				//队员角色调换

				oss << "MOVETO" << ' '
					<< input.GetAgents()[i]._ID << ' '
					<< tempVector[i].GetX() << ' '
					<< tempVector[i].GetY() << ' '
					//<< tempVector[i].Angle() << ' '
					//<< tempVector[i].DistanceTo(input.GetBall()._Loacion) << ' '
					<< '*' << ' ';
			}
			//防守预接球敌人策略：离球3m，防止传球
			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}
	private:
		//黑障重要程度评判函数
		virtual void FindMostImportantEnemys(const InputData & input)
		{
			for (int i = 0; i < 3; i++)
			{
				int minLength = (int)_TargetLocation[0].GetX();
				for (int j = 0; j < 4; j++) // 黑障数量未知，暂定四个
				{
					bool tempSign = true;
					for (int k = 0; k < i; k++)
					{
						if (j == importantEnemy[k])
						{
							tempSign = false;
							break;
						}
					}
					if (tempSign == false)
						continue;
					if (input.GetEnemies()[j]._Loacion.Distance(tempDoor) < minLength)
					{
						minLength = (int)input.GetEnemies()[j]._Loacion.Distance(tempDoor);
						importantEnemy[i] = j;
					}
				}
			}
			return;
		}
		int importantEnemy[4];
		Vec2D<float> tempDoor;

		std::vector<Vec2D<float>> _TargetLocation;
		/*
		[0].X通用寻找最小值是参量
		[0].Y球旁以Y为半径内有黑障则认为敌方持球（此处用来判断时候可以抢球
		[1].X 当对方持球队员偏移角度在(-PI/X,PI/X)内时认为可以抢球
		[1].Y 1号防守位（防守持球队员）距离球Ycm
		[2].X 计算过程参数
		[2].Y 协防队员离球距离
		[3]  半场长宽参数
		*/

	};
	/* 这段暂时废弃
	///////////////////////////////////////////////////////////////////
	///
	/// 阵型 A
	///
	///////////////////////////////////////////////////////////////////
	class Condition_Defend_Whether_to_Use_Plan_A : public Condition {
	virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
	{
	const InputData & input = inputRef.GetRealData<InputData>();

	// TODO: 判断是否应该进入防守A计划
	if (false)
	return NODE_STATUS_SUCCEED;
	else
	return NODE_STATUS_FAILED;
	}
	};

	class Action_Defend_Use_Plan_A : public Action {
	private:
	virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
	{
	const InputData & input = inputRef.GetRealData<InputData>();
	OutputData & output = outputRef.GetRealData<OutputData>();

	// TODO: 角色分配

	}

	virtual NodeStatus OnRunning
	(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
	{
	const InputData & input = inputRef.GetRealData<InputData>();
	OutputData & output = outputRef.GetRealData<OutputData>();

	// TODO: 方式阵型

	return NODE_STATUS_RUNNING;
	}

	virtual void OnExit() override{}
	};
	*/
}
