
//**********************************************************************************************************
//---------------------------------------------------------------------------------------------------------
//Author       ：Wang ZiCheng @ Robit @ BeiJing Institute Of Technology     wzcizyq@hotmail.com          *|
//               ->[wzc] for short will be used in this project                                          *|
//Time         ：2014-10-26                                                                              *|
//Header File  ：QAgent.h                                                                                *|
//Declaration  ：                                                                                        *|
//               1.Defination of the agent class                                                         *|
//               2.Defination of the tactical point class                                                *|
//               3.Defination of the obstacle class                                                      *|
//               4.Defination of the ball class                                                          *|
//               5.Defination of the tactical role-controling class                                      *|
//                                                                                                       *|
//Header File  ：DataLayer.h                                                                             *|
//---------------------------------------------------------------------------------------------------------
//*********************************************************************************************************

#include "DataLayer.h"


//****************************** Point Class Defination Below *********************************************
//-------------------------------------- Starts Here ------------------------------------------------------
//Tactical Point
Point::Point()
{
    x = 0 ;
    y = 0 ;
}

Point::~Point()
{
}

int Point::GetX()
{
    return x;
}
int Point::GetY()
{
    return y;
}
void Point::SetX(int inX)
{
    x = inX;
}
void Point::SetY(int inY)
{
    y = inY;
}
//----------------------------------------- Ends Here -----------------------------------------------------
//****************************** Point Class Defination Above *********************************************




//****************************** Obstacle Class Defination Below ******************************************
//-------------------------------------- Starts Here ------------------------------------------------------
//Obstacle


Obstacle:: Obstacle()
{
    m_Position.SetX(0);
    m_Position.SetY(0);
    m_Owner = 0;
    m_Size = 0;
    m_isValid = false;
}
Obstacle::~Obstacle()
{
}
Point Obstacle:: GetPositon()           // Get Obstacle Position , return a point
{
    return m_Position;
}
int Obstacle::  GetX()                  // return coordinate x;
{
    return m_Position.GetX();
}
int Obstacle::  GetY()                  // return coordinate y;
{
    return m_Position.GetY();
}
int Obstacle::  GetOwner()              // return its owner
{
    return m_Owner;
}
int Obstacle::  GetSize()               // return its size
{
    return m_Size;
}
bool Obstacle:: CheckIsValid()          // if info is valid , return true , else return false
{
    return m_isValid;
}
void Obstacle:: SetPosition(int inX, int inY)
{
    m_Position.SetX(inX);
    m_Position.SetY(inY);
}
bool Obstacle:: SetOwner(int inID)       // parameter for agent ID , if inID is within correct range , return true
{
    if (inID >= 1 && inID <= AG_NUM)
    {
        m_Owner = inID;
        return true;
    }
    else
    {
        m_isValid = false;
        return false;
    }
}
void Obstacle:: SetSize(int inSize)      // parameter for obstacle size
{
    m_Size = inSize;
}
void Obstacle::SetIsValid(bool inIsValid)//
{
    m_isValid = inIsValid;
}
//----------------------------------------- Ends Here -----------------------------------------------------
//****************************** Point Class Defination Above *********************************************





//******************************* Ball Class Defination Below ******************************************
//-------------------------------------- Starts Here ------------------------------------------------------
//Ball Class
Ball::Ball()
{
    m_Position.SetX(0);
    m_Position.SetY(0);
    m_IsUpdated = false;
    m_Owner = 0;
}
Ball::~Ball()
{
}
Point Ball::GetPosition()                // Get ball position , return a point
{
    return m_Position;
}
// return x coordinate
int  Ball:: GetX()                       // return x coordinate
{
    return m_Position.GetX();
}
int  Ball:: GetY()                       // return y coordinate
{
    return m_Position.GetY();
}
bool Ball:: CheckIsUpdated()             // check whether if the ball info is updated
{
    return m_IsUpdated;
}
int  Ball:: GetOwner()                   // return its observer
{
    return m_Owner;
}
void Ball:: SetPosition(int inX, int inY) // parameter stands for x coordinate andy coordinate
{
    m_Position.SetX(inX);
    m_Position.SetY(inY);
}
void Ball:: SetIsUpdated(bool inIs)       // parameter stands for whether ball info is updated
{
    m_IsUpdated = inIs;
}
bool Ball:: SetOwner(int inID)            // parameter stands for agent id , if it is within correct range ,return true
{
    if (inID >=1 && inID <=AG_NUM)
    {
        m_Owner = inID;
        return true;
    }
    else
    {
        m_IsUpdated =false;
        return false;
    }
}
//----------------------------------------- Ends Here -----------------------------------------------------
//****************************** Ball Class Defination Above *********************************************




