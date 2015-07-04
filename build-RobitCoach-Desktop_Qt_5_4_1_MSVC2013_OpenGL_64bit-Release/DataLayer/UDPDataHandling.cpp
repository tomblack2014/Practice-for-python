//#include"stdafx.h"
#include"UDPDataHandling.h"

CUDPDataHandling::CUDPDataHandling(Agent *inList)
{
	m_Agent = inList;
	for (int i = 0 ; i <= AG_NUM; i++)
	{
		msgCnt[i] = 0;
	}
}
void CUDPDataHandling::Received(unsigned char *inbuf, int inlen, SOCKADDR *inpSock){
    unsigned char* pch;
    pch = (unsigned char*)inpSock->sa_data;
	WORD iPort = ntohs(*(WORD*)pch);
    inIP[0] = pch[2]; inIP[1] = pch[3]; inIP[2] = pch[4]; inIP[3] = pch[5];
    m_curIP[0] = (int)pch[2];
    m_curIP[1] = (int)pch[3];
    m_curIP[2] = (int)pch[4];
    m_curIP[3] = (int)pch[5];

    char tmp[4][8];
    m_sCurIP = "";
    string temp[4];
    for (int i = 0 ; i < 4; i ++ )
    {
        sprintf_s(tmp[i],"%d",m_curIP[i]);
        temp[i] = tmp[i];
    }
    m_sCurIP = temp[0] + "." + temp[1] + "." + temp[2] + "." + temp[3];
    BufJudgement(inbuf);
	return;
}

void CUDPDataHandling::BufJudgement(unsigned char* inbuf){
	unsigned char* m_inbuf = inbuf;
	if (m_inbuf[0] != 85 || m_inbuf[1] != 170){
		return;
	}
	msgLen = m_inbuf[2];
	msgID = m_inbuf[3];
	msgCtrl = m_inbuf[4];
	if (m_calsum(m_inbuf, msgLen - 1) != m_inbuf[msgLen - 1]){
		return;
	}
    BufGetVaule(inbuf);
}

void CUDPDataHandling::BufGetVaule(unsigned char* inBuf){
	switch (msgCtrl){
		//preballs
	case MSL_PREDICTBALL:

		if (m_bFoundBall == true){
			SetPreball(inBuf[3], m_Piece2int(&inBuf[5]), m_Piece2int(&inBuf[7]));
		}
		break;
		//
	case MSL_DEBUG:{//It has no use[syc]
		int hball;
		int PlayerX;
		int PlayerY;
		int TargetX;
		int TargetY;
		hball = m_Piece2int(&inBuf[5]);
		PlayerY = m_Piece2int(&inBuf[7]);
		TargetX = m_Piece2int(&inBuf[9]);
		TargetY = m_Piece2int(&inBuf[11]);
		int nn = rand() % 10000;
		if (nn > 50)	{
			return;
		}
		break; 
	    }
	case MSL_INFO:	//Teammate information
		//whether this Teammate found ball or not
		if ((0x80 & inBuf[11]) > 0){
			m_bFoundBall = true;
		}
		else	{
			m_bFoundBall = false;
		}//renew teammate information
        SetAgent(
            inBuf[3],				//id
            m_Piece2int(&inBuf[5]),	//x
            m_Piece2int(&inBuf[7]),	//y
            m_Piece2int(&inBuf[9]),	//ang
            (int)inBuf[18],			//v
            m_Piece2int(&inBuf[16]),//v_angle
            (0x7f & inBuf[11]),	//status
            m_bFoundBall,     //foundb
            (int)inBuf[19]);	//holdball  [wzc] & [cyg]

		//renew ball information
		if (m_bFoundBall == true)	//foundball
		{
			int tmpx = m_Piece2int(&inBuf[12]);
			int tmpy = m_Piece2int(&inBuf[14]);
			m_Agent[inBuf[3]].SetBallInfo(tmpx,tmpy);
		}

		break;

	case MSL_OBST:	//Obstack information
		ClearObstBuf(msgID);
		int nNumofObst;
		nNumofObst = (msgLen - 7) / 5;
		int baseIndex;
		for (i = 0; i<nNumofObst; i++)
		{
			baseIndex = 6 + i * 5;
			AddObstToBuf(msgID, m_Piece2int(&inBuf[baseIndex]),
				         m_Piece2int(&inBuf[baseIndex + 2]), inBuf[baseIndex + 4]);
		}
		break;

	case MSL_KICK:	//someone  kicked-off
		Kick_Info[msgID].player_x = m_Piece2int(&inBuf[5]);
		Kick_Info[msgID].player_y = m_Piece2int(&inBuf[7]);
		Kick_Info[msgID].target_x = m_Piece2int(&inBuf[9]);
		Kick_Info[msgID].target_y = m_Piece2int(&inBuf[11]);
		Kick_Info[msgID].ID = msgID;
		break;
	}
}

