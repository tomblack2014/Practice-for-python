/*********************************************************************
 *	@file		CustomData.h
 *	@brief		自定义的需要输入\输出行为树的数据类型，
 *
 *	Date        Name        Description
 *	03/03/15	MYLS		Creation.
 *  06/03/15    ssj			Update
 *	23/06/15	TB			edit SwapAgent
 *
 *********************************************************************/
 #pragma once

#include <vector>
#include <list>
#include <algorithm>

#include "Stra/Common/Common.h"

namespace BehaviorTree {

	///////////////////////////////////////////////////////////////////
	///
	/// custom data types placed here
	///
	///////////////////////////////////////////////////////////////////

	enum GameStatus {
		GAME_STOP,
		GAME_START,

		GAME_DROP_BALL,
		
		GAME_THROW_IN,
		GAME_KICK_OFF,
		GAME_FREE_KICK,
		GAME_GOAL_KICK,
		GAME_CORNER_KICK,

		GAME_ANTI_THROW_IN,
		GAME_ANTI_KICK_OFF,
		GAME_ANTI_FREE_KICK,
		GAME_ANTI_GOAL_KICK,
		GAME_ANTI_CORNER_KICK,

		// TODO: 可以增加的其他状态
		GAME_AUTO,			/* 主要用于抢球，过渡为进攻和防守 */
		GAME_ATTACK,		/* 进攻，包括运球时传球 */
		GAME_DEFEND,		/* 防守状态 */
		GAME_PASS,			/* 用于进攻状态下的传球 */
		GAME_START_PASS,	/* 用于各种情况下的开球传球 */
		GAME_ANTI_START,	/* 应对对方在各种情况下的开球传球 */
	};

	struct Agent{
		Agent() : _ID(0), _Angle(0), _Loacion(), _Speed() {}

		int _ID;					/**< 从0开始 */
		double _Angle;				/**< 机器朝向 */
		Vec2D<float> _Loacion;		/**< 机器位置 */
		Vec2D<float> _Speed;			/**< (Vx, Vy)，单位：??? */
	};


	struct Ball{
		Ball() : _Owner(-1), _Loacion(), _Speed() {}
		
		int _Owner;					/**< 球所有者的ID。-1表示没有 */
		Vec2D<float> _Loacion;		/**< 球的位置，NO_LOCATION表示未找到球 */
		Vec2D<float> _Speed;			/**< (deltaX, deltaY) */

		static const Vec2D<float> NO_LOCATION;
	};


	struct Enemy{
		Enemy() : _Radius(0), _Loacion() {}

		int _Radius;				/**< 估计的大小 */
		Vec2D<float> _Loacion;		/**< 敌人的位置 */
	};


	///////////////////////////////////////////////////////////////////
	///
	/// MYLS's Define
	///
	///////////////////////////////////////////////////////////////////

	class InputData{

	public:

		InputData(
			GameStatus &gameStatus,
			Ball &ball,
			std::vector<Agent> &agents,
			std::vector<Enemy> &enemies)
		: _GameStatus(gameStatus)
		, _Ball(ball)
		, _Agents(agents)
		, _Enemies(enemies)
		{}

		const GameStatus & GetGameStatus() const		{ return _GameStatus;	}
		const Ball & GetBall() const					{ return _Ball;			}
		const std::vector<Agent> & GetAgents() const	{ return _Agents;		}
		const std::vector<Enemy> & GetEnemies() const	{ return _Enemies;		}

	private:

		GameStatus &_GameStatus;						/**< 当前比赛的状态 */
		Ball & _Ball;									/**< 球的相关信息 */
		std::vector<Agent> & _Agents;					/**< 己方球员相关信息 */
		std::vector<Enemy> & _Enemies;					/**< 敌方(黑障)相关信息 */

	};


	class OutputData{

	public:

		OutputData(
			GameStatus &gameStatus,
			std::vector<Agent> &agents,
			std::string & cmd)
		: _GameStatus(gameStatus)
		, _Agents(agents)
		, _Cmd(cmd)
		{}

		void SetGameStatus(const GameStatus gameStatus)	{ _GameStatus = gameStatus;						}
		void AddCMD(const std::string str)				{ _Cmd += str;									}
		void ClearCMD()									{ _Cmd.clear();									}
		const std::string & GetCMD() const				{ return _Cmd;									}
		void SwapAgent(int indexA, int indexB){
			/*最新加入错误检查*/
			if (indexA < 0 || indexB < 0 || indexA >= static_cast<int>(_Agents.size()) || indexB >= static_cast<int>(_Agents.size()))
				return;
			std::swap(_Agents[indexA], _Agents[indexB]); 
		}
		
	private:

		std::string	& _Cmd;
		GameStatus & _GameStatus;
		std::vector<Agent> & _Agents;

	};

}


