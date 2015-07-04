#include <time.h>
#include <windows.h>

#include <iostream>
#include <vector>

/////
#include "../BehaviorTree/BehaviorTree.h"
#include "../Common/common.h"
#include "StringParsing.hpp"

#include "DataLayer.h"

// v for debug
#include <typeinfo>

/*
#define DISTANCE 100
std::vector<Enemy> EnemyVector;

void InitObstacles(std::vector<Enemy> &enemyVector, std::vector<Agent> &agentVector)
{
for (int i = 0; i < EnemyVector.size(); i++)
{
for (int k = 0; k < agentVector.size(); k++)
{
if (agentVector[k]._ID == EnemyVector[i]._ID)
continue;
if (EnemyVector[i].position.DistanceTo(EnemyVector[i].position) < DISTANCE)
{
EnemyVector[i]._ID = 0;
break;
}
}
}
for (int i = 0; i < EnemyVector.size(); i++)
{
if (EnemyVector[i]._ID == 0)
continue;
for (int j = 0; j < EnemyVector.size(); j++)
{
if (i == j || EnemyVector[i]._ID == EnemyVector[j]._ID || EnemyVector[j]._ID == 0)
continue;
if (EnemyVector[i].position.DistanceTo(EnemyVector[j].position) < DISTANCE)
{
if (EnemyVector[i].distance > EnemyVector[j].distance)
{
EnemyVector[i]._ID = 0;
}
else EnemyVector[j]._ID = 0;
}
}
}
for (int i = 0; i < EnemyVector.size(); i++)
{
if (EnemyVector[i]._ID == 0)
continue;
enemyVector.push_back(EnemyVector[i]);
}
return;
}

*/
/*
void ShowBehaviorTree(BehaviorTree::Node * ptr, int depth)
{
	for (int i = 0; i < depth; i++)
		printf("    ");

	printf("%s\n", typeid(*ptr).name() + 6 + 14);

	if (dynamic_cast<BehaviorTree::Composite *>(ptr))
		for (auto &it : dynamic_cast<BehaviorTree::Composite *>(ptr)->_ChildNodes)
			ShowBehaviorTree(it, depth + 1);

	if (dynamic_cast<BehaviorTree::Decorator *>(ptr))
		ShowBehaviorTree(dynamic_cast<BehaviorTree::Decorator *>(ptr)->_ChildNode, depth + 1);
}*/
// ^ for debug

void load_info(BehaviorTree::Ball &ball,
	std::vector<BehaviorTree::Agent> &agents,
	std::vector<BehaviorTree::Enemy> &enemies,
	Ball *wzc_trueBall, Agent * wzc_agent,
	Obstacle * wzc_obstacle)
{

	ball._Loacion.SetX(wzc_trueBall->GetX());
	ball._Loacion.SetY(wzc_trueBall->GetY());// 这么纠结= =

	for (int i = 0; i < 10; i++) {
		if ((wzc_obstacle + i)->GetX() == 0 && (wzc_obstacle + i)->GetY() == 0) {
			break;
		}
		BehaviorTree::Enemy temp_Enemy;
		temp_Enemy._Loacion.SetX((wzc_obstacle + i)->GetX());
		temp_Enemy._Loacion.SetY((wzc_obstacle + i)->GetY());
		temp_Enemy._Radius = (wzc_obstacle + i)->GetSize();
		enemies.push_back(temp_Enemy);
	}
	bool tempSign[6] = { false };
	for (int i = 1; i < 6; i++) {
		if ((wzc_agent + i)->IsAgOnline()
			&& (wzc_agent + i)->GetStatus() != ROBST_ERR/*待机状态*/) {
			tempSign[i] = true;
		}
	}
	for (int i = 1; i < agents.size(); i++) {
		int tempID = agents[i]._ID;
		if (tempSign[tempID] == false) {
			agents.erase(agents.begin() + i);
			i -= 1;
		} else {
			agents[i]._Angle = wzc_agent[tempID].GetAngle();
			agents[i]._Loacion.SetX(wzc_agent[tempID].GetX());
			agents[i]._Loacion.SetY(wzc_agent[tempID].GetY());
			//TODO: agents[i]._Speed 具体情况不确定 
			tempSign[tempID] = false;
		}
	}
	for (int i = 1; i < 6; i++) {
		if (tempSign[i] == true) {
			BehaviorTree::Agent tempAgent;
			tempAgent._ID = i;
			tempAgent._Angle = wzc_agent[i].GetAngle();
			tempAgent._Loacion.SetX(wzc_agent[i].GetX());
			tempAgent._Loacion.SetY(wzc_agent[i].GetY());
			//tempAgent_Speed 具体情况不确定
			tempSign[i] = false;
			agents.push_back(tempAgent);
		}
	}
	return;
}

int main(void)
{
	//! [1] test for TheLeafData (xxx.ini)
	{
		std::cout << "0." << std::endl;
		Vec2D<float> V2D;
		TheLeafData::Instance()->GetValue<Vec2D<float>>("Settings", "test2D", V2D);
		std::cout << "V2D.x = " << V2D.GetX() << std::endl;
		std::cout << "V2D.y = " << V2D.GetY() << std::endl;

		std::cout << "1." << std::endl;
		std::vector<double> testA;
		TheLeafData::Instance()->GetValue<double>("Settings", "A", testA);
		for (auto &iter : testA) {
			std::cout << "A: " << iter << std::endl;
		}

		std::cout << "2." << std::endl;
		std::vector<Vec2D<float>> testV2D;
		TheLeafData::Instance()->GetValue<Vec2D<float>>("Settings", "test2D", testV2D);
		for (auto &iter : testV2D) {
			std::cout << "X: " << iter.GetX() << std::endl;
			std::cout << "Y: " << iter.GetY() << std::endl;
		}
	}
	system("pause");
	//! [1] end test


	//! [2] 从XML文件导入行为树
	BehaviorTree::Node * root = nullptr;
	try {
		std::string filePath = TheLeafData::Instance()->GetString("Settings", "BehaviorTreeXML");
		BehaviorTree::BehaviorTreeLoader btLoader(filePath);

		std::string name = TheLeafData::Instance()->GetString("Settings", "BehaviorTreeName");
		root = btLoader.CreateBehaviorTree(name);
	} catch (std::string & error) {
		std::cerr << error << std::endl;
		return 1;
	}
	//! [2] end

	//! [3] 创建需要的数据的类型
	BehaviorTree::GameStatus gameStatus = BehaviorTree::GAME_STOP;
	BehaviorTree::Ball ball;
	std::vector<BehaviorTree::Agent> agents;
	std::vector<BehaviorTree::Enemy> enemies;
	std::string cmd;

	BehaviorTree::InputData input(gameStatus, ball, agents, enemies);
	BehaviorTree::OutputData output(gameStatus, agents, cmd);
	StringParsing stringparser;

	Sleep(1000);

	//! [3]

	//! [4] 主循环
	while (1) {

		// TODO: load info(gameStatus, ball, agents, enemies)
		// for(1:ag_num)
		//	add or updata
		// size > ag_num ? search(1:size) & delete

		root->Process(AnyDataRef<BehaviorTree::InputData>(input), AnyDataRef<BehaviorTree::OutputData>(output));
		stringparser.GetString(output.GetCMD());

		std::cout << "testing..." << std::endl;

		// ShowBehaviorTree(root, 0);

		Sleep(333);
		system("cls");
	}
	//! [4]

	return 0;
}

