#ifndef DATALAYER_H
#define DATALAYER_H
#include <string>
/**********************************************************************************************************
//---------------------------------------------------------------------------------------------------------
//Author       ：Wang ZiCheng @ Robit @ BeiJing Institute Of Technology     wzcizyq@hotmail.com          *|
//               ->[wzc] for short will be used in this project                                          *|
//Time         ：2014-10-26                                                                              *|
//Header File  ：DataLayer.h                                                                                *|
//Declaration  ：                                                                                        *|
//               1.Declaration of the agent class                                                        *|
//               2.Declaration of the tactical point class                                               *|
//               3.Declaration of the obstacle class                                                     *|
//               4.Declaration of the ball class                                                         *|
//               5.Declaration of the tactical role-controling class                                     *|
//               6.Necessary Macro Defination                                                            *|
//Source File  ：DataLayer.cpp                                                                              *|
//---------------------------------------------------------------------------------------------------------
//********************************************************************************************************/
using namespace std;



/*********************************** Const Defination Below **************************************************
//-------------------------------------- Starts Here -------------------------------------------------------*/
//                                                                                                          */
//basic                                                                                                     */
const int AG_NUM = 6;                   /*                                                                  */
const int EACH_AG_OBST_NUM = 10;        //Number Of Obstacles that one single agent can observe             */
const int AG_PRIORITY_HIGH = 300;       /*High Priority , add to basic score when select best attacker      */
const int AG_PRIORITY_MID  = 500;       /*Middle Proority                                                   */
const int AG_PRIORITY_LOW  = 700;       /*Low Priority                                                      */
const int MAX_OBST_NUM_INFIELD = 10;    /*                                                                  */
/*                                                                                                          */
/*Message Type                                                                                              */
const int MSL_INFO	    = 1;            /*Agent information                                                 */
const int MSL_CMD		= 2;            /*Command                                                           */
const int MSL_OBST		= 3;            /*Obstacle infomation                                               */
const int MSL_TEAMMATE  = 4;            /*Teammate information (remain to be developed)                     */
const int MSL_KICK		= 5;            /*Some One Kicked Ball Message                                      */
const int MSL_INITPOS	= 6;            /*Initialize Position                                               */
const int MSL_HB_INFO   = 99;           /*                                                                  */
                                        /*                                                                  */
