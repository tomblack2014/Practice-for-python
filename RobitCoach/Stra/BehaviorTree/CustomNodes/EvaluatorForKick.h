/*********************************************************************
*	@file		EvaluatorForKick.h
*	@brief		包含所有的开球的角色分配方法和准备的位置
*
*
*	Date        Name        Description
*	15/04/15	MYLS		Creation.
*   03/05/15    TB,ssj		add KickOff、FreeKick、GoalKick、CornerKick、ThrowIn
*	22/05/15	TB			add AntiKickoff、AntiCornerKick、AntiThrowIn、DropBall
*	23/05/15	TB			add AntiFreeKick、AntiGoalKick
*	27/05/15	TB			modification
*
*********************************************************************/

#pragma once

#include <vector>

#include "Stra/Common/Common.h"

#include "../CustomData.h"
#include "../LeafData.h"


namespace BehaviorTree {

	/**
	*	\brief	基类，用于实现多态
	*			派生出各种分配、站位方式
	*/
	class EvaluatorForKick {
	public:
		virtual int Assignment(const InputData &, const int, const int) = 0;
		virtual std::pair<double, Vec2D<float>> KeepInPosition(const InputData &, const int) = 0;
	};

	/**
	*	\brief	KickOff行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]传球
	*			[1]接球
	*			[2]后场定点
	*			[3]另一个后场定点
	*/
	class KickOff : public EvaluatorForKick{

	public:
		KickOff() :
			_TargetLocation(),
			_TargetAngle()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("Kickoff", "Target2D", _TargetLocation);
			TheLeafData::Instance()->getValue<double>("Kickoff", "TargetA", _TargetAngle);
		}

	public:

		/* 评估值越高越适合做这件事，支持负的评估值 */
		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			Vec2D<float> delta(0, 0);

			/* 0,1需要根据球位置制定站位 */
			if (task == 0 || task == 1)
				delta = input.GetBall()._Loacion;

			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(delta + _TargetLocation[task]) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/* 这里机器角色号等于任务编号 */

			auto ret = Vec2D<float>(0.0, 0.0);

			/* 0,1需要根据球位置制定站位 */
			float sign = (index == 0 || index == 1) ? 1.0f : 0;

			ret = input.GetBall()._Loacion * sign + _TargetLocation[index];

