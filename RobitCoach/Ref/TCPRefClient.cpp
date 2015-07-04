// TCPRefClient.cpp : 定义控制台应用程序的入口点。
//


#include"TCPRefClient.h"
#include"stdio.h"
DWORD WINAPI TCPRefClient::RecvThread(LPVOID inp)
{
	TCPRefClient* p = (TCPRefClient*)inp;
	char buf[BUFSIZE];
	int recvlen;
	recvlen = 0;
	while (p->S != INVALID_SOCKET)
	{
		recvlen = recv(p->S, buf, BUFSIZE, 0);
		if (recvlen <= 0)
		{
			break;
		}
		p->InbufHandling(buf, recvlen);
	}
	p->isConnected = false;
	return 0;
}

TCPRefClient::TCPRefClient()
{
	S = INVALID_SOCKET;
	isConnected = false;
    gameStatus = 'S';
    isCyan = true;
    currentStatus = "STOP";
}
char TCPRefClient::GetGameStatus()
{
        return gameStatus;
}

bool TCPRefClient::hasStatusChanged()
{
    if (preGameStatus == gameStatus)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void TCPRefClient::ManualSetStatus(char c)
{
    gameStatus = c;
}

TCPRefClient::~TCPRefClient()
{
}

void TCPRefClient::SetIPPort(char inIP[], int inPort)
{
	strcpy_s(IP, inIP);
	Port = inPort;

	return;
}

void TCPRefClient::Connectto(char inIP[], int inPort)
{
	strcpy_s(IP, inIP);
	Port = inPort;
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		return;
	}
	S = socket(AF_INET, SOCK_STREAM, 0);
	
	Ref_addr.sin_family = AF_INET;
	Ref_addr.sin_port = htons(Port);
	Ref_addr.sin_addr.s_addr = inet_addr(IP);

	if (connect(S, (sockaddr*)&Ref_addr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		return;
	}
	isConnected = true;

	CreateThread(NULL, 0, RecvThread, this, 0, NULL);

	return;
}

void TCPRefClient::Send(char* inbuf, int buflen)
{
	if (isConnected == true)
	{
		send(S, inbuf, buflen, 0);
	}
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!InbufHandling需由策略组编写!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void TCPRefClient::InbufHandling(char* inbuf, int buflen){
	printf("recv %d buf:", buflen);
	for (int i = 0; i < buflen; ++i){
		printf("%c", inbuf[i]);
	}
    if (buflen == 1)
    {
        preGameStatus = gameStatus;
        gameStatus = inbuf[0];
    }
	printf("\n");
	return ;
}

bool TCPRefClient::isSideCyan()
{
    return isCyan;
}

void TCPRefClient::SetSide(bool inIsCyan)
{
    isCyan = inIsCyan;
}

void TCPRefClient::SetGameStatus(QString name)
{
    currentStatus = name;
}

QString TCPRefClient::getStatusName()
{
    switch (gameStatus) {
    case MSLS_Stop:
        return "STOP";
        break;
    case MSLS_Start:
        return "START";
        break;
    case MSLS_Cancle:
        return "STOP";
        break;
    case MSLS_DroppedBall:
        return "DROP BALL";
        break;
    case MSLS_EndHalf:
        return "STOP";
        break;
    case MSLS_Parking:
        return "STOP";
        break;

    //---------------------------------------------------------------------
    //*****************command toward CYAN below***************************
    //---------------------------------------------------------------------
    case MSLS_Kick_off_Cyan:
        if (isCyan)
        {
            return "KICK OFF";
        }
        else
        {
            return "ANTI KICK OFF";
        }
        break;
    case MSLS_Freekick_Cyan:
        if (isCyan)
        {
            return "FREE KICK";
        }
        else
        {
            return "ANTI FREE KICK";
        }
        break;
    case MSLS_Goalkick_Cyan:
        if (isCyan)
        {
            return "GOAL KICK";
        }
        else
        {
            return "ANTI GOAL KICK";
        }
        break;
    case MSLS_Throwin_Cyan:
        if (isCyan)
        {
            return "THROW IN";
        }
        else
        {
            return "ANTI THROW IN";
        }
        break;
    case MSLS_Pentalty_Cyan:
        //TODO::真正的罚球
        if (isCyan)
        {
            return "STOP";
        }
        else
        {
            return "STOP";
        }
        break;
    case MSLS_Goal_Cyan:
        //TODO::不知道干嘛
        if (isCyan)
        {
            return "STOP";
        }
        else
        {
            return "STOP";
        }
        break;
    case MSLS_Subgoal_Cyan:
        //TODO::不知道干嘛
        if (isCyan)
        {
            return "STOP";
        }
        else
        {
            return "STOP";
        }
        break;
    case MSLS_Corner_Cyan:
        if (isCyan)
        {
            return "CORNER KICK";
        }
        else
        {
            return "ANTI CORNER KICK";
        }
        break;



    //---------------------------------------------------------------------
    //*****************command toward MAGENTA below***************************
    //---------------------------------------------------------------------
    case MSLS_Kick_off_Magenta:
        if (isCyan)
        {
            return "ANTI KICK OFF";
        }
        else
        {
            return "KICK OFF";
        }
        break;
    case MSLS_Freekick_Magenta:
        if (isCyan)
        {
            return "ANTI FREE KICK";
        }
        else
        {
            return "FREE KICK";
        }
        break;
    case MSLS_Goalkick_Magenta:
        if (isCyan)
        {
            return "ANTI GOAL KICK ";
        }
        else
        {
            return "GOAL KICK";
        }
        break;
    case MSLS_Throwin_Magenta:
        if (isCyan)
        {
            return "ANTI THROW IN";
        }
        else
        {
            return "THROW IN";
        }
        break;
    case MSLS_Pentalty_Magenta:
        //TODO::真正的罚球
        if (isCyan)
        {
            return "STOP";
        }
        else
        {
            return "STOP";
        }
        break;
     case MSLS_Goal_Magenta:
        //TODO::不知道干嘛
        if (isCyan)
        {
            return "STOP";
        }
        else
        {
            return "STOP";
        }
        break;
    case MSLS_Subgoal_Magenta:
        //TODO::不知道干嘛
        if (isCyan)
        {
            return "STOP";
        }
        else
        {
            return "STOP";
        }
        break;
    case MSLS_Corner_Magenta:
        if (isCyan)
        {
            return "ANTI CORNER KICK";
        }
        else
        {
            return "CORNER KICK";
        }
        break;
    case MSLS_Restart:
        //...
        return "STOP";
        break;
    case MSLS_Dummy:
        //,..
        return "STOP";
        break;
    case MSLS_Ready:
        //,..
        return "STOP";
        break;
    case MSLS_EndGame:
        return "STOP";
        break;
    default:
        return "STOP";
        break;
    }
}