const int MSL_DEBUG		  = 7;          /*                                                                  */
const int MSL_PREDICTBALL = 8;          /*                                                                  */
/*                                      /*                                                                  */
/*Agent Role Control                    /*                                                                  */
const int CTRL_STOP		   = 0;         /*                                                                  */
const int CTRL_ATTACK	   = 1;         /*                                                                  */
const int CTRL_GOALKEEP	   = 2;         /*                                                                  */
const int CTRL_DEFENCE	   = 3;         /*                                                                  */
const int CTRL_PASS		   = 4;         /*                                                                  */
const int CTRL_CATCH	   = 5;         /*                                                                  */
const int CTRL_MID_PASS	   = 6;         /*                                                                  */
const int CTRL_MID_CATCH   = 7;         /*                                                                  */
const int CTRL_3M_PASS     = 8;         /*                                                                  */
const int CTRL_3M_CATCH    = 9;         /*                                                                  */
const int CTRL_MOVETO			= 11;   /*                                                                  */
const int CTRL_BLOCK			= 12;   /*                                                                  */
const int CTRL_ATTENTIONBALL	= 13;   /*                                                                  */
const int CTRL_PRODEF			= 14;   /*                                                                  */
const int CTRL_SEARCHBALL		= 15;   /*                                                                  */
const int CTRL_SHIFTATK		    = 16;   /*                                                                  */
const int CTRL_REMOTECTRL		= 17;   /*                                                                  */
const int CTRL_AROUNDBALL		= 18;   /*                                                                  */
const int CTRL_ATKCOVER		    = 19;   /*                                                                  */
const int CTRL_ATK_CAT_CONVERT  = 103;  /*For pass ball action [wzc]                                        */
const int CTRL_PASS_MOVE        = 133;  /*For pass ball action [wzc]                                        */
const int CTRL_TAC_WAIT         = 333;  /*For pass ball action [wzc]                                        */
/*                                                                                                          */
/*dig in                                                                                                    */
const int CTRL_FOLLOWPOSITION   = 20;   /*                                                                  */
/*                                                                                                          */
/*pre ball                              /*                                                                  */
const int CTRL_PREDICTBALL      = 21;   /*                                                                  */
const int CTRL_TEST		        = 40;   /*                                                                  */
const int CTRL_IDLE		        = 41;   /*                                                                  */
/*                                      /*                                                                  */
/*KickOff                               /*                                                                  */
const int CTRL_KICKOFF_PRIM_READY  = 50;           /*                                                       */
const int CTRL_KICKOFF_SLAVE_READY = 51;           /*                                                       */
const int CTRL_KICKOFF_PRIM		   = 52;           /*                                                       */
const int CTRL_KICKOFF_SLAVE	   = 53;           /*                                                       */
/*                                                                                                          */
/*FreeKick                                         /*                                                       */
const int CTRL_FREEKICK_PRIM_READY  = 60;          /*                                                       */
const int CTRL_FREEKICK_SLAVE_READY = 61;          /*                                                       */
const int CTRL_FREEKICK_PRIM		= 62;          /*                                                       */
const int CTRL_FREEKICK_SLAVE		= 63;          /*                                                       */
/*                                                                                                          */
/*Goalkick                                         /*                                                       */
const int CTRL_GOALKICK_PRIM_READY	= 70;          /*                                                       */
const int CTRL_GOALKICK_SLAVE_READY	= 71;          /*                                                       */
const int CTRL_GOALKICK_PRIM		= 72;          /*                                                       */
const int CTRL_GOALKICK_SLAVE		= 73;          /*                                                       */
/*                                                                                                          */
/*Throw in                                         /*                                                       */
const int CTRL_THROWIN_PRIM_READY	= 80;          /*                                                       */
const int CTRL_THROWIN_SLAVE_READY	= 81;          /*                                                       */
const int CTRL_THROWIN_PRIM			= 82;          /*                                                       */
const int CTRL_THROWIN_SLAVE		= 83;          /*                                                       */
/*                                                                                                          */
/*Corner Kick                                      /*                                                       */
const int CTRL_CORNERKICK_PRIM_READY	= 90;      /*                                                       */
const int CTRL_CORNERKICK_SLAVE_READY	= 91;      /*                                                       */
const int CTRL_CORNERKICK_PRIM		    = 92;      /*                                                       */
const int CTRL_CORNERKICK_SLAVE		    = 93;      /*                                                       */
/*                                                                                                          */
/*Anti_KickOff                                     /*                                                       */
const int CTRL_PENALTY_READY = 100;                /*                                                       */
const int CTRL_PENALTY		 = 101;                /*                                                       */
/*                                                                                                          */
/*status                                           /*                                                       */
const int ROBST_NEW			 = 110;                /*                                                       */
const int ROBST_ERR			 = 111;                /*                                                       */
const int ROBST_PROBE		 = 112;                /*                                                       */
/*                                                                                                          */
/*Tech Challenge                                   /*                                                       */
const int TC_FINDBALL	     = 200;                /*                                                       */
/*                                                 /*                                                       */
/*----------------------------------------- Ends Here --------------------------------------------------------
/************************************* Const Definition Above************************************************/








/**********************************************************************************************************
//-------------------------------------------------------------------------------------------------------*/
//Agent Role Control
typedef unsigned int AgentControl;
//Agent Priority
typedef unsigned int AgentPriority;
//Agent Status
typedef unsigned int AgentStatus;
/*---------------------------------------------------------------------------------------------------------
//********************************************************************************************************/



class ipCtrl
{
public:
    ipCtrl();
    bool hasBeenSet;
    string ip;
    bool isOnline;
};



/******************************* Point Class Defination Below *********************************************
/*-------------------------------------- Starts Here ----------------------------------------------------*/

//Tactical Point
class Point
{
public:
    Point();                   //Constructor
    ~Point();                  //Destructor
    int GetX();                //Get X coordinate
    int GetY();                //Get Y coordinate
    void SetX(int inX);        //Set X coordinate , Parameter inX represents X coordiante
    void SetY(int inY);        //Set Y coordinate , Parameter inY represents Y coordiante
protected:
    ;
private:
    int x;                     //X coordinate
    int y;                     //Y coordinate
};
/*----------------------------------------- Ends Here -----------------------------------------------------
//****************************** Point Class Defination Above ********************************************/









