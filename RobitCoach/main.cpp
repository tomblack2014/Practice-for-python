#include "MainWindow.h"
#include <QApplication>

#include <time.h>
#include <windows.h>

#include <iostream>
#include <vector>

/////
#include "Stra/BehaviorTree/BehaviorTree.h"
#include "Stra/Common/Common.h"
#include "Stra/test/StringParsing.hpp"


// v for debug
#include <typeinfo>

//! [3] 创建需要的数据的类型
BehaviorTree::GameStatus gameStatus = BehaviorTree::GAME_STOP;

BehaviorTree::Ball ball;
std::vector<BehaviorTree::Agent> agents;
std::vector<BehaviorTree::Enemy> enemies;
std::string cmd;

Agent *AgentInfo;
Ball *BallInfo;
Obstacle *ObstInfo;
CUDPDataHandling *extSender;
TCPRefClient  *extRef;

char memStatus = 'S';
bool firstRun = true;

void checkGameStatus()
{

    bool isCyan = extRef->isSideCyan();
    char status = extRef->GetGameStatus();
    if (!firstRun)
    {
        if (memStatus == status)
        {
            return;
        }
        else
        {
            memStatus = status;
        }
    }
    firstRun = false;
    switch (status) {
    case MSLS_Stop:
        gameStatus = BehaviorTree::GAME_STOP;
        //status = extRef->GetGameStatus();
        //extRef->SetGameStatus("STOP");
        break;
    case MSLS_Start:
        gameStatus = BehaviorTree::GAME_START;
        //extRef->SetGameStatus("START");
        break;
    case MSLS_Cancle:
        gameStatus = BehaviorTree::GAME_STOP;
        //extRef->SetGameStatus("STOP");
        break;
    case MSLS_DroppedBall:
        gameStatus = BehaviorTree::GAME_DROP_BALL;
        //extRef->SetGameStatus("DROP BALL");
        break;
    case MSLS_EndHalf:
        gameStatus = BehaviorTree::GAME_STOP;
        //extRef->SetGameStatus("STOP");
        break;
    case MSLS_Parking:
        gameStatus = BehaviorTree::GAME_STOP;
        //extRef->SetGameStatus("STOP");
        break;

    //---------------------------------------------------------------------
    //*****************command toward CYAN below***************************
    //---------------------------------------------------------------------
    case MSLS_Kick_off_Cyan:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_KICK_OFF;
            //extRef->SetGameStatus("Kick Off");

        }
        else
        {
            gameStatus = BehaviorTree::GAME_ANTI_KICK_OFF;
            //extRef->SetGameStatus("Anti Kick Off");
        }
        break;
    case MSLS_Freekick_Cyan:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_FREE_KICK;
            //extRef->SetGameStatus("Free Kick");
        }
        else
        {
            gameStatus = BehaviorTree::GAME_ANTI_FREE_KICK;
            //extRef->SetGameStatus("Anti Free Kick");
        }
        break;
    case MSLS_Goalkick_Cyan:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_GOAL_KICK;
            //extRef->SetGameStatus("Goal Kick");
        }
        else
        {
            gameStatus = BehaviorTree::GAME_ANTI_GOAL_KICK;
            //extRef->SetGameStatus("Anti Goal Kick");
        }
        break;
    case MSLS_Throwin_Cyan:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_THROW_IN;
            //extRef->SetGameStatus("Throw In");
        }
        else
        {
            gameStatus = BehaviorTree::GAME_ANTI_THROW_IN;
            //extRef->SetGameStatus("Anti Throw In");
        }
        break;
    case MSLS_Pentalty_Cyan:
        //TODO::真正的罚球
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_STOP;
            //extRef->SetGameStatus("STOP");
        }
        else
        {
            gameStatus = BehaviorTree::GAME_STOP;
            //extRef->SetGameStatus("STOP");
        }
        break;
    case MSLS_Goal_Cyan:
        //TODO::不知道干嘛
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_STOP;
            //extRef->SetGameStatus("STOP");
        }
        else
        {
            gameStatus = BehaviorTree::GAME_STOP;
            //extRef->SetGameStatus("STOP");
        }
        break;
    case MSLS_Subgoal_Cyan:
        //TODO::不知道干嘛
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_STOP;
            //extRef->SetGameStatus("STOP");
        }
        else
        {
            gameStatus = BehaviorTree::GAME_STOP;
            //extRef->SetGameStatus("STOP");
        }
        break;
    case MSLS_Corner_Cyan:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_CORNER_KICK;
            //extRef->SetGameStatus("Corner Kick");
        }
        else
        {
            gameStatus = BehaviorTree::GAME_ANTI_CORNER_KICK;
            //extRef->SetGameStatus("Anti Corner Kick");
        }
        break;



    //---------------------------------------------------------------------
    //*****************command toward MAGENTA below***************************
    //---------------------------------------------------------------------
    case MSLS_Kick_off_Magenta:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_ANTI_KICK_OFF;
        }
        else
        {
            gameStatus = BehaviorTree::GAME_KICK_OFF;
        }
        break;
    case MSLS_Freekick_Magenta:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_ANTI_FREE_KICK;
        }
        else
        {
            gameStatus = BehaviorTree::GAME_FREE_KICK;
        }
        break;
    case MSLS_Goalkick_Magenta:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_ANTI_GOAL_KICK;
        }
        else
        {
            gameStatus = BehaviorTree::GAME_GOAL_KICK;
        }
        break;
    case MSLS_Throwin_Magenta:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_ANTI_THROW_IN;
        }
        else
        {
            gameStatus = BehaviorTree::GAME_THROW_IN;
        }
        break;
    case MSLS_Pentalty_Magenta:
        //TODO::真正的罚球
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_STOP;
        }
        else
        {
            gameStatus = BehaviorTree::GAME_STOP;
        }
        break;
     case MSLS_Goal_Magenta:
        //TODO::不知道干嘛
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_STOP;
        }
        else
        {
            gameStatus = BehaviorTree::GAME_STOP;
        }
        break;
    case MSLS_Subgoal_Magenta:
        //TODO::不知道干嘛
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_STOP;
        }
        else
        {
            gameStatus = BehaviorTree::GAME_STOP;
        }
        break;
    case MSLS_Corner_Magenta:
        if (isCyan)
        {
            gameStatus = BehaviorTree::GAME_ANTI_CORNER_KICK;
        }
        else
        {
            gameStatus = BehaviorTree::GAME_CORNER_KICK;
        }
        break;
    case MSLS_Restart:
        //...
        break;
    case MSLS_Dummy:
        //,..
        break;
    case MSLS_Ready:
        //,..i
        break;
    case MSLS_EndGame:
        gameStatus = BehaviorTree::GAME_STOP;
        break;
    default:
        gameStatus = BehaviorTree::GAME_STOP;
        break;
    }
}

