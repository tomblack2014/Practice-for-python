/*********************************************************************
 *	@file		Pass.h
 *	@brief		控制传球的分支
 *
 *
 *	Date        Name        Description
 *	22/05/15	MYLS		Creation
 *	05/06/15	TB			Design Action_Pass
 *
 *********************************************************************/
#pragma once

#include <sstream>

#include "Stra/Common/Common.h"

#include "../Nodes.h"
#include "../CustomData.h"
#include "../LeafData.h"
#include "../DataCollector.h"


namespace BehaviorTree {
	
	class Condition_IsPassing : public Condition {
	private:

		virtual NodeStatus Check(const BehaviorTreeInput& inputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();

			if (input.GetGameStatus() == GAME_PASS)
				return NODE_STATUS_SUCCEED;
			else
				return NODE_STATUS_FAILED;
		}

	};
	
	///////////////////////////////////////////////////////////////////
	///
	/// 管理状态，管理角色分配，检查传球是否成功
	///
	///////////////////////////////////////////////////////////////////

	class Action_Pass_Assignment : public Action {
	public:

		Action_Pass_Assignment()
			: _BallSamples(NUMBER_OF_SAMPLES_MAX)
			, _CatcherSamples(NUMBER_OF_SAMPLES_MAX)
		{};

	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/*检查并分配各个角色（只分配一次）*/
			/*假设一定有队员持球*/
			if (input.GetBall()._Owner != -1)
				output.SwapAgent(input.GetBall()._Owner,0);
			else{
				//TODO:异常处理
				;
			}
		}

		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();

			/* [1]检查状态是否被改变 */
			if (input.GetGameStatus() != GAME_PASS) {
				return NODE_STATUS_FAILED;
			}
			 
			/* [2]确认是否已经接到球 */
			if (input.GetBall()._Owner >= 0) {
				output.SetGameStatus(GAME_ATTACK);
				return NODE_STATUS_FAILED;
			}
			
			/* [3]未接到球时，采样NUMBER_OF_SAMPLES_MAX帧，检查球和接球者的位置变化 */

			auto & ballLocation = input.GetBall()._Loacion;
			if (ballLocation == Ball::NO_LOCATION) {
				/* 没有找到球，开始防守 */
				output.SetGameStatus(GAME_DEFEND);
				return NODE_STATUS_FAILED;
			}

			/* 上一帧，<球,接球者> 平均距离 */
			float oldDistanceCatcher2Ball = 
				_BallSamples.GetAverage().Distance(_CatcherSamples.GetAverage());
			
			_BallSamples.Push(ballLocation);
			_CatcherSamples.Push(input.GetAgents()[1]._Loacion);

