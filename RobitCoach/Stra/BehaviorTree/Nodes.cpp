/*********************************************************************
 *	@file		Nodes.cpp
 *	@brief		行为树中各种节点，(不变的部分)，的具体实现。
 *
 *
 *	Date        Name        Description
 *	01/03/15	MYLS		Creation.
 *
 *********************************************************************/

#include "Nodes.h"

namespace BehaviorTree {

	/////////////////////////////////////////////////////////////////////////////
	///  Node                                                                 ///
	/////////////////////////////////////////////////////////////////////////////

	Node::
	Node()
	{}

	Node::
	~Node()
	{}

	/////////////////////////////////////////////////////////////////////////////
	///  Leaf                                                                 ///
	/////////////////////////////////////////////////////////////////////////////

	Leaf::
	Leaf() : 
		Node()
	{}

	Leaf::
	~Leaf()
	{}

	/////////////////////////////////////////////////////////////////////////////
	///  Condition                                                            ///
	/////////////////////////////////////////////////////////////////////////////

	Condition::
	Condition() : 
		Leaf()
	{}

	Condition::
	~Condition()
	{}

	NodeStatus Condition::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput&)
	{
		return Check(inputRef);
	}

	void Condition::
	Reset()
	{}

	/////////////////////////////////////////////////////////////////////////////
	///  Action                                                               ///
	/////////////////////////////////////////////////////////////////////////////

	Action::
	Action() :
		Leaf(),
		_IsReady(false)
	{}

	Action::
	~Action()
	{}

	NodeStatus Action::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef)
	{
		NodeStatus ret = NODE_STATUS_RUNNING;
		if (!_IsReady) {
			OnEnter(inputRef, outputRef);
			_IsReady = true;
		}

		ret = OnRunning(inputRef, outputRef);
		if (ret != NODE_STATUS_RUNNING) {
			OnExit();
			_IsReady = false;
			/* Action is over && Reset all */
			Reset();
		}

		return ret;
	}

	void Action::
	Reset()
	{
		if (_IsReady) {
			OnExit();
			_IsReady = false;
		}
	}


	/////////////////////////////////////////////////////////////////////////////
	///  Decorator                                                            ///
	/////////////////////////////////////////////////////////////////////////////

	Decorator::
	Decorator() :
		_ChildNode(nullptr)
	{}

	Decorator::
	~Decorator()
	{
		DeleteChildNode();
		_ChildNode = nullptr;
	}

	NodeStatus Decorator::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef)
	{

		if (_ChildNode == nullptr)
			return NODE_STATUS_FAILED;
		else
			return _ChildNode->Process(inputRef, outputRef);
	}

	void Decorator::
	SetChildNode(Node * ptrChildNode)
	{
		DeleteChildNode();
		_ChildNode = ptrChildNode;
	}

	void Decorator::
	DeleteChildNode()
	{
		if (_ChildNode != nullptr)
			delete _ChildNode;
	}

	/////////////////////////////////////////////////////////////////////////////
	///  Loop													  ///
	/////////////////////////////////////////////////////////////////////////////

	Loop::
	Loop() :
		Decorator()
	{}

	Loop::
	~Loop() {}


	NodeStatus Loop::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef)
	{

		if (Decorator::Process(inputRef, outputRef) == NODE_STATUS_FAILED)
			return NODE_STATUS_SUCCEED;
		else
			return NODE_STATUS_RUNNING;
	}

	void Loop::
	Reset()
	{}


	/////////////////////////////////////////////////////////////////////////////
	///  Inverter															  ///
	/////////////////////////////////////////////////////////////////////////////

	Inverter::
	Inverter() :
		Decorator()
	{}

	Inverter::
	~Inverter() {}


	NodeStatus Inverter::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef)
	{
		auto ret = Decorator::Process(inputRef, outputRef);
		switch (ret) {	
		case NODE_STATUS_FAILED:
			ret = NODE_STATUS_SUCCEED;
			break;
		case NODE_STATUS_SUCCEED:
			ret = NODE_STATUS_FAILED;
			break;
		default:
			break;
		}

		return ret;
	}

	void Inverter::
	Reset()
	{}


	/////////////////////////////////////////////////////////////////////////////
	///  Composite                                                            ///
	/////////////////////////////////////////////////////////////////////////////

	Composite::
	Composite() :
		_ChildNodes()
	{}

	Composite::
	~Composite()
	{
		for (auto & it : _ChildNodes)
			if (it != nullptr)
				delete it;
		_ChildNodes.clear();
	}

	void Composite::
	AddChildNode(Node * ptrChildNode)
	{
		if (ptrChildNode != nullptr)
			_ChildNodes.push_back(ptrChildNode);
	}

	/////////////////////////////////////////////////////////////////////////////
	///  LinearComposite                                                      ///
	/////////////////////////////////////////////////////////////////////////////

	LinearComposite::
	LinearComposite() :
		_CurrentNode(_ChildNodes.end())
	{}

	LinearComposite::
	~LinearComposite()
	{}

	void LinearComposite::
	Reset()
	{
		if (_CurrentNode != _ChildNodes.end()) {
			(*_CurrentNode)->Reset();
			_CurrentNode = _ChildNodes.end();
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	///  Sequence(Linear)                                                     ///
	/////////////////////////////////////////////////////////////////////////////

	Sequence::
	Sequence()
	{}

	Sequence::
	~Sequence()
	{}

	NodeStatus Sequence::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef)
	{
		if (_ChildNodes.empty())
			/* when list is empty */
			return NODE_STATUS_SUCCEED;

		if (_CurrentNode == _ChildNodes.end())
			/* first time running it */
			_CurrentNode = _ChildNodes.begin();

		while (_CurrentNode != _ChildNodes.end()) {
			auto ret = (*_CurrentNode)->Process(inputRef, outputRef);

			switch (ret) {
			case NODE_STATUS_RUNNING:
				return ret;
			case NODE_STATUS_SUCCEED:
				_CurrentNode++;
				break;
			case NODE_STATUS_FAILED:
				/* sequence succeeds && Reset all */
				Reset();
				return ret;
			default:
				break;
			}
		}

		if (_CurrentNode == _ChildNodes.end()) {
			/* sequence is over && Reset all */
			Reset();
			return NODE_STATUS_SUCCEED;
		}

		return NODE_STATUS_RUNNING;
	}

	/////////////////////////////////////////////////////////////////////////////
	///  Selector(Linear)                                                     ///
	/////////////////////////////////////////////////////////////////////////////

	Selector::
	Selector()
	{}

	Selector::
	~Selector()
	{}

	NodeStatus Selector::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef)
	{
		if (_ChildNodes.empty())
			/* when list is empty */
			return NODE_STATUS_FAILED;

		if (_CurrentNode == _ChildNodes.end())
			/* first time running it */
			_CurrentNode = _ChildNodes.begin();

		while (_CurrentNode != _ChildNodes.end()) {
			auto ret = (*_CurrentNode)->Process(inputRef, outputRef);

			switch (ret) {
			case NODE_STATUS_RUNNING:
				return ret;
			case NODE_STATUS_FAILED:
				_CurrentNode++;
				break;
			case NODE_STATUS_SUCCEED:
				/* selector succeeds && Reset all */
				Reset();
				return ret;
			default:break;
			}
		}

		if (_CurrentNode == _ChildNodes.end()) {
			/* selector is end && Reset all */
			Reset();
			return NODE_STATUS_FAILED;
		}

		return NODE_STATUS_RUNNING;
	}

	/////////////////////////////////////////////////////////////////////////////
	///  ParallelComposite                                                    ///
	/////////////////////////////////////////////////////////////////////////////

	ParallelComposite::
	ParallelComposite() :
		_PendingNodes()
	{}

	ParallelComposite::
	~ParallelComposite()
	{
		if (!_PendingNodes.empty())
			for (auto & it : _PendingNodes)
				if (it != nullptr) {
					delete it;
					it = nullptr;
				}
		_PendingNodes.clear();
	}

	void ParallelComposite::
	Reset()
	{
		for (auto & i : _PendingNodes)
			i->Reset();
		_PendingNodes.clear();
	}

	/////////////////////////////////////////////////////////////////////////////
	///  ParallelSequence                                                     ///
	/////////////////////////////////////////////////////////////////////////////

	ParallelSequence::
	ParallelSequence()
	{}

	ParallelSequence::
	~ParallelSequence()
	{}

	NodeStatus ParallelSequence::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef)
	{
		if (_ChildNodes.empty())
			/* when list is empty */
			return NODE_STATUS_SUCCEED;

		if (_PendingNodes.empty())
			/* first time process it */
			_PendingNodes = _ChildNodes;

		for (auto it = _PendingNodes.begin(); it != _PendingNodes.end();) {
			auto ret = (*it)->Process(inputRef, outputRef);

			switch (ret) {
			case NODE_STATUS_RUNNING:
				it++;
				break;
			case NODE_STATUS_FAILED:
				Reset();
				return ret;
			case NODE_STATUS_SUCCEED:
				it = _PendingNodes.erase(it);
				break;
			default:break;
			}
		}

		if (_PendingNodes.empty()) {
			Reset();
			return NODE_STATUS_SUCCEED;
		}

		return NODE_STATUS_RUNNING;
	}

	/////////////////////////////////////////////////////////////////////////////
	///  ParallelSelector                                                     ///
	/////////////////////////////////////////////////////////////////////////////

	ParallelSelector::
	ParallelSelector()
	{}

	ParallelSelector::
	~ParallelSelector()
	{}

	NodeStatus ParallelSelector::
	Process(const BehaviorTreeInput& inputRef, BehaviorTreeOutput& outputRef)
	{
		if (_ChildNodes.empty())
			/* when list is empty */
			return NODE_STATUS_FAILED;

		if (_PendingNodes.empty())
			/* first time process it */
			_PendingNodes = _ChildNodes;

		for (auto it = _PendingNodes.begin(); it != _PendingNodes.end();) {
			auto ret = (*it)->Process(inputRef, outputRef);
			
			switch (ret) {
			case NODE_STATUS_RUNNING:
				it++;
				break;
			case NODE_STATUS_SUCCEED:
				Reset();
				return ret;
			case NODE_STATUS_FAILED:
				it = _PendingNodes.erase(it);
				break;
			default:break;
			}
		}

		if (_PendingNodes.empty()) {
			Reset();
			return NODE_STATUS_FAILED;
		}

		return NODE_STATUS_RUNNING;
	}

}
