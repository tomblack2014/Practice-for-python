/*********************************************************************
 *	@file		NodeFactory.cpp
 *	@brief		Class NodeFactory的具体实现。
 *
 *
 *	Date        Name        Description
 *	01/03/15	MYLS		Creation.
 *
 *********************************************************************/

#include "CustomNodes.h"
#include "NodeFactory.h"

namespace BehaviorTree {

	NodeFactory::
	NodeFactory() 
	{
		/* default */
		Register<Sequence>("Sequence");
		Register<Selector>("Selector");
		Register<ParallelSequence>("ParallelSequence");
		Register<ParallelSelector>("ParallelSelector");

		Register<Loop>("Loop");
		Register<Inverter>("Inverter");
	
		/* custom */
		Register<Condition_IsKick>("Condition_IsKick");
		Register<Action_Kick_Assignment>("Action_Kick_Assignment");
		Register<Action_Kick_KeepInPosition>("Action_Kick_KeepInPosition");
		Register<Condition_IsStartPass>("Condition_IsStartPass");
		Register<Action_StartPass_Assignment>("Action_StartPass_Assignment");
		Register<Action_StartPass>("Action_StartPass");
		Register<Condition_IsAntiStart>("Condition_IsAntiStart");
		Register<Action_AntiStart_Assignment>("Action_AntiStart_Assignment");
		Register<Action_AntiStart>("Action_AntiStart");
		Register<Condition_IsAuto>("Condition_IsAuto");
		Register<Action_Auto_Assignment>("Action_Auto_Assignment");
		Register<Action_Auto_CatchBall>("Action_Auto_CatchBall");
		Register<Condition_IsDefending>("Condition_IsDefending");
		Register<Action_Defend_Assignment>("Action_Defend_Assignment");
		Register<Action_Defend_Use_Default_Plan>("Action_Defend_Use_Default_Plan");
		Register<Condition_IsAttacking>("Condition_IsAttacking");
		Register<Action_Attack_Assignment>("Action_Attack_Assignment");
		Register<Action_Attack_Use_Default_Plan>("Action_Attack_Use_Default_Plan");
		Register<Condition_IsPassing>("Condition_IsPassing");
		Register<Action_Pass_Assignment>("Action_Pass_Assignment");
		Register<Action_Pass>("Action_Pass");
		Register<Condition_IsStop>("Condition_IsStop");
		Register<Action_AllStop>("Action_AllStop");
	}


}