/******************************* Obstacle Class Defination Below ******************************************
//-------------------------------------- Starts Here ----------------------------------------------------*/

//Obstacle
class Obstacle
{
public:
    Obstacle();                    //constructor
    ~Obstacle();                   //destructor
    Point GetPositon();            // Get Obstacle Position , return a point
    int   GetX();                  // return coordinate x;
    int   GetY();                  // return coordinate y;
    int   GetOwner();              // return its owner
    int   GetSize();               // return its size
    bool  CheckIsValid();          // if info is valid , return true , else return false

    void SetPosition(int inX, int inY);
    bool SetOwner(int inID);       // parameter for agent ID , if inID is within correct range , return true
    void SetSize(int inSize);      // parameter for obstacle size
    void SetIsValid(bool inIsValid);//

protected:

private:
    Point m_Position;              //Positon
    int   m_Owner;                 //Observer ID
    int   m_Size;                  //Obstacle Size
    bool  m_isValid;               //To see if this obstacle information is avilible
};
/*----------------------------------------- Ends Here -----------------------------------------------------
//****************************** Obstacle Class Defination Above ********************************************/








/******************************* Ball Class Defination Below **********************************************
//-------------------------------------- Starts Here ----------------------------------------------------*/

//Ball Class
class Ball
{
public:
    Ball();
    ~Ball();
    Point GetPosition();                // Get ball position , return a point
    int   GetX();                       // return x coordinate
    int   GetY();                       // return y coordinate
    bool  CheckIsUpdated();             // check whether if the ball info is updated
    int   GetOwner();                   // return its observer

    void SetPosition(int inX, int inY); // parameter stands for x coordinate and y coordinate
    void SetIsUpdated(bool inIs);       // parameter stands for whether ball info is updated
    bool SetOwner(int inID);            // parameter stands for agent id , if it is within correct range ,return true
protected:
    ;
private:
    Point m_Position;                   // position
    bool m_IsUpdated;                   // whether if the ball infomation is updated and avilible
    int m_Owner;                        // observer ID
};
/*----------------------------------------- Ends Here -----------------------------------------------------
//****************************** Ball Class Defination Above *********************************************/










/****************************** Role Control Class Defination Below *****************************************
//-------------------------------------- Starts Here ------------------------------------------------------*/

//Control Class
class RoleControl
{
public:
    RoleControl();
    ~RoleControl();
    AgentControl GetCtrl();                     // return current status
    Point        GetTargetCoor();               // Get target position , return a point
    int          GetTargetX();                  // Get x
    int          GetTargetY();                  // Get y
    int          GetDefDist();                  // Get defence distance
    int          GetDefAngle();                 // Get defence angle

    void SetCtrl(AgentControl inCtrl);          // Set contorl priority's role
    void SetTargetCoor(Point inCoordinate);     // when role is MOVE_TO , Set
    void SetTargetX(int inX);
    void SetTargetY(int inY);
    void SetDefDist(int inDist);
    void SetDefAngle(int inAngle);
protected:
    ;
private:
    AgentControl m_Ctrl;          //Role
    Point m_TargetCoordinate;     //when the role is MOVE_TO , this coordinate stands for the destination
    Point m_SourceCoordinate;     // **** remain to be finished ****[wzc]
    int  m_TargetAngle;           // when the role is MOVE_TO, this angle stands for the direction that agent face

    int  m_DefenceDistance;       // when the role is DEFENCE , this distance stands for the range between agent and the target object
    int  m_DefenceAngle;          // when the role is DEFENCE , this angle stands for the direction that agent face

    int  m_re_ballx;              // this still remain UNKONWN [wzc]
    int  m_re_bally;              // this still remain UNKONWN [wzc]
    bool m_TargetGoal;            // this still remain UNKONWN [wzc]
};
/*----------------------------------------- Ends Here --------------------------------------------------------
//************************** Role Control Class Defination Above ********************************************/









/******************************** Agent Class Defination Below ********************************************
//-------------------------------------- Starts Here ----------------------------------------------------*/