//***************************** Role Control Class Defination Below ******************************************
//-------------------------------------- Starts Here ------------------------------------------------------

//Control Class
RoleControl::RoleControl()
{
    m_Ctrl = CTRL_STOP;
    m_TargetCoordinate.SetX(0);
    m_TargetCoordinate.SetY(0);
    m_SourceCoordinate.SetX(0);
    m_SourceCoordinate.SetY(0);
    m_TargetAngle = 0 ;
    m_DefenceAngle = 0;
    m_DefenceDistance = 0;
    m_re_ballx = 0 ;
    m_re_bally = 0;
    m_TargetGoal = false;
}
RoleControl::~RoleControl()
{
}
AgentControl RoleControl:: GetCtrl()                     // return current status
{
    return m_Ctrl;
}
Point RoleControl:: GetTargetCoor()               // Get target position , return a point
{
    return m_TargetCoordinate;
}
int  RoleControl:: GetTargetX()                 // Get x
{
    return m_TargetCoordinate.GetX();
}
int  RoleControl:: GetTargetY()                  // Get y
{
    return m_TargetCoordinate.GetY();
}
int  RoleControl:: GetDefDist()                  // Get defence distance
{
    return m_DefenceDistance;
}
int  RoleControl:: GetDefAngle()                 // Get defence angle
{
    return m_DefenceAngle;
}
void RoleControl:: SetCtrl(AgentControl inCtrl)          // Set contorl priority's role
{
    m_Ctrl = inCtrl;
}
void RoleControl:: SetTargetCoor(Point inCoordinate)
{
    m_TargetCoordinate.SetX(inCoordinate.GetX());
    m_TargetCoordinate.SetY(inCoordinate.GetY());
}
void RoleControl:: SetTargetX(int inX)
{
    m_TargetCoordinate.SetX(inX);
}
void RoleControl:: SetTargetY(int inY)
{
    m_TargetCoordinate.SetY(inY);
}
void RoleControl:: SetDefDist(int inDist)
{
    m_DefenceDistance = inDist;
}
void RoleControl:: SetDefAngle(int inAngle)
{
    m_DefenceAngle = inAngle;
}
//----------------------------------------- Ends Here -----------------------------------------------------
//************************** Role Control Class Defination Above *********************************************




//******************************* Agent Class Defination Below ******************************************
//-------------------------------------- Starts Here ------------------------------------------------------
Agent::Agent()
{
    m_Angle = 0;
    m_Position.SetX(0);
    m_Position.SetY(0);

    m_IsAgAllocated  = false;
    m_IsAgFoundBall  = false;
    m_IsAgHoldBall   = false;
    m_IsAgOnline     = false;
    m_PreStatus      = 0;
    m_Status         = 0;

    m_LinearSpeedAngle = 0;

    m_ObstacleCounter  = 0;
    for (int i = 0; i <= EACH_AG_OBST_NUM; i++)
    {
        m_Obstacle[i].SetPosition(0,0);

        m_Obstacle[i].SetSize(0);
        m_Obstacle[i].SetOwner(0);
        m_Obstacle[i].SetIsValid(false);
    }

    m_Ball.SetIsUpdated(false);
}

//Constructor
Agent::~Agent()
{
}
//Get ID
int Agent::GetID()
{
    return m_ID;
}
//Set ID
bool Agent::SetID(int inID)
{
    if (m_IsAgOnline == true && inID >= 1 && inID <= AG_NUM)
    {
        m_ID = inID;
        return true;
    }
    else
    {
        return false;
    }
}

int Agent::GetX()
{
    return m_Position.GetX();
}

int Agent::GetY()
{
    return m_Position.GetY();
}

bool Agent::SetPosition(int inX, int inY)
{
    if (m_IsAgOnline == true)
    {
        m_Position.SetX(inX);
        m_Position.SetY(inY);
        return true;
    }
    else
    {
        return false;
    }
}



bool Agent::IsAgHoldBall()
{
    return m_IsAgHoldBall;
}

bool Agent::SetIsHoldBall(bool Key)
{
    if (m_IsAgOnline == true)
    {
        m_IsAgHoldBall = Key;
        return true;
    }
    else
    {
        return false;
    }
}

bool Agent::IsAgFoundBall()
{
    return m_IsAgFoundBall;
}

bool Agent::SetIsFoundBall(bool Key)
{
    if (m_IsAgOnline == true)
    {
        m_IsAgFoundBall = Key;
        return true;
    }
    else
    {
        return false;
    }
}

bool Agent::IsAgOnline()
{
    return m_IsAgOnline;
}