void load_info(BehaviorTree::Ball &ball,
    std::vector<BehaviorTree::Agent> &agents,
    std::vector<BehaviorTree::Enemy> &enemies,
    Ball *wzc_trueBall, Agent * wzc_agent,
    Obstacle * wzc_obstacle)
{

    bool flag = false;
    ball._Loacion.SetX(wzc_trueBall->GetX()-900);
    ball._Loacion.SetY(wzc_trueBall->GetY()-600);// 这么纠结= =
    ball._Owner = wzc_trueBall->GetOwner();
    //ball._Owner = -1;

    for (int i = 0; i < 10; i++)
    {
        if (wzc_obstacle[i].GetX() == 0 && wzc_obstacle[i].GetY() == 0)
        {
            break;
        }
        BehaviorTree::Enemy temp_Enemy;
        temp_Enemy._Loacion.SetX(wzc_obstacle[i].GetX()-900);
        temp_Enemy._Loacion.SetY(wzc_obstacle[i].GetY()-600);
        temp_Enemy._Radius = wzc_obstacle[i].GetSize();
        enemies.push_back(temp_Enemy);
    }

    agents.clear();
    for (int i = 1; i <= AG_NUM; i++)
    {
        if (wzc_agent[i].IsAgOnline())
        {
            flag = true;
            if (wzc_agent[i].GetStatus() == ROBST_ERR)
            {
                continue;
            }
            BehaviorTree::Agent tempAgent;
            tempAgent._ID = i;
            tempAgent._Angle = wzc_agent[i].GetAngle();
            tempAgent._Loacion.SetX(wzc_agent[i].GetX()-900);
            tempAgent._Loacion.SetY(wzc_agent[i].GetY()-600);
            agents.push_back(tempAgent);
        }
    }
    if (flag == false)
    {
        ball._Owner = -1;
    }
    return;
}

