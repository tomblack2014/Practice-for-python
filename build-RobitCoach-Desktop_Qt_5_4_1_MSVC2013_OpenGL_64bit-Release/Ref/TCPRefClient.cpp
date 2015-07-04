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
	printf("\n");
	return ;
}