/*********************************************************************
 *	@file		BehaviorTreeLoader.cpp
 *	@brief		BehaviorTreeLoader的具体实现。
 *
 *
 *	Date        Name        Description
 *	01/03/15	MYLS		Creation.
 *	03/03/15	MYLS		Support XML comments now
 *
 *********************************************************************/

#include "NodeFactory.h"
#include "BehaviorTreeLoader.h"


namespace BehaviorTree {

	BehaviorTreeLoader::
	BehaviorTreeLoader(const std::string & filePath) :
		_XMLDoc(filePath),
		_NodeFactory()
	{
		if (!_XMLDoc.LoadFile())
			std::cerr << "Error, Cannot Open File! " << _XMLDoc.ErrorDesc() << std::endl;

		if (_XMLDoc.FirstChildElement() == nullptr)
			std::cerr << "Error, No Root Element!" << std::endl;

		if (strcmp("BehaviorTrees", _XMLDoc.FirstChildElement()->Value()) != 0)
			std::cerr << "Error, Not a BehaviorTree XML file!" << std::endl;
	}

	BehaviorTreeLoader::
	~BehaviorTreeLoader()
	{}

	BehaviorTreeLoader::
	BehaviorTreeLoader(const BehaviorTreeLoader & rhs) :
		_XMLDoc(rhs._XMLDoc),
		_NodeFactory(rhs._NodeFactory)
	{}

	BehaviorTreeLoader & BehaviorTreeLoader::
	operator = (const BehaviorTreeLoader & rhs)
	{
		_XMLDoc = rhs._XMLDoc;
		_NodeFactory = rhs._NodeFactory;
		return *this;
	}


	Node * BehaviorTreeLoader::
	CreateBehaviorTree(const std::string & btName) const
	{
		Node * pBehaviorTreeRoot = nullptr;

		for (auto pIt = _XMLDoc.FirstChildElement()->FirstChildElement(); 
			 pIt != nullptr; 
			 pIt = pIt->NextSiblingElement()) {

			if (strcmp(pIt->Value(), btName.c_str()) == 0) {
				auto pChild = pIt->FirstChildElement();
				if (pChild == nullptr)
					continue;

				std::string name;
				pChild->QueryStringAttribute(DEFAULT_NODE_ATTRIBUTE, &name);
				pBehaviorTreeRoot = _NodeFactory.Create(name);

				if (pChild->NextSibling() != nullptr)
					std::cerr << "Warning, Behavior Tree [" << btName 
					<< "] has more than One Root!" << std::endl;

				CreateBehaviorTreeNode(pChild->FirstChildElement(), pBehaviorTreeRoot, pChild->Value());

				break;
			}
		}

		if (!pBehaviorTreeRoot)
			std::cerr << "BehaviorTreeLoader::Cannot create BehaviorTree, " << btName << "!" << std::endl;

		return pBehaviorTreeRoot;
	}

	void BehaviorTreeLoader::
	Print() const
	{
		TiXmlPrinter printer;
		_XMLDoc.Accept(&printer);
		std::cout << printer.CStr() << std::endl;
	}

	void BehaviorTreeLoader::
	CreateBehaviorTreeNode(const TiXmlElement* pFirstChild, Node * & pNode, const std::string & btName) const
	{
		for (auto pIt = pFirstChild; pIt != nullptr; pIt = pIt->NextSiblingElement()) {
			std::string name;
			pIt->QueryStringAttribute(DEFAULT_NODE_ATTRIBUTE, &name);
			Node * pChildNode = _NodeFactory.Create(name);
			
			if (btName == DEFAULT_NODE_COMPOSITE)
				dynamic_cast<Composite *>(pNode)->AddChildNode(pChildNode);
			else if (btName == DEFAULT_NODE_DECORATOR)
				dynamic_cast<Decorator *>(pNode)->SetChildNode(pChildNode);
			else
				std::cerr << "Error, Unknown BehaviorTree Node Type : " + btName << std::endl;

			CreateBehaviorTreeNode(pIt->FirstChildElement(), pChildNode, pIt->Value());
		}
	}


	char BehaviorTreeLoader::DEFAULT_NODE_ATTRIBUTE[] = "name";
	char BehaviorTreeLoader::DEFAULT_NODE_COMPOSITE[] = "Composite";
	char BehaviorTreeLoader::DEFAULT_NODE_DECORATOR[] = "Decorator";

}