			if (_BallSamples.IsReady()) {

				/* 这一帧，<球,接球者> 平均距离 */
				float distanceCatcher2Ball = 
					_BallSamples.GetAverage().Distance(_CatcherSamples.GetAverage());

				if (oldDistanceCatcher2Ball > distanceCatcher2Ball + DISTANCE_THRESHOLD) {
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
		DataCollector<Vec2Df> _BallSamples;
		DataCollector<Vec2Df> _CatcherSamples;
	};


	///////////////////////////////////////////////////////////////////
	///
	/// 传球的具体事项
	///
	///////////////////////////////////////////////////////////////////

	class Action_Pass : public Action {
	public:

		Action_Pass()
			: _IsPassing(false)
			, _TargetLoc()
			, UNIT_ANGLE(0)
		{
			TheLeafData::Instance()->getValue<double>("Pass_Action", "Unit_Angle", UNIT_ANGLE);
		}
	
	private:

		virtual void OnEnter(const BehaviorTreeInput& inputRef, BehaviorTreeOutput&) override
		{
			_IsPassing = false;
		}
		
		virtual NodeStatus OnRunning
			(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef) override
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			OutputData & output = outputRef.GetRealData<OutputData>();
			
			const std::vector<Agent> & agents = input.GetAgents();
			int n = agents.size();

			if (!_IsPassing) {
				_IsPassing = true;

				/* [1]只做一次，寻找合适的接球位置 */

				_TargetLoc = Vec2D<float>(FindTarget(inputRef));

				/* [2]寻找接球者，将其Swap到位置1 */

				int tagent = 1;
				float min = 1200 + 1800;
				for (int i = 0; i < n; i++){
					float temp = agents[i]._Loacion.Distance(_TargetLoc);
					if (temp < min){
						min = temp;
						tagent = i;
					}
				}

				output.SwapAgent(1, tagent);

				/* [3]只做一次，对持球人发布传球命令 */

				std::ostringstream oss;
				oss	<< "3M_PASS"					<< ' '
					<< agents[0]._ID				<< ' ' 
					<< _TargetLoc .GetX()			<< ' '
					<< _TargetLoc .GetY()			<< ' '
					<< '*'							<< ' ';
				output.AddCMD(oss.str());
				oss.clear();

				/* [4]只做一次，对接球者发布命令 */
				//TODO:此处用队员位置还是球位置？需要测试

				oss << "3M_CATCH"				 << ' '
					<< agents[1]._ID			 << ' '
					<< agents[0]._Loacion.GetX() << ' '
					<< agents[0]._Loacion.GetY() << ' '
					//<< input.GetBall()._Loacion.GetX() << ' '
					//<< input.GetBall()._Loacion.GetY() << ' '
					<< '*'						 << ' ';
				output.AddCMD(oss.str());
				oss.clear();

			} else {
				/* [5]对接球者发布命令 */
				//TODO:此处用队员位置还是球位置？需要测试

				std::ostringstream oss;
				oss << "3M_CATCH" << ' '
					<< agents[1]._ID << ' '
					<< agents[0]._Loacion.GetX() << ' '
					<< agents[0]._Loacion.GetY() << ' '
					//<< input.GetBall()._Loacion.GetX() << ' '
					//<< input.GetBall()._Loacion.GetY() << ' '
					<< '*' << ' ';
				output.AddCMD(oss.str());
				oss.clear();
			}
			
			/*这里是两个打酱油的机器的相关命令(暂时不给命令？等到转进攻或防守？)*/

			return NODE_STATUS_RUNNING;
		}

		virtual void OnExit() override{}

	private:
		/*求出当前最适合接球点*/

		//TODO:在原来基础上可以加上根据当前场地位置的判断（例如前场腹地不可能向前场传球）
		//以及传球的距离（例如一个黑障离持球队员很远，就不需要考虑）

		/*当前策略：
		从0度开始，每次搜索一个固定角度是否有黑障，搜索过程为正负交替，
		如先搜索0~k度，再搜索0~（-k）度，再搜索k~2k度，再搜索（-k）~（-2k）度，以此类推，
		直到找到第一个没有黑障的角度区间，在此区间取角平分线上一点作为传球点*/
		Vec2D<float> FindTarget(const BehaviorTreeInput& inputRef)
		{
			const InputData & input = inputRef.GetRealData<InputData>();
			const std::vector<Enemy> & enermys = input.GetEnemies();
			const int n = enermys.size();

			/*暂时假定一定能找到传球角度*/
			double angle;
			for (angle = 0; angle < Calculation::PI; angle += UNIT_ANGLE){
				bool flag = false;
				for (int i = 0; i < n; i++){
					double tempAngle = input.GetBall()._Loacion.AngleTo(enermys[i]._Loacion);
					if (tempAngle > angle && tempAngle < angle + UNIT_ANGLE){
						flag = true;
						break;
					}
				}
				if (!flag)
					break;

				flag = false;
				for (int i = 0; i < n; i++){
					double tempAngle = input.GetBall()._Loacion.AngleTo(enermys[i]._Loacion);
					if (tempAngle < -angle && tempAngle > -(angle + UNIT_ANGLE)){
						flag = true;
						break;
					}
				}
				if (!flag)
					break;
			}

			Vec2D<float> _Target(angle + UNIT_ANGLE/2, (float)DIATANCE, true);

			return _Target;
		}

	private:

		bool _IsPassing;							/**< 标记完成传球准备 */
		Vec2D<float> _TargetLoc;						/**< 传球的目标点 */

		static const int DIATANCE = 300;
		double UNIT_ANGLE;						/**<固定单位偏角*/

	};

	/*写在源文件中*/
	//static const double UNIT_ANGLE = Calculation::PI/6;				// TODO: 不知这个数据最优值,需测试
	
}
