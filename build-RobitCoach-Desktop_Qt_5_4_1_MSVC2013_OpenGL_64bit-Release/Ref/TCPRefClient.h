#include<winsock.h>
#include<windows.h>
#include<string.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

const char Cyan = 0;
const char Magenta = 1;

const char FirstHalf = '1';
const char SecondHalf = '2';
const char halfTime = 'h';
const char EndGame = 'e';

const char Start = 's';
const char Stop = 'S';
const char Cancle = 'x';
const char DroppedBall = 'N';
const char EndHalf = 'h';
const char Parking = 'L';

const char Kick_off_Cyan = 'K';
const char Freekick_Cyan = 'F';
const char Goalkick_Cyan = 'G';
const char Throwin_Cyan = 'T';
const char Pentalty_Cyan = 'P';
const char Goal_Cyan = 'A';
const char Subgoal_Cyan = 'D';
const char Corner_Cyan = 'C';

const char Kick_off_Magenta = 'k';
const char Freekick_Magenta = 'f';
const char Goalkick_Magenta = 'g';
const char Throwin_Magenta = 't';
const char Pentalty_Magenta = 'p';
const char Goal_Magenta = 'a';
const char Subgoal_Magenta = 'd';
const char Ccorner_Magenta = 'c';

const char Restart = 'n';
const char Dummy = '*';
const char Ready = ' ';
 
const int BUFSIZE = 64;

class TCPRefClient{
public:
	TCPRefClient();
	~TCPRefClient();

	void SetIPPort(char inIP[], int inPort);//Set box's IP&Port
	void Connectto(char inIP[], int inPort = 28097);//Connect to the box
	void InbufHandling(char* inbuf,int inbuflen);//handle the message recved
	static DWORD WINAPI RecvThread(LPVOID p);//recv thread to recv message
	void Send(char* buf, int buflen);

private:
	SOCKET S;//socket to connect
	sockaddr_in Ref_addr;//box's location
	char IP[20];//IP
	int Port;//Port
	bool isConnected;
};