void Agent::SetIsOnline(bool Key)
{
    m_IsAgOnline = Key;
}

bool Agent::IsAllocated()
{
    return m_IsAgAllocated;
}

bool Agent::SetIsAllocated(bool Key)
{
    if (m_IsAgOnline == true)
    {
        m_IsAgAllocated = Key;
        return true;
    }
    else
    {
        return false;
    }
}

double Agent::GetAngle()
{
    return m_Angle;
}

bool Agent::SetAngle(double inAng)
{
    if (m_IsAgOnline == true)
    {
        m_Angle = inAng;
        return true;
    }
    else
    {
        return false;
    }
}

AgentStatus Agent::GetStatus()
{
    return m_Status;
}

bool Agent::SetStatus(AgentStatus Ctrl)
{
    if (m_IsAgOnline == true)
    {
        m_Status = Ctrl;
        return true;
    }
    else
    {
        return false;
    }
}

AgentStatus Agent::GetPreStatus()
{
    return m_PreStatus;
}

bool Agent::SetPreStatus(AgentStatus Ctrl)
{
    if (m_IsAgOnline == true)
    {
        m_PreStatus = Ctrl;
        return true;
    }
    else
    {
        return false;
    }
}

AgentPriority Agent::GetPrio()
{
    return m_AgentPriority;
}

bool Agent::SavePrio(AgentPriority Seq)
{
    if (m_IsAgOnline == true &&(Seq == AG_PRIORITY_HIGH || Seq == AG_PRIORITY_LOW || Seq == AG_PRIORITY_MID))
    {
        m_AgentPriority = Seq;
        return true;
    }
    else
    {
        return false;
    }
}

Point Agent::GetPosition()
{
    return m_Position;
}



Obstacle Agent::GetObstacleInfo(int Obst_ID)
{
    if (Obst_ID > m_ObstacleCounter)
    {
        return m_Obstacle[0];
    }
    else
    {
        return m_Obstacle[Obst_ID];
    }
}

bool Agent::AddObstacle(int x, int y, int Size, int Owner, bool IsValid)
{
    m_ObstacleCounter ++;
    if (m_ObstacleCounter > EACH_AG_OBST_NUM)
    {
        return false;
    }
    if (m_IsAgOnline == false)
    {
        return false;
    }

    m_Obstacle[m_ObstacleCounter].SetPosition(x,y);
    m_Obstacle[m_ObstacleCounter].SetSize(Size);
    m_Obstacle[m_ObstacleCounter].SetOwner(Owner);
    m_Obstacle[m_ObstacleCounter].SetIsValid(IsValid);

    return true;
}

bool Agent::ClearObstacle()
{
    m_ObstacleCounter =0;

    if (m_IsAgOnline == false)
    {
        return false;
    }

    return true;
}

int Agent::GetObstacleCnt()
{
    return m_ObstacleCounter;
}

void Agent::SetIsObstacleValid(int id, bool flag)
{
    m_Obstacle[id].SetIsValid(flag);
}

bool Agent::CheckIsObstValid(int id)
{
    return m_Obstacle[id].CheckIsValid();
}

Ball Agent::GetBallInfo()
{
    return m_Ball;
}

bool Agent::SetBallInfo(int x, int y)
{
    if (m_IsAgFoundBall == false)
    {
        return false;
    }
    if (m_IsAgOnline == false)
    {
        return false;
    }
    m_Ball.SetPosition(x,y);
    return true;
}

double Agent::GetSpeed()
{
    return m_Speed;
}

void Agent::SetSpeed(double v)
{
    m_Speed = v;
}

double Agent::GetLinearSpeedAngle()
{
    return m_LinearSpeedAngle;
}

void Agent::SetLinearSpeedAngle(double ang)
{
    m_LinearSpeedAngle = ang;
}

void Agent::SetIP(string inIP)
{
    m_IP = inIP;
}

string Agent::GetIP()
{
    return m_IP;
}

bool Agent::IsAgMemOn()
{
    return m_IsAgMemOn;
}

void Agent::SetIsAgMemOn(bool key)
{
    m_IsAgMemOn = key;
}

int Agent::GetLaptopBattery()
{
    return m_LaptopBattery;
}

void Agent::SetLaptopBattery(int in)
{
    m_LaptopBattery = in;
}

int Agent::GetRobotVoltage()
{
    return m_RobotVoltage;
}

void Agent::SetRobotVlotage(int in)
{
    m_RobotVoltage = in;
}

//----------------------------------------- Ends Here -----------------------------------------------------
//******************************* Agent Class Defination Above *********************************************

ipCtrl::ipCtrl()
{
    isOnline = false;
    ip = "0.0.0.0";
    hasBeenSet = true;
}
