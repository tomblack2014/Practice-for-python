/*********************************************************************
 *	@file		Timer.cpp
 *	@brief		Implement of Timer.h
 *
 *	Date        Name        Description
 *	23/11/14	MYLS		Creation.
 *	08/12/14	MYLS		Modify comment.
 *
 *********************************************************************/


#include <time.h>

#include "Timer.h"


/*==========================================================================*/
/*	public Constructor \ Destructor											*/
/*==========================================================================*/

Timer::
Timer()
	: _Status(TIMER_STOP)
	, _TimePaused(0)
	, _TimeInitial(0)
{}

Timer::
~Timer()
{}


/*==========================================================================*/
/*	public Methods, Modify													*/
/*==========================================================================*/

void Timer::
Start(void)
{
	_Status = TIMER_RUNNINNG;
	_TimeInitial = clock();
	_TimePaused = 0;
}

void Timer::
Pause(void)
{
	if (_Status != TIMER_RUNNINNG)
		return;

	_Status = TIMER_PAUSED;
	_TimePaused = clock();
}

void Timer::
Resume(void)
{
	if (_Status != TIMER_PAUSED)
		return;

	_Status = TIMER_RUNNINNG;
	_TimeInitial += clock() - _TimePaused;
	_TimePaused = 0;
}

void Timer::
Stop(void)
{
	_Status = TIMER_STOP;
	_TimeInitial = 0;
	_TimePaused = 0;
}


/*==========================================================================*/
/*	public Methods, Query													*/
/*==========================================================================*/

unsigned int Timer::
GetElapsedTime(void) const
{
	switch (_Status) {
	case Timer::TIMER_STOP:
		return 0;
		break;
	case Timer::TIMER_RUNNINNG:
		return clock() - _TimeInitial;
		break;
	case Timer::TIMER_PAUSED:
		return _TimePaused - _TimeInitial;
		break;
	default:
		return 0;
		break;
	}
}