			/* 处理结果是机器应该有的[弧度]和[位置] */
			return std::make_pair(_TargetAngle[index], ret);
		}

	private:

		/* 需要预先读取的数据都在这里 */

		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
		std::vector<double> _TargetAngle;			/**< _TargetAngleA[i]即站在第i个目标点时应有的朝向 */
	};



	/**
	*	\brief	FreeKick行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]传球
	*			[1]接球
	*			[2]中场站位（y>0)
	*			[3]中场站位（y<0)
	*/
	class FreeKick : public EvaluatorForKick{

	public:
		FreeKick() :
			_TargetLocation(),
			_Target(),
			_HasCalculated()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("FreeKick", "Target2D", _TargetLocation);
			int numMax = 0;
			TheLeafData::Instance()->getValue<int>("Settings", "AgentMaxNum", numMax);
			_Target = std::move(std::vector < Vec2D<float> >(numMax));
			_HasCalculated = std::move(std::vector < bool >(numMax));
		}

	public:

		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			if (_HasCalculated[index] == false)
			{
				double angle = 0;
				int tempWay = 1;
				if (input.GetBall()._Loacion.GetY() > 0)
					tempWay = -1; //保证传球关于进攻（与中线垂直）方向对称   
				if (input.GetBall()._Loacion.GetX() > -600)
					angle = tempWay * (input.GetBall()._Loacion.GetX() + 600) / 1800 * Calculation::PI;
				// -600 至 600 传球角度随距离变换 ，传球线角度计算
				if (index == 0)
					_Target[index] = input.GetBall()._Loacion + Vec2D<float>(angle, -_TargetLocation[index].Length(), true);
				//一号位传球，距离球50cm
				else if (index == 1)
					_Target[index] = input.GetBall()._Loacion + Vec2D<float>(angle, _TargetLocation[index].Length(), true);
				// 二号位接球，距离球100cm
				else if (index == 2 || index == 3)
				{
					if (input.GetBall()._Loacion.GetY() < 0)
					{
						if (index == 2)
							_Target[index] = _TargetLocation[index];
						else
						{
							if (angle > 0)
								angle += Calculation::PI / 2;
							else angle -= Calculation::PI / 2;
							_Target[index] = input.GetBall()._Loacion + Vec2D<float>(angle, 200, true);
						}
					}
					else
					{
						if (index == 3)
							_Target[index] = _TargetLocation[index];
						else
						{
							if (angle > 0)
								angle += Calculation::PI / 2;
							else angle -= Calculation::PI / 2;
							_Target[index] = input.GetBall()._Loacion + Vec2D<float>(angle, 200, true);
						}
					}
				}
				//三号位四号位（一个为定点，另一个与传球角度成直角，距离球200cm）
				_HasCalculated[index] = true;
			}
			return -(int)(_Target[index] - (input.GetAgents())[index]._Loacion).Length() * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/* 这里机器角色号等于任务编号 */
			double angle = 0;
			int tempWay = 1;
			if (input.GetBall()._Loacion.GetY() > 0)
				tempWay = -1;
			//保证传球关于进攻（与中线垂直）方向对称   
			if ((index == 0 || index == 1) && input.GetBall()._Loacion.GetX() > -600)
				angle = tempWay * (input.GetBall()._Loacion.GetX() + 600) / 1800 * Calculation::PI;
			// -600 至 300 传球角度随距离变换 
			if (index == 1)
			{
				if (angle > 0)
					angle -= Calculation::PI;
				else angle += Calculation::PI;
			}
			_HasCalculated[index] = false;
			return std::make_pair(angle, _Target[index]);
		}

	private:
		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
		/* 需要预先读取的数据都在这里 */
		std::vector<Vec2D<float>> _Target;			/**< 计算得到的目标点 */
		std::vector<bool> _HasCalculated;			/**< 检查是否计算完成 */
	};


	/**
	*	\brief	GoalKick行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]传球
	*			[1]接球
	*			[2]中场站位，准备进攻（y>0)
	*			[3]中场站位，准备进攻（y<0)
	*/
	class GoalKick : public EvaluatorForKick{

	public:
		GoalKick() :
			_TargetLocation(),
			_TargetAngle(),
			_Target(),
			_HasCalculated()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("GoalKick", "Target2D", _TargetLocation);
			//读取预处理数据
			TheLeafData::Instance()->getValue<double>("GoalKick", "TargetA", _TargetAngle);
			//读取预处理角度
			int numMax = 0;
			TheLeafData::Instance()->getValue<int>("Settings", "AgentMaxNum", numMax);
			_Target = std::move(std::vector < Vec2D<float> >(numMax));
			_HasCalculated = std::move(std::vector < bool >(numMax));
		}

	public:
		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			if (_HasCalculated[index] == false)
			{
                //int tempWay = 1;
				if (index == 0)
					_Target[index] = input.GetBall()._Loacion + Vec2D<float>(_TargetAngle[index], -_TargetLocation[index].Length(), true);
				else if (index == 1)
					_Target[index] = input.GetBall()._Loacion + Vec2D<float>(_TargetAngle[index], _TargetLocation[index].Length(), true);
				// 一，二号位，距离球50cm,150cm
				else
					_Target[index] = _TargetLocation[index];
				//三号位四号位定点(预处理）
				_HasCalculated[index] = true;
			}
			return -(int)(_Target[index] - (input.GetAgents())[index]._Loacion).Length() * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/* 这里机器角色号等于任务编号 */
			auto ret = Vec2D<float>(0, 0);
			double angle = 0;
