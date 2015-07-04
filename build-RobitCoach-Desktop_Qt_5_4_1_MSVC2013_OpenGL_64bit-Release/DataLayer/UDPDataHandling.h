#include"UDPserver.h"
#define MAX_OBST 10
#define MAX_TM 7
#define TO_AG_OB_NUM MAX_OBST
//#include "qmessagebox.h"

//#include "qdebug.h"
typedef struct preball{
	float ang, len;
}PREBALL;//predict ball
typedef struct kickinfo{
	int player_x, player_y;
	int target_x, target_y;
	int ID;
}KICKINFO;

class CUDPDataHandling :public CUDPServer{
public:
	void SetAgent(unsigned char inID, int inx, int iny, double inangle, int inV, int inV_Angle, UINT inStatus, bool infb, int inhb);
	void SetPreball(unsigned char ID, float ang, float len);
	void BufGetVaule(unsigned char* inbuf);
	void BufJudgement(unsigned char* inbuf);
	void Received(unsigned char *inbuf, int inlen, SOCKADDR* inpSock);
private:
	void ClearObstBuf(int inID);
	unsigned char m_calsum(unsigned char *inBuf, int inlen);
	int m_Piece2int(unsigned char *inTarg);
	void AddObstToBuf(int inID, int inX, int inY, int inSize);
private:
	int i;
	char msgLen;
	char msgID;
	char msgCtrl;
	char inIP[4];
	bool m_bFoundBall;
	int  msgCnt[AG_NUM+1];
public:
	PREBALL Pre_Ball[MAX_TM];
	KICKINFO Kick_Info[MAX_TM];
//Data received handling
//====================================================
//Data to send handling
public:
	CUDPDataHandling();
	CUDPDataHandling(Agent *inList);
	virtual ~CUDPDataHandling();
public:
    void SetIpCtrl(ipCtrl *inCtrl);
	void SetAgentID(int inID);
	void AChangeStatus(UINT inCtrlCode, double inAngle = 15, int inDist = 18);
	void CatchCmd(int inFromX, int inFromY);
	void CatchCmd_Normal(int inFromX, int inFromY);
	void PassCmd(int inTargX, int inTargY);
	void PassCmd_Normal(int inTargX, int inTargY);
	void CtrlCmd(int inCtrl, int inReBx, int inReBy, int inAng, int inDist, bool inbField);
	void Predictball(int inCtrl, int inReBx, int inReBy, float jiao, float chang);
	void DefCmd(int inAngle, int inDist);
	void CtrlMidPassCmd(int ctrl, int mid_pass_x, int mid_pass_y, int mid_pass_believe, int mid_pass_jiao);
	void FollowPosition(int inCtrl, int goalx, int goaly, int angle, int dist);
	void MoveTo(int inTargetx, int inTargety, int inTargetAng, int inDist, bool inbField, int inSpd);
	void MoveCmd(int inTargetx, int inTargety, int inTargetAng, int inDist, bool inbField);
	void SendWithInitPos(BYTE *inBuf, int inTail);

protected:
	void m_SendWithTail(BYTE* inBuf, int inTail);
	void m_Split2Bytes(unsigned char *inTarg, unsigned int inSrc);

	unsigned char m_sendbuf[1024];

	
	int trueball_x;
	int trueball_y;
	bool inbField;
	
	bool m_bInitPos;
	int m_nInit_x;
	int m_nInit_y;
	int m_nInit_angle;

	int AgentID;

    int m_curIP[4];
    string m_sCurIP;


    ipCtrl  *m_ipCtrl;


//==================================================
//Data storage
private:
	Agent *m_Agent;
};
