/*********************************************************************
 *	@file		EventManager.h
 *	@brief		事件管理器，用于分发各种事件
 *
 *
 *	Date        Name        Description
 *	21/05/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <list>
#include <iostream>
#include <type_traits>
#include <unordered_map>

#include "Event.h"
#include "EventListener.h"

/**
 *	\brief	事件管理者，负责分发事件
 */
class EventManager {

public:

	/**
	 *	\brief	默认构造函数
	 */
	EventManager();

public:

	/**
	 *	\brief	清除所有事件，释放资源
	 */
	void clean();

	/**
	 *	\brief	分发事件，执行事件对应listener的操作
	 */
	void dispatch();

	/**
	 *	\brief 发送一个事件
	 *
	 *	\param	eventObj	被发送的事件
	 */
	void sendEvent(const Event * eventObj);
	
	/**
	 *	\brief	注册一个listener<T>，T为被监听事件的类型
	 *
	 *	\param	listener	事件监听者
	 */
	template<typename T> void registerListener(const ListenerBase * listener);

	/**
	 *	\brief	清除一个listener<T>，T为被监听事件的类型
	 *
	 *	\param	listener	事件监听者，如果为nullptr，将会清除那个事件的所有监听者
	 */
	template<typename T> void removeListener(const ListenerBase * listener = nullptr);

private:

	/**
	 *	\brief	添加一个listener，将会被registerListener调用
	 *
	 *	\param	type		事件类型的名字
	 *	\param	listener	事件监听者
	 */
	void addListener(const char * type, const ListenerBase * listener);

	/**
	 *	\brief	删除listener，将会被removeListener调用
	 *
	 *	\param	type		事件类型的名字
	 *	\param	listener	事件监听者
	 */
	void deleteListener(const char * type, const ListenerBase * listener);

private:

	bool _IsDispatching;								/**< 判断当前是否正在处理事件 */
	std::list<const Event *> _EventQueue;				/**< 正在处理的事件 */
	std::list<std::pair<const char *, const ListenerBase *>> _ToBeAdded;	/**< 将要被增加的事件 */
	std::list<std::pair<const char *, const ListenerBase *>> _ToBeDeleted;	/**< 将要被删除的事件 */
	std::unordered_map<const char *, std::list<const ListenerBase *>> _ListenerLists;	/**< 事件监听者的列表 */
};



template<typename EventType> void EventManager::
registerListener(const ListenerBase * listener)
{
	if (listener != nullptr && dynamic_cast<const EventListener<EventType> *>(listener))
		addListener(typeid(EventType).name(), listener);
	else
		std::cerr << "EventManager:: Unsupport Listener Type!" << std::endl;
}

template<typename EventType> void EventManager::
removeListener(const ListenerBase * listener)
{
	if (listener == nullptr || dynamic_cast<const EventListener<EventType> *>(listener))
		deleteListener(typeid(EventType).name(), listener);
}

