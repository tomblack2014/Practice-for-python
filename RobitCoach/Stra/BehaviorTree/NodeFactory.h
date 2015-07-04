/*********************************************************************
 *	@file		NodeFactory.h
 *	@brief		工厂模式引用，用于创建形式多样的行为树节点
 *
 *
 *	Date        Name        Description
 *	01/03/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

//#include <Common/Common.h>
#include "Stra/Common/Common.h"

#include "Nodes.h"

namespace BehaviorTree {

	/**
	 *	\brief  行为树工厂，用于生成不同类型的Node.
	 */
	class NodeFactory : public AbsFactory<Node> {

	public:

		/*==========================================================================*/
		/*	公有 构造函数															*/
		/*==========================================================================*/

		/**
		 *	\brief 构造函数
		 *			需要在这里初始化支持的构造对象
		 */
		NodeFactory();

	};

}
