/*********************************************************************
 *	@file		StateMachine.h
 *	@brief		简单的有限状态机，用于控制流程
 *				
 *
 *	Date        Name        Description
 *	20/05/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once


#include <vector>

#include "State.h"

/**
 *	\brief	StateMachine
 *
 *			A Finite State Machine
 */
class StateMachine {

public:

	/**
	 *	\brief Constructor
	 */
	StateMachine();

	/**
	 *	\brief	Destructor
	 */
	~StateMachine();

public:

	/**
	 *	\brief	clean the StateMachine, clean all States, release resources.
	 */
	void clean();

	/**
	 *	\brief	push a state in the FSM
	 *
	 *	\param	pState			State will be added on the top.
	 */
	void push(State* pState);

	/**
	 *	\brief	change the top state of FSM
	 *
	 *	\param	pState			pop the old and add a new state on the top.
	 */
	void change(State* pState);

	/**
	 *	\brief	pop the top state of FSM
	 */
	void pop();

	/**
	 *	\brief	update the top state of FSM
	 */
	void update(float deltaTime);

	/**
	 *	\brief	Run the top state of FSM
	 */
	void render();

	/**
	 *	\brief	get current top State
	 *
	 *	\return the top state of FSM
	 */
	State * getCurState();

	/**
	 *	\brief	Check whether the FMS is empty
	 *
	 *	\return true for empty, or false for not
	 */
	bool empty();

private:

	std::vector<State*> _States;				/**< Vector as stack */
};



