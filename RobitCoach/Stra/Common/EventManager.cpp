#include <typeinfo>
#include <algorithm>

#include "EventManager.h"

EventManager::
EventManager()
	: _IsDispatching(false)
	, _EventQueue()
	, _ToBeAdded()
	, _ToBeDeleted()
	, _ListenerLists()
{}


void EventManager::
clean()
{
	if (_IsDispatching == false) {
		_EventQueue.clear();
		_ToBeAdded.clear();
		_ToBeDeleted.clear();
		_ListenerLists.clear();
	}
}

void EventManager::
sendEvent(const Event * Event)
{
	_EventQueue.push_back(Event);
}

void EventManager::
dispatch()
{
	/* [0]lock */
	_IsDispatching = true;

	/* [1]分发事件 */
	while (!_EventQueue.empty()) {

		auto frontEvent = _EventQueue.front();
		_EventQueue.pop_front();

		auto & listeners = _ListenerLists[typeid(*frontEvent).name()];

		for (auto & it : listeners) {
			it->trigger(frontEvent);
		}

		delete frontEvent;
	}

	/* [2]检查是否有监听被取消 */
	while (!_ToBeDeleted.empty()) {
		auto frontEvent = _ToBeDeleted.front();
		_ToBeDeleted.pop_front();
		auto index = frontEvent.first;
		auto listener = frontEvent.second;

		if (listener != nullptr) {
			auto it = std::find(_ListenerLists[index].begin(), _ListenerLists[index].end(), listener);
			if (it != _ListenerLists[index].end())
				it = _ListenerLists[index].erase(it);
		} else {
			_ListenerLists[index].clear();
		}
	}

	/* [3]检查是否有监听被加入 */
	while (!_ToBeAdded.empty()) {
		_ListenerLists[_ToBeAdded.front().first].push_back(_ToBeAdded.front().second);
		_ToBeAdded.pop_front();
	}

	/* [4]unlock */
	_IsDispatching = false;
}


void EventManager::
addListener(const char * index, const ListenerBase * listener)
{
	if (_IsDispatching)
		_ToBeAdded.push_back(std::make_pair(index, listener));
	else
		_ListenerLists[index].push_back(listener);
}


void EventManager::
deleteListener(const char * index, const ListenerBase * listener)
{
	if (_IsDispatching) {
		_ToBeDeleted.push_back(std::make_pair(index, listener));
	} else {
		if (listener != nullptr) {
			auto it = std::find(_ListenerLists[index].begin(), _ListenerLists[index].end(), listener);
			if (it != _ListenerLists[index].end())
				it = _ListenerLists[index].erase(it);
		} else {
			_ListenerLists[index].clear();
		}
	}
}