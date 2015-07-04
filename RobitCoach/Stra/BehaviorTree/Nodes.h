/*********************************************************************
 *	@file		Nodes.h
 *	@brief		Classes for BehaviorTree's nodes.
 *
 *	Date        Name        Description
 *	01/03/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <map>
#include <list>
#include <string>

#include "AnyDataRef.h"


// v for debug
//#define private public
//#define protected public
// ^ for debug



namespace BehaviorTree {

	enum NodeStatus {
		NODE_STATUS_RUNNING,
		NODE_STATUS_SUCCEED,
		NODE_STATUS_FAILED,
	};	/**< return value of each node */
	
	/**
	 *	\brief	A base class, Node.
	 */
	class Node {
	
	public:


	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/
		
		/**
		 *	\brief Constructor
		 */
		Node();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Node();
		
		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/
		
		/**
		 *	\brief	prue virtual Process, process itself and all child nodes.
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&) = 0;
		
		/**
		 *	\brief	prue virtual Reset, reset itself and all child nodes.
		 */
		virtual void Reset() = 0;



	};


	/**
	 *	\brief	A base class, for Action \ Condition.
	 */
	class Leaf : public Node {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/
		
		/**
		 *	\brief Constructor
		 */
		Leaf();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Leaf();

	};

	/**
	 *	\brief	A base class, Condition.
	 *			user defined condition based on it.
	 */
	class Condition : public Leaf {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		Condition();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Condition();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process, Check the condition
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&);

		/**
		 *	\brief	prue virtual Reset, reset itself.
		 */
		virtual void Reset();


	private:

		/*==========================================================================*/
		/*	private Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	prue virtual Check, is true ?
		 *
		 *	\param	input
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Check(const BehaviorTreeInput&) = 0;
	};


	/**
	 *	\brief	A base class, Action.
	 *			user defined Action based on it.
	 */
	class Action : public Leaf {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		Action();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Action();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process, Check the condition
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&);

		/**
		 *	\brief	prue virtual Reset, reset itself.
		 */
		virtual void Reset();

	private:

		/*==========================================================================*/
		/*	private Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	prue virtual OnEnter, 
		 *			it will be called the first time running it.
		 *
		 *	\param	input
		 *	\param	output	
		 */
		virtual void OnEnter(const BehaviorTreeInput&, BehaviorTreeOutput&) = 0;
		
		/**
		 *	\brief	prue virtual OnRunning, Check the condition
		 *
		 *	\param	input
		 *	\param	output
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus OnRunning(const BehaviorTreeInput&, BehaviorTreeOutput&) = 0;
		
		/**
		 *	\brief	prue virtual OnExit, 
		 *			it will be called when leaving this node.
		 */
		virtual void OnExit() = 0;

	private:

		/*==========================================================================*/
		/*	private Variables / Constants											*/
		/*==========================================================================*/
		bool _IsReady;				/**< Check if it's the first time runnning it. */
	};


	/**
	 *	\brief	A base class, Decorator
	 *			it has only one child node.
	 */
	class Decorator : public Node {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		Decorator();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Decorator();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&) override;

		/**
		 *	\brief	Set a child node
		 *
		 *	\param	node,	its child node.
		 */
		void SetChildNode(Node*);


	private:

		/*==========================================================================*/
		/*	private Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	Delete the child node
		 */
		inline void DeleteChildNode(void);

	private:

		/*==========================================================================*/
		/*	private Variables / Constants											*/
		/*==========================================================================*/
		Node * _ChildNode;					/**< the only child node */
	};


	/**
	 *	\brief	A Decorator class,
	 *			keep returning running until its child return failed.
	 */
	class Loop : public Decorator {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		Loop();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Loop();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus 类似while, 遇到 failed将会返回succeed，否则将持续执行 
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&) override;

		/**
		 *	\brief	virtual Reset, reset itself and all child nodes
		 */
		virtual void Reset() override;

	};

	/**
	 *	\brief	A Decorator class,
	 *			!Decorator::Process(); 
	 */
	class Inverter : public Decorator {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		Inverter();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Inverter();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&) override;

		/**
		 *	\brief	virtual Reset, reset itself and all child nodes
		 */
		virtual void Reset() override;

	};


	/**
	 *	\brief	A base class, Composite
	 */
	class Composite : public Node {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		Composite();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Composite();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/
		
		/**
		 *	\brief	Add a child node to *this
		 */
		void AddChildNode(Node*);


	protected:

		/*==========================================================================*/
		/*	private Variables / Constants											*/
		/*==========================================================================*/
		std::list<Node *> _ChildNodes;				/**< list of child nodes */
	};

	/**
	 *	\brief	A base class, LinearComposite,
	 *			they will process its child nodes one by one,
	 */
	class LinearComposite : public Composite {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		LinearComposite();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~LinearComposite();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Reset, reset itself and all child nodes
		 */
		virtual void Reset() override;


	protected:
		/*==========================================================================*/
		/*	protected Variables / Constants											*/
		/*==========================================================================*/
		std::list<Node *>::iterator _CurrentNode;	/**< only current node is running */

	};

	/**
	 *	\brief	Class Sequence
	 *			similar to "&&", and process its child nodes one by one,
	 *			return failed until a child node return failed, or return succeed.
	 */
	class Sequence : public LinearComposite {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		Sequence();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Sequence();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process, process Sequence
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&) override;

	};

	/**
	 *	\brief	Class Selector
	 *			similar to "||", and process its child nodes one by one,
	 *			return succeed until a child node return succeed, or return failed.
	 */
	class Selector : public LinearComposite {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		Selector();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~Selector();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&) override;

	};


	/**
	 *	\brief	A base class, ParallelComposite,
	 *			they will process all child nodes at the same time,
	 */
	class ParallelComposite : public Composite {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		ParallelComposite();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~ParallelComposite();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Reset, reset itself and all child nodes
		 */
		virtual void Reset() override;

	protected:
		/*==========================================================================*/
		/*	protected Variables / Constants											*/
		/*==========================================================================*/
		std::list<Node *> _PendingNodes;		/**< those nodes all keep runnning */
	};


	/**
	 *	\brief	Class ParallelSequence,
	 *			it process all child nodes at the same time,
	 *			when there is a child node returning failed, it return failed
	 */
	class ParallelSequence : public ParallelComposite {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		ParallelSequence();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~ParallelSequence();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&) override;

	};

	/**
	 *	\brief	Class ParallelSelector,
	 *			it process all child nodes at the same time,
	 *			when there is a child node returning succeed, it return succeed
	 */
	class ParallelSelector : public ParallelComposite {

	public:

		/*==========================================================================*/
		/*	public Constructor \ Destructor											*/
		/*==========================================================================*/

		/**
		 *	\brief Constructor
		 */
		ParallelSelector();

		/**
		 *	\brief	virtual Destructor
		 */
		virtual ~ParallelSelector();

		/*==========================================================================*/
		/*	public Methods															*/
		/*==========================================================================*/

		/**
		 *	\brief	virtual Process
		 *
		 *	\param	input
		 *	\param	output	
		 *
		 *	\return	NodeStatus
		 */
		virtual NodeStatus Process(const BehaviorTreeInput&, BehaviorTreeOutput&) override;

	};

}

// v for debug
#undef private
#undef protected
// ^ for debug


