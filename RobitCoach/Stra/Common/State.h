/**********************************************************************
 *
 *	@file		State.h
 *	@brief		State, for StateMachine.
 *
 *	Date        Name        Description
 *	11/11/14	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

/**
 *	\brief	Abstract Class: State
 *
 *			StateMachine uses those classes as its elements;
 */

class State
{

public:

	/**
	 *	\brief	Virtual Destructor
	 */
    virtual ~State() {}
    
public:

	/**
	 *	\brief	Pure Virtual, update
	 *			Class StateMachine also has a "update()" function, 
	 *			and it will call "_States.back()->update()" in it's "update()".
	 */
    virtual void update(float deltaTime) = 0;

	/**
	 *	\brief	Pure Virtual, render
	 *			Similar to above.
	 */
    virtual void render() = 0;
    
	/**
	 *	\brief	Pure Virtual, OnEnter
	 *			When it is pushed onto the StateMachine.
	 *
	 *	\return	1 successful or 0 not.
	 */
    virtual bool onEnter() = 0;
    
	/**
	 *	\brief	Pure Virtual, OnExit
	 *			When it is out of the StateMachine.
	 *
	 *	\return	1 successful or 0 not.
	 */
	virtual bool onExit() = 0;

	/**
	 *	\brief	Pause
	 *			状态机将会保存这个状态，这里是保存之前的操作
	 *
	 *	\return	1 successful or 0 not.
	 */
	virtual bool Pause() = 0;

	/**
	 *	\brief	Pause
	 *			状态机将会恢复保存的这个状态，这里是恢复时候的操作
	 *
	 *	\return	1 successful or 0 not.
	 */
	virtual bool Resume() = 0;


protected:

	enum {
		ENTERING,
		RUNNING,
		EXITING,
	};
};