//			int tempWay = 1;
			if (index == 1)
				angle = Calculation::PI;
			//接球角度变换
			_HasCalculated[index] = false;
			return std::make_pair(angle, _Target[index]);
		}

	private:
		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
		std::vector<double> _TargetAngle;			/**< _TargetAngle[i]即站在第i个目标点时应有的朝向 */
		/* 需要预先读取的数据都在这里 */
		std::vector<Vec2D<float>> _Target;			/**< 计算得到的目标点 */
		std::vector<bool> _HasCalculated;			/**< 检查是否计算完成 */
	};


	/**
	*	\brief	CornerKick行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]传球
	*			[1]接球
	*			[2]同进攻
	*			[3]同进攻
	*/
	class CornerKick : public EvaluatorForKick{

	public:
		CornerKick()
			: _TargetLocation()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("CornerKick", "Target2D", _TargetLocation);
		}

	public:

		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			/* 评估值越高越适合做这件事，支持负的评估值 */

			if (task > 1){
				return -(int)input.GetAgents()[index]._Loacion.Distance(_TargetLocation[task]) * 10;
			}

			/*0,1号需要根据球的位置制定站位，且两种情况y轴坐标相反*/
			Vec2D <float> delta(_TargetLocation[task]);
			if (input.GetBall()._Loacion.GetY() > 0)
				delta.SetY(-delta.GetY());

			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(input.GetBall()._Loacion + delta) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/* 这里机器角色号等于任务编号 */

			auto ret = Vec2D<float>(0, 0);
			Vec2D <float> delta(_TargetLocation[index]);

			/*0,1号需要根据球的位置制定站位，且两种情况y轴坐标相反*/
			if (index == 0 || index == 1){
				if (input.GetBall()._Loacion.GetY() > 0)
					delta.SetY(-delta.GetY());
				ret = input.GetBall()._Loacion + delta;
			}
			else {
				/*其他队员固定站位*/
				ret = delta;
			}

			/*0,1号的角度根据球的位置可能有两种相反的情况*/
