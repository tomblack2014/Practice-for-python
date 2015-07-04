/*********************************************************************
 *	@file		EventListener.h
 *	@brief		事件的监听者
 *
 *
 *	Date        Name        Description
 *	21/05/15	MYLS		Creation.
 *
 *********************************************************************/
#pragma once

#include <type_traits>
#include "Event.h"

/**
 *	\brief 事件监听者 基类
 */
class ListenerBase {

	friend class EventManager;

public:

	/**
	 *	\brief  基类的虚析构函数
	 */
	virtual ~ListenerBase() {};

private:

	/**
	 *	\brief  将会检查并调用监听者的对应的操作
	 *	\param	eventObject	触发的事件
	 */
	virtual void trigger(const Event * eventObject) const = 0;

};

/**
 *	\brief 事件监听者
 */
template<class T> class EventListener : public ListenerBase {
	
	/**
	 *	\brief 执行监听者对应操作
	 *	\param	eventObject	被触发的事件
	 */
	inline virtual void process(const T * eventObject) const = 0;

	/**
	 *	\brief 将会检查并调用监听者的对应的操作
	 *	\param	eventObject	触发的事件
	 */
	virtual void trigger(const Event * eventObject) const override;
};



template<class T> void EventListener<T>::
trigger(const Event * eventObject) const
{
	static_assert(std::is_base_of<Event, T>::value, "EventListener:: T is not a Event");
	static_assert(std::is_convertible<T, Event>::value, "EventListener:: Cannot convert T to Event");
	auto theEvent = dynamic_cast<const T *>(eventObject);
	if (theEvent)
		process(theEvent);
}