DWORD WINAPI Tree(LPVOID pParam)
{
    //int cnt = 0;
    //! [2] 从XML文件导入行为树
    BehaviorTree::Node * root = nullptr;
    try
    {
        std::string filePath = TheLeafData::Instance()->getString("Settings", "BehaviorTreeXML");
        BehaviorTree::BehaviorTreeLoader btLoader(filePath);
        std::string name = TheLeafData::Instance()->getString("Settings", "BehaviorTreeName");
        root = btLoader.CreateBehaviorTree(name);
    }
    catch (std::string & error)
    {
        std::cerr << error << std::endl;
        return 1;
    }
    //! [2] end
    BehaviorTree::InputData input(gameStatus, ball, agents, enemies);
    BehaviorTree::OutputData output(gameStatus, agents, cmd);
    //StringParsing stringparser;
   // ! [4] 主循环
    int iii = 0;
    while (iii<1) {
        iii++;
        //load info(gameStatus, ball, agents, enemies)
        // for(1:ag_num)
        //	add or updata
        // size > ag_num ? search(1:size) & delete
        checkGameStatus();
        //gameStatus = BehaviorTree::GAME_AUTO;
        load_info(ball,agents,enemies,BallInfo,AgentInfo,ObstInfo);
        root->Process(AnyDataRef<BehaviorTree::InputData>(input), AnyDataRef<BehaviorTree::OutputData>(output));
        //stringparser.GetString(output.GetCMD());
        std::string m_String = output.GetCMD();

        std::string str = "";

        std::istringstream itemp(m_String);

        int ID = 0, x = 0, y = 0;
        double angle = 0;

        while (itemp >> str){

            if (str == "ATTACK") {
                itemp >> ID;
                //TODO:给ID发送ATTACK
                extSender[ID].CtrlCmd(CTRL_ATTACK,BallInfo->GetX(),BallInfo->GetY(),0,0);
                //std::cout << "ATTACK" << ' ' << ID << std::endl;
            }
            else if (str == "STOP"){
                itemp >> ID;
                //TODO:给ID发送STOP
                extSender[ID].CtrlCmd(CTRL_STOP,0,0,0,0);
                //printf("No.%d  command:STOP\n");
                //std::cout << "STOP" << ' ' << ID << std::endl;
            }
                    else if (str == "MOVETO"){
                        itemp >> ID >> x >> y;
                        //TODO:给ID发送MOVETO(x,y)
                        extSender[ID].MoveCmd(x,y,0,0);
                        //std::cout << "MOVETO" << ' ' << ID << ' ' << x << ' ' << y << std::endl;
                    }
                    else if (str == "PASSMOVE"){
                        itemp >> ID >> x >> y >> angle;
                        //TODO:给ID发送PASSMOVE(x,y,angle)
                        //extSender[ID].SetTarget("127.0.0.1",20091);
                        extSender[ID].MoveCmd(x,y,angle,0);
                        //printf("dfsdfsdfsdfsd\n");
                        //std::cout << "PASSMOVE" << ' ' << ID << ' ' << x << ' ' << y << ' ' << angle << std::endl;
                    }
                    else if (str == "3M_PASS"){
                        itemp >> ID >> x >> y;
                        //TODO:给ID发送PASS(x,y)
                        extSender[ID].PassCmd_Normal(x,y);
                        //std::cout << "3M_PASS" << ' ' << ID << ' ' << x << ' ' << y << std::endl;
                    }
                    else if (str == "3M_CATCH"){
                        itemp >> ID >> x >> y;
                        //TODO:给ID发送CATCH(x,y)
                        extSender[ID].CatchCmd_Normal(x,y);
                        //std::cout << "3M_CATCH" << ' ' << ID << ' ' << x << ' ' << y << std::endl;
                    }
            else if (str == "PASS"){
                itemp >> ID >> x >> y;
                extSender[ID].PassCmd(x,y);
            }
            else if (str == "CATCH"){
                itemp >> ID >> x >> y;
                extSender[ID].CatchCmd(x,y);
            }
                    else if (str == "*")
                        continue;
                }

        /*std::cout << "testing..." << std::endl;
        // ShowBehaviorTree(root, 0);
        Sleep(333);
        system("cls");*/
   }

    return 1;
}

void RobitCoachInitialize(Agent *iAgentInfo, Ball *iBallInfo,
                          Obstacle *iObstInfo,CUDPDataHandling *inSender,
                          TCPRefClient *ref)
{
    AgentInfo = iAgentInfo;
    BallInfo  = iBallInfo;
    ObstInfo  = iObstInfo;
    extSender = inSender;
    extRef    = ref;
    memStatus = 'S';
    firstRun = true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //int status;
    // Define Agent
    Agent    *ExtAgent;
    ExtAgent   = new Agent[AG_NUM+1];
    Ball     *ExtBall;
    ExtBall    = new Ball;
    Obstacle *ExtObst;
    ExtObst    = new Obstacle[MAX_OBST_NUM_INFIELD];

    // Define Coach's Listening thread
    CUDPDataHandling Reciever(ExtAgent);

    // Define Coach's Sending object
    CUDPDataHandling *Sender;
    Sender = new CUDPDataHandling[AG_NUM+1];

    TCPRefClient *Referee;
    Referee = new TCPRefClient;

    // Define IP management
    ipCtrl *ExtIpCtrl;
    ExtIpCtrl = new ipCtrl[AG_NUM+1];
    Reciever.SetIpCtrl(ExtIpCtrl);
    // Coach ready to listen at port 20090 with UDP
    Reciever.Listen(20090);


    // send array to class "MainWindow"
    w.buildConnection(ExtAgent,Sender,ExtIpCtrl,Referee);
    w.initializeInfoElimination(ExtBall,ExtObst);
    w.show();

    RobitCoachInitialize(ExtAgent,ExtBall,ExtObst,Sender,Referee);
    CreateThread(NULL, 0, Tree, NULL, 0, NULL);
    //QObject::connect(&w,&MainWindow::setRefPara,&w,&MainWindow::refreshGUI);

    return a.exec();
}
