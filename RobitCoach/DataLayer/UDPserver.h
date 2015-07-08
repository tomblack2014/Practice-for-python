#pragma once
#include"stdlib.h"
#include"winsock.h"
#include"stdio.h"
#include"datalayer.h"
#include<iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

#define UPUDPBUFLEN 1024



class CUDPServer{
public:
	CUDPServer();
	virtual ~CUDPServer();
public:
	void Close();
    BOOL SetTarget(const char* inTIP, int inPort);                                  //Set aim IP and port
	BOOL Send(char *inbuf, int inLen);                                              //If SetTarget() finished,send inbuf whichs length is inLen to the target set
	BOOL Send(char *inTarIP, int inPort, char *inbuf, int inLen);                   //send inbuf to the aim IP and port
	BOOL Listen(int inPort);                                                        //Set your port and get ready to receive message from the Agent
	static DWORD WINAPI UDPReceiveThread(LPVOID pParam);                            //Begin a new thread to receive message from the Agent
    virtual void Received(unsigned char *inbuf, SOCKADDR* inpSock);      //Start to deal with the message after receiving it from the Agent
	
	SOCKET m_serverskt;                       //MSLCoach's address

	int sendres;                              //To see if there is an error when sendto()
	bool bConnected;	                      //To see whether m_sendskt is an INVALID_SOCKET

protected:                                    //target
	SOCKADDR_IN targAdr;                      //Agent's address
	int targAdrlen;                           //sizeof(SOCKADDR)
	char m_DesIP[16];                         //Agent's IP
	int m_DesPort;                            //Agent's PORT
	SOCKET m_sendskt;                         //SOCKET used in sendto() to send inbuf
	unsigned char m_tarIP[4];                 //Agent's IP
};

