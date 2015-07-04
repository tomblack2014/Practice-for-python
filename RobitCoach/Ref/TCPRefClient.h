#include<winsock.h>
#include<windows.h>
#include<string.h>
#include"DataLayer/DataLayer.h"
#include<QString>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

const char MSLS_Cyan = 0;
const char MSLS_Magenta = 1;

const char MSLS_FirstHalf = '1';
const char MSLS_SecondHalf = '2';
const char MSLS_halfTime = 'h';
const char MSLS_EndGame = 'e';

const char MSLS_Start = 's';
const char MSLS_Stop = 'S';
const char MSLS_Cancle = 'x';
const char MSLS_DroppedBall = 'N';
const char MSLS_EndHalf = 'h';
const char MSLS_Parking = 'L';

const char MSLS_Kick_off_Cyan = 'K';
const char MSLS_Freekick_Cyan = 'F';
const char MSLS_Goalkick_Cyan = 'G';
const char MSLS_Throwin_Cyan = 'T';
const char MSLS_Pentalty_Cyan = 'P';
const char MSLS_Goal_Cyan = 'A';
const char MSLS_Subgoal_Cyan = 'D';
const char MSLS_Corner_Cyan = 'C';

const char MSLS_Kick_off_Magenta = 'k';
const char MSLS_Freekick_Magenta = 'f';
const char MSLS_Goalkick_Magenta = 'g';
const char MSLS_Throwin_Magenta = 't';
const char MSLS_Pentalty_Magenta = 'p';
const char MSLS_Goal_Magenta = 'a';
const char MSLS_Subgoal_Magenta = 'd';
const char MSLS_Corner_Magenta = 'c';

const char MSLS_Restart = 'n';
const char MSLS_Dummy = '*';
const char MSLS_Ready = ' ';
 
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
    char GetGameStatus();
    bool hasStatusChanged();
    QString getStatusName();
    void SetGameStatus(QString name);
    void ManualSetStatus(char c);
    bool isSideCyan();
    void SetSide (bool isCyan);

private:
	SOCKET S;//socket to connect
	sockaddr_in Ref_addr;//box's location
	char IP[20];//IP
	int Port;//Port
	bool isConnected;
    char gameStatus;
    char preGameStatus;
    bool isCyan;
    QString currentStatus;
};
