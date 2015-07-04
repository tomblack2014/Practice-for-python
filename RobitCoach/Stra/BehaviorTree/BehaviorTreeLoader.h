/*********************************************************************
 *	@file		BehaviorTreeLoader.h
 *	@brief		装载行为树头文件，会用到tinyXML
 *
 *
 *	Date        Name        Description
 *	01/03/15	MYLS		Creation.
 *
 *********************************************************************/

 #pragma once

#include <string>

#define TIXML_USE_STL

//#ifdef _DEBUG
//#pragma comment(lib, "../Debug/tinyxmlSTL.lib")
//#else
//#pragma comment(lib, "../Release/tinyxmlSTL.lib")
//#endif

#include "../tinyxml/tinyxml.h"

#include "Nodes.h"
#include "NodeFactory.h"


/**
 *	\brief	行为树使用的命名空间
 *
 *			包含类BehaviorTree
 */
namespace BehaviorTree {
	
	/**
	 *	\brief	装载行为树的类
	 *
	 *			通过链接xml链接库，完成树的可视化构建
	 */
	class BehaviorTreeLoader {

	public:

		/*==========================================================================*/
		/*	公有 构造\析构\操作符重载													*/
		/*==========================================================================*/

		/**
		 *	\brief 构造函数
		 *
		 *	\param	filePath  含有树型图的xml文件指针
		 */
		BehaviorTreeLoader(const std::string & filePath);

		/**
		 *	\brief 析构函数
		 *
		 */
		~BehaviorTreeLoader();

		/**
		 *	\brief 构造函数[重载]，拷贝树
		 *
		 *	\param	rhs  被拷贝的对象
		 */
		BehaviorTreeLoader(const BehaviorTreeLoader & rhs);

		/**
		 *	\brief 运算符重载
		 *
		 *	\param	rhs  等号右边的对象
		 */
		BehaviorTreeLoader & operator = (const BehaviorTreeLoader & rhs);

		/*==========================================================================*/
		/*	公有方法																	*/
		/*==========================================================================*/

		/**
		 *	\brief 创建行为树
		 *
		 *	\param	btName 行为树节点名，用于创建跟节点。(递归构建树)
		 *
		 *	\return	根节点
		 */
		Node * CreateBehaviorTree(const std::string & btName) const;

		/**
		 *	\brief 输出XML内容 （主要用于debug）
		 */
		void Print() const;


	private:

		/*==========================================================================*/
		/*	私有方法																	*/
		/*==========================================================================*/

		/**
		 *	\brief 创建行为树（重载）节点间连接
		 *
		 *	\param	pFirstChild		需要读取的XML文件对应节点
		 *	\param  pNode			行为树的父亲节点
		 *	\param  btType			当前节点类型
		 */
		void CreateBehaviorTreeNode(const TiXmlElement* pFirstChild, Node * & pNode, const std::string & btType) const;

		/*==========================================================================*/
		/*	私有 成员变量\常量														*/
		/*==========================================================================*/
		static char DEFAULT_NODE_ATTRIBUTE[];		/**< 静态变量，需要读取的标签名 */
		static char DEFAULT_NODE_COMPOSITE[];		/**< 静态变量，需要读取的标签名 */
		static char DEFAULT_NODE_DECORATOR[];		/**< 静态变量，需要读取的标签名 */

		TiXmlDocument _XMLDoc;						/**< 存储行为树的xml文件 */
		NodeFactory _NodeFactory;					/**< 工厂类 */
	};

}
