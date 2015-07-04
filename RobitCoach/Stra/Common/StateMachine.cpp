/**********************************************************************
 *
 *	@file		StateMachine.cpp
 *	@brief		Implement of StateMachine.h.
 *
 *	Date        Name        Description
 *	11/11/14	MYLS		Creation.
 *
 *********************************************************************/

#include "StateMachine.h"

#include <typeinfo>

/*==========================================================================*/
/*	public Constructor \ Destructor											*/
/*==========================================================================*/

StateMachine::
StateMachine()
	: _States()
{}

StateMachine::
~StateMachine()
{}

/*==========================================================================*/
/*	public Methods, Modify													*/
/*==========================================================================*/

void StateMachine::
clean()
{
	if (!_States.empty()) {

		for (auto &it : _States) {
			it->onExit();
			delete it;
		}

		_States.erase(_States.begin(), _States.end());
	}
}

void StateMachine::
update(float deltaTime)
{
	if (!_States.empty()) {
		_States.back()->update(deltaTime);
	}
}

void StateMachine::
render()
{
	if (!_States.empty()) {
		_States.back()->render();
	}
}

void StateMachine::
push(State *pState)
{
	if (!_States.empty()) {
		_States.back()->Pause();
	}
	_States.push_back(pState);
	_States.back()->onEnter();
}

void StateMachine::
change(State *pState)
{
	if (!_States.empty()) {
		if (typeid(*_States.back()) == typeid(*pState)) {
			return;
		}

		_States.back()->onExit();
		_States.pop_back();
	}

	pState->onEnter();
	_States.push_back(pState);
}

void StateMachine::
pop()
{
	if (!_States.empty()) {
		_States.back()->onExit();
		_States.pop_back();
	}

	_States.back()->Resume();
}

State * StateMachine::
getCurState()
{
	return _States.back();
}

/*==========================================================================*/
/*	public Methods, Query													*/
/*==========================================================================*/

bool StateMachine::
empty()
{
	return _States.empty();
}
