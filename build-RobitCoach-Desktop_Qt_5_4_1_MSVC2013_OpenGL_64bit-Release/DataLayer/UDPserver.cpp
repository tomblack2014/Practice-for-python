#include "UDPServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDPServer::CUDPServer()
{
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0){
		return;
	}
	m_sendskt = INVALID_SOCKET;
	m_DesPort = -1;
	bConnected = false;
}

CUDPServer::~CUDPServer()
{

}

DWORD WINAPI CUDPServer::UDPReceiveThread(LPVOID pParam)
{
    CUDPServer* pudp = (CUDPServer*)pParam;

	int reclen = 0;

	char buffer[UPUDPBUFLEN] = "\0";
	SOCKADDR linkAdr;
	int len = sizeof(SOCKADDR);

	while (pudp->m_serverskt != INVALID_SOCKET){
		reclen = recvfrom((pudp->m_serverskt), buffer, UPUDPBUFLEN, 0, (SOCKADDR*)&linkAdr, &len);
		if (reclen != SOCKET_ERROR){
			pudp->Received((unsigned char*)buffer, reclen, (SOCKADDR*)&linkAdr);
		}
	}

	if (pudp->m_serverskt != INVALID_SOCKET){
		closesocket(pudp->m_serverskt);
		pudp->m_serverskt = INVALID_SOCKET;
	}

	return 1;
}

BOOL CUDPServer::Listen(int inPort)
{
    if (m_serverskt != INVALID_SOCKET)
	{
		closesocket(m_serverskt);
		m_serverskt = INVALID_SOCKET;
		Sleep(100);	
	}

	SOCKADDR_IN local;
	targAdrlen = sizeof(SOCKADDR);

	local.sin_family = AF_INET;
	local.sin_port = htons(inPort);             
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	m_serverskt = socket(AF_INET, SOCK_DGRAM, 0);
	if (bind(m_serverskt, (SOCKADDR*)&local, sizeof(SOCKADDR)) != 0)
	{
		return FALSE;
	}
	CreateThread(NULL, 0, UDPReceiveThread, this, 0, NULL);
	return TRUE;
}

BOOL CUDPServer::Send(char *inTarIP, int inPort, char *inbuf, int inLen)
{
	if (inPort<0 || inTarIP == NULL)
	{
		return FALSE;
	}

	targAdrlen = sizeof(SOCKADDR);

	targAdr.sin_family = AF_INET;
	targAdr.sin_port = htons(inPort);             
	targAdr.sin_addr.s_addr = inet_addr(inTarIP); 

	//change IP to 4 char
	SOCKADDR* pAddr = (SOCKADDR*)&targAdr;
	unsigned char* pch = (unsigned char*)pAddr->sa_data;
	pch += 2;
	memcpy(m_tarIP, pch, 4);

	if (m_sendskt != INVALID_SOCKET)
	{
		closesocket(m_sendskt);
		m_sendskt = INVALID_SOCKET;
	}

	m_sendskt = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_sendskt == INVALID_SOCKET)
	{
       return FALSE;
	}

	sendres = sendto(m_sendskt, inbuf, inLen, 0, (SOCKADDR*)&targAdr, targAdrlen);
	if (sendres == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CUDPServer::Send(char *inbuf, int inLen)
{
	if (m_sendskt == INVALID_SOCKET)
	{
		return FALSE;
	}

	sendres = sendto(m_sendskt, inbuf, inLen, 0, (SOCKADDR*)&targAdr, targAdrlen);
	if (sendres == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CUDPServer::SetTarget(const char* inTIP, int inPort)
{
	if (inPort<0)
	{
		return FALSE;
	}

	strcpy_s(m_DesIP, inTIP);
	m_DesPort = inPort;

	targAdrlen = sizeof(SOCKADDR);

	targAdr.sin_family = AF_INET;
	targAdr.sin_port = htons(m_DesPort);          
	targAdr.sin_addr.s_addr = inet_addr(m_DesIP); 

	SOCKADDR* pAddr = (SOCKADDR*)&targAdr;
	unsigned char* pch = (unsigned char*)pAddr->sa_data;
	pch += 2;
	memcpy(m_tarIP, pch, 4);

	if (m_sendskt != INVALID_SOCKET)
	{
		closesocket(m_sendskt);
		m_sendskt = INVALID_SOCKET;
	}

	m_sendskt = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_sendskt == INVALID_SOCKET)
	{
        return FALSE;
	}

	bConnected = true;
	return TRUE;
}

void CUDPServer::Close()
{
	if (m_sendskt != INVALID_SOCKET)
	{
		closesocket(m_sendskt);
	}

	if (m_serverskt != INVALID_SOCKET)
	{
		closesocket(m_serverskt);
	}
}

void CUDPServer::Received(unsigned char *inbuf, int inlen, SOCKADDR* inpSock){
    unsigned char* pch = (unsigned char*)inpSock->sa_data;
	WORD iPort = ntohs(*(WORD*)pch);
}
