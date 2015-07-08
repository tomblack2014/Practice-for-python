/*********************************************************************
 *	@file		Auto.h
 *	@brief		行为树中，抢球操作，自动切换到进攻或者防守状态。
 *
 *
 *	Date        Name        Description
 *	15/04/15	MYLS		Creation.
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

namespace BehaviorTree {
	

	class Condition_IsAuto : public Condition {

	private:

		virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			auto currentStatus = input.GetGameStatus();
			if (currentStatus == GAME_AUTO)
				return NODE_STATUS_SUCCEED;
			else
				return NODE_STATUS_FAILED;
		}

	};
	

	///////////////////////////////////////////////////////////////////
	///
	/// 管理状态，判断是否合适转换为其它状态
	///	管理角色分配
	///
	///////////////////////////////////////////////////////////////////

	class Action_Auto_Assignment : public Action {

	private:

		virtual void OnEnter
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override {}

		/* 它只返回Running(继续执行)或者Failed(退出这个分支) */
		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/* 检查状态是否被改变 */
			if (input.GetGameStatus() != GAME_AUTO) {
				/* 退出这个分支 */
				return NODE_STATUS_FAILED;
			}

			/* 检查是否发现球 */
			
			const auto & ballLocation = input.GetBall()._Loacion;
			if (ballLocation == Ball::NO_LOCATION) {
				/* 未找到球，转换成防守 */
				output.SetGameStatus(GAME_DEFEND);
				return NODE_STATUS_FAILED;
			}

			/* 检查是否己方持球 */
			if (input.GetBall()._Owner != -1) {
				/* 己方持球，转为[进攻] */
				output.SwapAgent(input.GetBall()._Owner, 0);
				output.SetGameStatus(GAME_ATTACK);
				return NODE_STATUS_FAILED;
			}

			/* 
			 * 检查球和[己方]机器的距离
			 * 取得离球最近的机器的编号(不是id)以及位置
			 */

			int attacker = 0, attackerDis = INT_MAX;
			const auto & agents = input.GetAgents();
            for (int i = 0, n = static_cast<int>(agents.size()); i < n; i++) {
				int dis = (int)agents[i]._Loacion.Distance(ballLocation);
				if (attackerDis > dis) {
					attackerDis = dis;
					attacker = i;
				}
			}

			/* 检查球和[敌方]机器的距离 */
			
			int competitor = 0, competitorDis = INT_MAX;
			const auto & enemys = input.GetEnemies();
            for (int i = 0, n = static_cast<int>(enemys.size()); i < n; i++) {
				int dis = (int)enemys[i]._Loacion.Distance(ballLocation);
				if (competitorDis > dis) {
					competitorDis = dis;
					competitor = i;
				}
			}

			/* 检查己方或者敌方谁更容易抢球 */
			if (attackerDis > SWTICH_ATTACK_THRESHOLD + competitorDis) {
				/* 不利于抢球，转为[防守] */
				output.SwapAgent(input.GetBall()._Owner, 0);
				output.SetGameStatus(GAME_DEFEND);
				return NODE_STATUS_FAILED;
			}

			/* 下一次继续维护 */
			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}

	private:

		static const int SWTICH_ATTACK_THRESHOLD = 50;	/* 如果 己方离球距离 < 对方离球距离 则进攻，否则防守 */

	};


	///////////////////////////////////////////////////////////////////
	///
	/// 具体的抢球方法
	///
	///////////////////////////////////////////////////////////////////

	class Action_Auto_CatchBall : public Action {
		
	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput&) override{}
		
		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();
			
			std::ostringstream oss;
			
			/* 对0号发起抢球的命令 */

			const auto & agents = input.GetAgents();
			oss	<< "ATTACK"						<< ' '
				<< agents[0]._ID				<< ' ' 
				<< '*'							<< ' ';
			output.AddCMD(oss.str());
			oss.clear();

			/* 对其它机器发布MOVETO命令(暂时无) */

			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}

	};

}