void CUDPDataHandling::SetPreball(unsigned char ID, float ang, float len){
	Pre_Ball[ID].ang = ang;
	Pre_Ball[ID].len = len;
}

int CUDPDataHandling::m_Piece2int(unsigned char *inTarg)
{
	short ret;
	ret = inTarg[0];
	ret <<= 8;
	ret &= 0xff00;
	ret |= ((int)inTarg[1] & 0x00ff);
	return ret;
}

unsigned char CUDPDataHandling::m_calsum(unsigned char *inBuf, int inlen)
{
	unsigned char sum = 0;
	for (int i = 0; i<inlen; i++)
	{
		sum += inBuf[i];
	}
	return sum;
}

void CUDPDataHandling::SetAgent(unsigned char inID, int inx, int iny, double inangle, int inV, int inV_Angle, AgentStatus inStatus, bool infb, int inhb)
{

    //The Code below is designed for data checking, to see who's online;
    //check
    /*msgCnt[0]++;
    if (msgCnt[0]==20)
    {
        for (int i = 0; i <= AG_NUM; i++)
        {
            if (msgCnt[i] == 0)
            {
                m_Agent[i].SetIsOnline(false);
            }
            msgCnt[i] = 0;
        }
    }
    msgCnt[inID] = 1; */
    //----------------------------------------------------
    //ends here;
    //check every 25 frames, if there is no msg from an agent in 25 Msgs,
    //then we take it for granted that the agent is off line
    //when 2 or more agent connect to the coach , this approach is proved to be effective
    //but when it comes to the situation that there is only one agent  , these code can not
    //detect or determine when this agent goes off line, so
    //now it is substitued by ipCtrl management   [wzc]
    //ipCtrl management starts here-----------------------



    //if this agent is previously off line , then register it to the ipCtrl
    // if (hasbeenset == false); funtion "setTargetChecking()" in the Class "MainWindow"
    //will do the "SetTarget" action to update the Sender later [wzc]
    if (m_Agent[inID].IsAgOnline() == false)
    {
        m_ipCtrl[inID].hasBeenSet = false;
        m_ipCtrl[inID].ip = m_sCurIP;
    }

    //if this agent is changing it's IP address , then register it to the ipCtrl
    // if (hasbeenset == false); funtion "setTargetChecking()" in the Class "MainWindow"
    //will do the "SetTarget" action to update the Sender later [wzc]
    if (m_sCurIP != m_ipCtrl[inID].ip )
    {
        m_ipCtrl[inID].hasBeenSet = false;
        m_ipCtrl[inID].ip = m_sCurIP;
    }


    //register this agent in ipCtrl as online , 3000ms later, function "chechAgentOnlie"
    //in the "MainWindow" class will set isOnline as false, within the next 3000ms,
    //if there is no further infomation or msg comes from this ID, then we know that
    //this agent is offline [wzc]
    m_ipCtrl[inID].isOnline = true;

    //-----------------------------------------------------
    //ends here

    m_Agent[inID].SetIsOnline(true);
    m_Agent[inID].SetID(inID);
    m_Agent[inID].SetIP(m_sCurIP);
    m_Agent[inID].SetPosition(inx,iny);
    m_Agent[inID].SetSpeed(inV);
    m_Agent[inID].SetAngle(inangle);
    m_Agent[inID].SetLinearSpeedAngle(inV_Angle);
    m_Agent[inID].SetStatus(inStatus);
    m_Agent[inID].SetIsFoundBall(infb);
    bool tmp;
    if (inhb == 1)
    {
        tmp = true;
    }
    else
    {
        tmp = false;
    }
    m_Agent[inID].SetIsHoldBall(tmp);
}