//Agent Class
class Agent
{
public:
    Agent();                         //constructor
    ~Agent();                        //destructor

    int   GetID();                   //Get ID
    bool  SetID(int inID);           //Set ID

    void   SetIP(string inIP);
    string GetIP();

    int   GetX();                    //
    int   GetY();                    //
    bool SetPosition(int inX, int inY);

    double GetSpeed();               //
    void   SetSpeed(double v);       //

    bool  IsAgHoldBall();            //whether the agent is holding the ball or not
    bool  SetIsHoldBall(bool Key);   //to set whether the agent is holding the ball or not

    bool  IsAgFoundBall();           //whether the agent can see ball
    bool  SetIsFoundBall(bool Key);  //to set whether the agent can see ball

    bool  IsAgOnline();              //whether the agent is online
    void  SetIsOnline(bool Key);     //to set whether the agent is online

    bool  IsAgMemOn();
    void  SetIsAgMemOn(bool key);

    bool  IsAllocated();             //whether this agent has been allocated a role
    bool  SetIsAllocated(bool Key);  //to set whether this agent has been allocated a role

    double GetAngle();               //get the direction that agent face
    bool   SetAngle(double inAng);   //set the direction that agent face

    AgentStatus GetStatus();         //get agent status
    bool SetStatus(AgentStatus Ctrl);//set agent status

    AgentStatus GetPreStatus();             //get agent status in last frame
    bool SetPreStatus(AgentStatus Ctrl);    //set agent status in last frame

    AgentPriority GetPrio();                //get agent priority
    bool SavePrio(AgentPriority Seq);       //set agent priority

    Point GetPosition();                    //get agent position  , return a point

    Obstacle GetObstacleInfo(int Obst_ID);  //get obstacle information , parameter stands for the obst ID
    //add an obstacle, parameter x, y stand for its position, parameter size stand for size
    //owner means observer, IsValid means whether if this obst information is avilible
    //!!!!!!!ATTENTION!!!!!  When Trying to get all the obstacle info of one agent, condition:" i <= m_Agent[x].GetObstacleCnt()" MUST BE USED！！！！
    bool     AddObstacle(int x, int y, int size, int owner, bool IsValid);
    bool     ClearObstacle();              //clear Agent_ID's all obst
    int      GetObstacleCnt();             //to get how many obstacles are there in this agent's view
    void SetIsObstacleValid(int id,bool flag);//to set whether the info is valid or not , when one agent's obstacle info is being updated, this parameter will be saved as TRUE automatically
    bool     CheckIsObstValid(int id);           // to check whether the obst info is valid
    Ball  GetBallInfo();                   //Get ball's info of its own
    bool  SetBallInfo(int x, int y);       //Update ball info

    double GetLinearSpeedAngle();          //
    void   SetLinearSpeedAngle(double ang);//

    int   GetRobotVoltage();               //
    void  SetRobotVlotage(int in);               //

    int   GetLaptopBattery();              //
    void  SetLaptopBattery(int in);              //


private:
    Point   m_Position;           // Agent Position in Field
    int     m_ID;                 //ID
    string  m_IP;

    bool    m_IsAgFoundBall;      //
    bool    m_IsAgHoldBall;       //
    bool    m_IsAgOnline;         //
    bool    m_IsAgMemOn;
    bool    m_IsAgAllocated;      //

    double  m_Angle;              //in what direction that this agent face
    double  m_LinearSpeedAngle;   //
    double  m_Speed;

    AgentStatus   m_Status;        //
    AgentStatus   m_PreStatus;     //status in last frame

    AgentPriority m_AgentPriority; //Agent mood priortity - agent that in a better mood will be firstly assigned a role of ATTACK

    Obstacle   m_Obstacle[EACH_AG_OBST_NUM+1];      //all obst that this agent can see, count from [1]
    int        m_ObstacleCounter;                   //numer of obst that this agent can see currently

    Ball       m_Ball;                              //ball information

    int m_RobotVoltage;                             //Robot Voltage
    int m_LaptopBattery;	                        //percentage of the agent's computer
};
/*----------------------------------------- Ends Here -----------------------------------------------------
//****************************** Agent Class Defination Above ********************************************/

#endif // DATALAYER_H