//			double sign = (input.GetBall()._Loacion.GetY() > 0) ? -1 : 1;

			/* 处理结果是机器应该有的[位置]和[弧度] */
			return std::make_pair(ret.AngleTo(input.GetBall()._Loacion), ret);
		}

	private:

		/* 需要预先读取的数据都在这里 */

		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
	};

	/**
	*	\brief	ThrowIn行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]传球
	*			[1]接球
	*			[2]与接球手关于y轴对称
	*			[3]与接球手关于x轴对称
	*/
	class ThrowIn : public EvaluatorForKick{

	public:
		ThrowIn()
			: _Distance(0)
			, _Location()
			, _HasCalculated()
			, _Target()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("ThrowIn", "Target2D", _Location);
			TheLeafData::Instance()->getValue<float>("ThrowIn", "TargetA", _Distance);

			int numMax = 0;
			TheLeafData::Instance()->getValue<int>("Settings", "AgentMaxNum", numMax);
			_Target = std::move(std::vector < Vec2D<float> >(numMax));
			_HasCalculated = std::move(std::vector < bool >(numMax));
		}

	public:

		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			/* 评估值越高越适合做这件事，支持负的评估值 */

			if (!_HasCalculated[task]){
				/*球->标记点 角度*/
				double angle = _Location.AngleTo(input.GetBall()._Loacion);

				if (task == 1 || task == 2 || task == 3)
					angle += Calculation::PI;

				/*队员位置分配点*/
				Vec2D <float> delta(angle, _Distance[task], true);

				delta = input.GetBall()._Loacion + delta;

				/*2、3号分别于1号关于y轴、x轴对称*/
				if (index == 2)
					delta.SetX(-delta.GetX());
				else if (index == 3)
					delta.SetY(-delta.GetY());

				/*1号靠近中线情况下2号可能与1号靠的太近，在此修正*/
				if (index == 2 && abs(delta.GetX()) < 100)
					if (delta.GetX() < 0)
						delta.SetX(delta.GetX() - 100);
					else
						delta.SetX(delta.GetX() + 100);

				_Target[task] = delta;
			}
			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(_Target[task]) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/* 这里机器角色号等于任务编号 */

			/*队员位置分配点*/
			Vec2D <float> ret(_Target[index]);

			/* 处理结果是机器应该有的[弧度]和[位置] */

			_HasCalculated[index] = false;

			return std::make_pair(ret.AngleTo(input.GetBall()._Loacion), ret);
		}

	private:

		/* 需要预先读取的数据都在这里 */

		Vec2D <float> _Location;						/**< _Location为标记点 */
		std::vector<float> _Distance;					/**< _Distance[i]为传接球手与球的距离 */

		std::vector<bool> _HasCalculated;			/**< 检查是否计算完成 */
		std::vector<Vec2D<float>> _Target;			/**< 计算得到的目标点 */
	};

	/**
	*	\brief	AntiKickOff行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]防守位1（距球门较近,在球和球门中点之间）
	*			[1]防守位2（距中场较近）	//TODO：位置为敌方其他进攻球员附近
	*			[2]防守位3（距中场较近）	//TODO：安放在最空旷的地方，便于抢球
	*			[3]防守反击位（对方半场距中场较近）
	*/
	class AntiKickOff : public EvaluatorForKick{

	public:
		AntiKickOff() :
			_TargetLocation()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("AntiKickOff", "Target2D", _TargetLocation);
		}

	public:

		/* 评估值越高越适合做这件事，支持负的评估值 */
		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			Vec2D <float> delta(_TargetLocation[task]);

			if (task == 0){
				delta += input.GetBall()._Loacion;
			}
			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(delta) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/* 这里机器角色号等于任务编号 */

			Vec2D <float> delta(_TargetLocation[index]);

			if (index == 0){
				delta += input.GetBall()._Loacion;
			}

			/* 处理结果是机器应该有的[弧度]和[位置] */
			return std::make_pair(_TargetLocation[index].AngleTo(input.GetBall()._Loacion), delta);
		}

	private:

		/* 需要预先读取的数据都在这里 */

		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
	};

	/**
	*	\brief	AntiCornerKick行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]配合守门员防守
	*			[1]配合守门员防守(守门员、0、1三台机器位置封锁敌方开球机器，便于防守和防止传球)
	*			[2]靠近中线防守 //TODO:位置为敌方其他进攻球员附近
	*			[3]中线位置随时防守反击
	*/
	class AntiCornerKick : public EvaluatorForKick{

	public:
		AntiCornerKick()
			: _TargetLocation()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("AntiCornerKick", "Target2D", _TargetLocation);
		}

	public:

		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			/* 评估值越高越适合做这件事，支持负的评估值 */

			Vec2D <float> delta(_TargetLocation[task]);

			/*根据球的位置有两种y轴坐标相反的站位情况，y值为正时与默认值相反*/
			if (input.GetBall()._Loacion.GetY() > 0)
				delta.SetY(-delta.GetY());

			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(delta) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/* 这里机器角色号等于任务编号 */

			Vec2D <float> ret(_TargetLocation[index]);

			/*根据球的位置有两种y轴坐标相反的站位情况，y值为正时与默认值相反*/
			if (input.GetBall()._Loacion.GetY() > 0)
				ret.SetY(-ret.GetY());

			/* 处理结果是机器应该有的[位置]和[弧度] */
			/*其中机器朝向均为朝向球*/
			return std::make_pair(ret.AngleTo(input.GetBall()._Loacion), ret);
		}

	private:

		/* 需要预先读取的数据都在这里 */

		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
	};

	/**
	*	\brief	AntiThrowIn行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]靠近防守1
	*			[1]靠近防守2（0、1两台机器来封锁传球以及紧逼防守）
	*			[2]远处防守（防止传出球后来不及到另半边防守）
	*			[3]中线为止随时防守反击
	*
	*
	*	//TODO：此处的防守站位有两种优化方案待实现：
	*			1.根据黑障(即敌方球员站位)分配，尽量做到防守和阻碍传球兼备
	*			2.可以根据球的坐标和场地大小等的实际情况，进行数学建模，得到防守站位与球位置的对应关系函数，以此来分配站位(前提为黑障信息不准确，且此处可能涉及遗传算法)
	*/
	class AntiThrowIn : public EvaluatorForKick{

	public:
		AntiThrowIn()
			: _TargetLocation()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("AntiThrowIn", "Target2D", _TargetLocation);
		}

	public:

		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			/* 评估值越高越适合做这件事，支持负的评估值 */

			Vec2D <float> delta(0, 0);

			/*0、1号位根据球位置加固定向量值获得*/
			if (task == 0 || task == 1)
				delta += input.GetBall()._Loacion;

			/*根据球的y轴坐标翻转目标点的y值*/
			if (input.GetBall()._Loacion.GetY() > 0)
				delta.SetY(-delta.GetY());

			delta += _TargetLocation[task];

			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(delta) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/* 这里机器角色号等于任务编号 */

			Vec2D <float> ret(0, 0);

			/*0、1号位根据球位置加固定向量值获得*/
			if (index == 0 || index == 1)
				ret += input.GetBall()._Loacion;

			/*根据球的y轴坐标翻转目标点的y值*/
			if (input.GetBall()._Loacion.GetY() > 0)
				ret.SetY(-ret.GetY());

			ret += _TargetLocation[index];

			/* 处理结果是机器应该有的[位置]和[弧度] */
			/*其中机器朝向均为朝向球*/
			return std::make_pair(ret.AngleTo(input.GetBall()._Loacion), ret);
		}

	private:

		/* 需要预先读取的数据都在这里 */
		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
	};

	/**
	*	\brief	AntiFreeKick行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]主防守队员（球与己方球门中点连线距球较近一点）
	*			[1]侧应防守队员（球的坐标在y轴作调整）
	*			[2]补后方空场（球在后场就去与球y坐标相反的位置，球在前场就去与球y坐标相同的位置）
	*			[3]位置补充（球在后场就去中线附近打防守反攻，球在前场就和2一起补后场空位）
	*
	*	//TODO:之后更加精细的修改策略参照AntiThrowIn
	*
	*/
	class AntiFreeKick : public EvaluatorForKick{

	public:
		AntiFreeKick()
			: _TargetLocation()
			, _HasCalculated()
			, _Target()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("AntiFreeKick", "Target2D", _TargetLocation);

			int numMax = 0;
			TheLeafData::Instance()->getValue<int>("Settings", "AgentMaxNum", numMax);
			_Target = std::move(std::vector < Vec2D<float> >(numMax));
			_HasCalculated = std::move(std::vector < bool >(numMax));
		}

	public:

		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			/* 评估值越高越适合做这件事，支持负的评估值 */

			Vec2D <float> delta(input.GetBall()._Loacion);

			if (!_HasCalculated[task]){
				switch (task)
				{
				case 0:
					delta += Vec2D<float>(delta.AngleTo(_TargetLocation[task]), 350, true);
					break;
				case 1:
					if (delta.GetY() > 0)
						delta += _TargetLocation[task];
					else
						delta -= _TargetLocation[task];
					break;
				case 2:
					if (delta.GetX() > 0)
						delta.SetX(-delta.GetX());
					else
						if (delta.GetY() > 0)
							delta += _TargetLocation[task];
						else {
							delta.SetX(delta.GetX() + _TargetLocation[task].GetX());
							delta.SetY(delta.GetY() - _TargetLocation[task].GetY());
						}
						break;
				case 3:
					if (delta.GetX() > 0)
						delta = Vec2D<float>(0, 0) - delta;
					else
						delta = _TargetLocation[task];
					break;
				}
			}
	
			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(delta) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/*队员位置分配点*/
			Vec2D <float> ret(_Target[index]);

			_HasCalculated[index] = false;

			/* 处理结果是机器应该有的[弧度]和[位置] */
			/*其中机器朝向均为朝向球*/
			return std::make_pair(ret.AngleTo(input.GetBall()._Loacion), ret);
		}

	private:
		/* 需要预先读取的数据都在这里 */
		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */

		std::vector<bool> _HasCalculated;			/**< 检查是否计算完成 */
		std::vector<Vec2D<float>> _Target;			/**< 计算得到的目标点 */
	};

	/**
	*	\brief	AntiGoalKick行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]前场站位1
	*			[1]前场站位2
	*			[2]中场站位
	*			[3]后场站位
	*			
	*			//TODO：本策略为纯定点站位，可参照AntiThrowIn继续优化
	*/
	class AntiGoalKick : public EvaluatorForKick{

	public:
		AntiGoalKick()
			: _TargetLocation()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("AntiGoalKick", "Target2D", _TargetLocation);
		}

	public:

		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(_TargetLocation[task]) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			/*队员位置分配点*/
			Vec2D <float> ret(_TargetLocation[index]);

			/* 处理结果是机器应该有的[弧度]和[位置] */
			/*其中机器朝向均为朝向球*/
			return std::make_pair(ret.AngleTo(input.GetBall()._Loacion), ret);
		}

	private:
		/* 需要预先读取的数据都在这里 */
		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
	};

	/**
	*	\brief	DropBall行为中，分配任务的权值计算以及需要走到的目标点。
	*
	*			任务分配如下:
	*			[0]执行抢球操作
	*			[1]抢到球后的第一接球者（球坐标做y轴方向上的变换）
	*			[2]球与x轴对称的另外半场补位
	*			[3]根据球位置调整为进攻位置或防守位置（球在中前场防守姿态，球在后场进攻姿态）
	*/
	class DropBall : public EvaluatorForKick{
	public:
		DropBall()
			: _TargetLocation()
			, _Target4th()
		{
			TheLeafData::Instance()->getValue<Vec2D<float>>("DropBall", "Target2D", _TargetLocation);
			TheLeafData::Instance()->getValue<Vec2D<float>>("DropBall", "Target4th", _Target4th);
		}

	public:

		virtual int Assignment
			(const InputData & input, const int index, const int task) override
		{
			/* 评估值越高越适合做这件事，支持负的评估值 */

			Vec2D <float> delta(input.GetBall()._Loacion);

			/*0、1、2根据球的位置确定站位；3号根据当前形势适当补充空缺位置*/
			if (task != 0)
				delta += _TargetLocation[task];
			else
				if (input.GetBall()._Loacion.GetX() > -300)
					delta = _Target4th[0];		/*防守姿态*/
				else
					delta = _Target4th[1];		/*进攻姿态*/

			/* 计算结果 */
			return -(int)input.GetAgents()[index]._Loacion.Distance(delta) * 10;
		}

		virtual std::pair<double, Vec2D<float>> KeepInPosition
			(const InputData & input, const int index) override
		{
			Vec2D <float> ret(input.GetBall()._Loacion);

			/*0、1、2根据球的位置确定站位；3号根据当前形势适当补充空缺位置*/
			if (index != 0)
				ret += _TargetLocation[index];
			else
				if (input.GetBall()._Loacion.GetX() > -300)
					ret = _Target4th[0];		/*防守姿态*/
				else
					ret = _Target4th[1];		/*进攻姿态*/

			/* 处理结果是机器应该有的[位置]和[弧度] */
			/*其中机器朝向均为朝向球*/
			return std::make_pair(ret.AngleTo(input.GetBall()._Loacion), ret);
		}
	private:
		std::vector<Vec2D<float>> _TargetLocation;	/**< _TargetLocation[i]即第i个目标点的坐标 */
		std::vector<Vec2D<float>> _Target4th;			/**< _TargetLocation[i]即第i个目标点的坐标 */
	};
}