void CUDPDataHandling::ClearObstBuf(int inID){
	if (inID >= MAX_TM){
		return;
	}
    m_Agent[inID].ClearObstacle();
}

void CUDPDataHandling::AddObstToBuf(int inID, int inX, int inY, int inSize)
{
	if (inID >= MAX_TM){
		return;
	}
	
	m_Agent[inID].AddObstacle(inX,inY,inSize,inID,true);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Data Sending part
// CatchCmd, CatchCmd_Normal, PassCmd, PassCmd_Normal   //Those function can be combined to one,but didn't
void CUDPDataHandling::PassCmd(int inTargX, int inTargY)
{
	m_sendbuf[2] = 15;							//len
	m_sendbuf[4] = MSL_CMD;
	m_sendbuf[9] = CTRL_PASS;					//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), inTargX);	//tx
	m_Split2Bytes(&(m_sendbuf[12]), inTargY);	//ty

	m_sendbuf[14] = m_calsum(m_sendbuf, 14);		//sum
	Send((char*)m_sendbuf, 15);
}
void CUDPDataHandling::PassCmd_Normal(int inTargX, int inTargY)
{
	m_sendbuf[2] = 15;							//len
	m_sendbuf[4] = MSL_CMD;
	m_sendbuf[9] = CTRL_3M_PASS;					//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), inTargX);	//tx
	m_Split2Bytes(&(m_sendbuf[12]), inTargY);	//ty

	m_sendbuf[14] = m_calsum(m_sendbuf, 14);		//sum
	Send((char*)m_sendbuf, 15);
}
void CUDPDataHandling::CatchCmd(int inFromX, int inFromY)
{
	m_sendbuf[2] = 15;							//len
	m_sendbuf[4] = MSL_CMD;
	m_sendbuf[9] = CTRL_CATCH;					//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), inFromX);	//fx
	m_Split2Bytes(&(m_sendbuf[12]), inFromY);	//fy

	m_sendbuf[14] = m_calsum(m_sendbuf, 14);		//sum
	Send((char*)m_sendbuf, 15);
}
void CUDPDataHandling::CatchCmd_Normal(int inFromX, int inFromY)
{
	m_sendbuf[2] = 15;							//len
	m_sendbuf[4] = MSL_CMD;
	m_sendbuf[9] = CTRL_3M_CATCH;					//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), inFromX);	//fx
	m_Split2Bytes(&(m_sendbuf[12]), inFromY);	//fy

	m_sendbuf[14] = m_calsum(m_sendbuf, 14);		//sum
	Send((char*)m_sendbuf, 15);
}

//CtrlCmd
void CUDPDataHandling::CtrlCmd(int inCtrl, int inReBx, int inReBy, int inAng, int inDist, bool inbField)
{
	m_sendbuf[2] = 15;
	m_sendbuf[4] = MSL_CMD;
	m_Split2Bytes(&(m_sendbuf[5]), inReBx);		//rebx
	m_Split2Bytes(&(m_sendbuf[7]), inReBy);		//reby	
	m_sendbuf[9] = (unsigned char)inCtrl;		//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), inAng);		//angle
	m_Split2Bytes(&(m_sendbuf[12]), inDist);		// dist

	m_sendbuf[14] = m_calsum(m_sendbuf, 14);		//sum
	//Send((char*)m_sendbuf,15);
	SendWithInitPos(m_sendbuf, 15);
}

//Predictball
void CUDPDataHandling::Predictball(int inCtrl, int inReBx, int inReBy, float jiao, float chang){
	m_sendbuf[2] = 15;
	m_sendbuf[4] = MSL_CMD;
	m_Split2Bytes(&(m_sendbuf[5]), inReBx);		//rebx
	m_Split2Bytes(&(m_sendbuf[7]), inReBy);		//reby	
	m_sendbuf[9] = (unsigned char)inCtrl;		//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), jiao * 100);		//angle
	m_Split2Bytes(&(m_sendbuf[12]), chang * 100);		// dist

	m_sendbuf[14] = m_calsum(m_sendbuf, 14);		//sum
	Send((char*)m_sendbuf, 15);

}


//DefCmd
void CUDPDataHandling::DefCmd(int inAngle, int inDist)
{
	//make inAngle between 0 and 360
	while (inAngle < 0)
	{
		inAngle += 360;
	}

	while (inAngle > 360)
	{
		inAngle -= 360;
	}

	if (inDist<0)
	{
		inDist = -inDist;
	}

	m_sendbuf[2] = 15;								//len
	m_sendbuf[4] = MSL_CMD;
	m_sendbuf[9] = CTRL_DEFENCE;					//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), inAngle);		//ang
	m_Split2Bytes(&(m_sendbuf[12]), inDist);			//dist

	m_sendbuf[14] = m_calsum(m_sendbuf, 14);			//sum
	Send((char*)m_sendbuf, 15);
}

void CUDPDataHandling::CtrlMidPassCmd(int ctrl, int mid_pass_x, int mid_pass_y, int mid_pass_believe, int mid_pass_jiao)
{
	m_sendbuf[2] = 19;								//len
	m_sendbuf[4] = MSL_CMD;
	m_sendbuf[9] = ctrl;						//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), mid_pass_x);		//x
	m_Split2Bytes(&(m_sendbuf[12]), mid_pass_y);		//y
	m_Split2Bytes(&(m_sendbuf[14]), mid_pass_believe);	//b
	m_Split2Bytes(&(m_sendbuf[16]), mid_pass_jiao);
	m_sendbuf[18] = m_calsum(m_sendbuf, 18);			//sum
	Send((char*)m_sendbuf, 19);
}


void CUDPDataHandling::FollowPosition(int inCtrl, int goalx, int goaly, int angle, int dist){

	m_sendbuf[2] = 18;
	m_sendbuf[4] = MSL_CMD;

	if (goaly>600){
		m_Split2Bytes(&(m_sendbuf[10]), goalx + 50);		//rebx
		m_Split2Bytes(&(m_sendbuf[12]), goaly - 50);		//reby	
		m_sendbuf[9] = (unsigned char)CTRL_MOVETO;		//ctrl
		m_Split2Bytes(&(m_sendbuf[14]), 0);		//angle
	}
	else{
		m_Split2Bytes(&(m_sendbuf[10]), goalx + 50);		//rebx
		m_Split2Bytes(&(m_sendbuf[12]), goaly + 50);		//reby	
		m_sendbuf[9] = (unsigned char)CTRL_MOVETO;		//ctrl
		m_Split2Bytes(&(m_sendbuf[14]), 0);		//angle
	}
	m_sendbuf[16] = 100;

	m_sendbuf[17] = m_calsum(m_sendbuf, 17);			//sum
	Send((char*)m_sendbuf, 18);
}

void CUDPDataHandling::MoveTo(int inTargetx, int inTargety, int inTargetAng, int inDist, bool inbField, int inSpd)
{
	//make inAngle between 0 and 360
	while (inTargetAng < 0)
	{
		inTargetAng += 360;
	}

	while (inTargetAng > 360)
	{
		inTargetAng -= 360;
	}

	if (inDist<0)
	{
		inDist = -inDist;
	}

	m_sendbuf[2] = 18;								//len
	m_sendbuf[4] = MSL_CMD;
	m_sendbuf[9] = CTRL_MOVETO;						//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), inTargetx);		//x
	m_Split2Bytes(&(m_sendbuf[12]), inTargety);		//y
	m_Split2Bytes(&(m_sendbuf[14]), inTargetAng);	//angle
	m_sendbuf[16] = (UCHAR)inSpd;

	m_sendbuf[17] = m_calsum(m_sendbuf, 17);			//sum
	Send((char*)m_sendbuf, 18);
}

void CUDPDataHandling::MoveCmd(int inTargetx, int inTargety, int inTargetAng, int inDist, bool inbField)
{
	//make inAngle between 0 and 360
	while (inTargetAng < 0)
	{
		inTargetAng += 360;
	}

	while (inTargetAng > 360)
	{
		inTargetAng -= 360;
	}

	if (inDist<0)
	{
		inDist = -inDist;
	}

	m_sendbuf[2] = 18;								//len
	m_sendbuf[4] = MSL_CMD;
	m_sendbuf[9] = CTRL_MOVETO;						//ctrl
	m_Split2Bytes(&(m_sendbuf[10]), inTargetx);		//x
	m_Split2Bytes(&(m_sendbuf[12]), inTargety);		//y
	m_Split2Bytes(&(m_sendbuf[14]), inTargetAng);	//angle
	m_sendbuf[16] = 100;

	m_sendbuf[17] = m_calsum(m_sendbuf, 17);			//sum
	Send((char*)m_sendbuf, 18);

}


void CUDPDataHandling::SendWithInitPos(BYTE *inBuf, int inTail)
{
	if (m_bInitPos == true)
	{
		BYTE* initbuf = &(inBuf[inTail]);
		initbuf[0] = 0x55;
		initbuf[1] = 0xaa;
		initbuf[2] = 13;
		initbuf[3] = m_sendbuf[3];
		initbuf[4] = MSL_INITPOS;
		initbuf[5] = 1;
		m_Split2Bytes(&(initbuf[6]), m_nInit_x);
		m_Split2Bytes(&(initbuf[8]), m_nInit_y);
		m_Split2Bytes(&(initbuf[10]), m_nInit_angle);
		initbuf[12] = m_calsum(initbuf, 12);		//sum
		Send((char*)inBuf, inBuf[2] + initbuf[2]);

		m_bInitPos = false;
	}
	else
	{
		Send((char*)inBuf, inTail);
	}
}

void CUDPDataHandling::m_Split2Bytes(unsigned char *inTarg, unsigned int inSrc)
{
	if (inTarg == NULL)
	{
		return;
	}

	unsigned short temp = (unsigned short)0x0000ffff & inSrc;
	inTarg[1] = (unsigned char)temp & 0x00ff;

	temp >>= 8;

	inTarg[0] = (unsigned char)temp & 0x00ff;
}

void CUDPDataHandling::AChangeStatus(UINT inCtrlCode, double inAngle, int inDist)
{
	CtrlCmd(inCtrlCode, trueball_x, trueball_y, (int)inAngle, inDist, inbField);
}

CUDPDataHandling::CUDPDataHandling(){
		m_sendbuf[0] = 0x55;
		m_sendbuf[1] = 0xaa;

		m_bInitPos = false;

		m_nInit_x = 900;
		m_nInit_y = 0;
		m_nInit_angle = 0;
}

void CUDPDataHandling::SetAgentID(int inID){
	AgentID = inID;
	m_sendbuf[3] = inID;
}

CUDPDataHandling::~CUDPDataHandling(){

}


void CUDPDataHandling::SetIpCtrl(ipCtrl *inCtrl)
{
    m_ipCtrl = inCtrl;
}
