//对等通信：服务端与客户端发送的消息类型一样，接收的消息类型一样

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
using namespace std;
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

enum XInfo :char {
	XI_NoInfo = -1,

	XI_PlayerInfo = 0,

	XI_InfoTypes
};
class XPack {
public:
	XInfo infoType;
public:
	XPack(XInfo infotype) :infoType(infotype) {};
};
class XPack_Player :public XPack {//Player信息包
public:
	bool isExist;
	unsigned char controlSig;
public:
	XPack_Player() :XPack(XI_PlayerInfo) {};
};
int GetInfoPackSize(XInfo infotype) {
	switch (infotype)
	{
	case XI_PlayerInfo:
		return sizeof(XPack_Player);
		break;
	}
}


char pChar_comData[256] = { 0 };//传输字节——ok
XPack_Player pack;//传输类对象

bool isConnected = false;
bool isNewMessageToSend = false;

DWORD CALLBACK SendThread(LPVOID pParam) {
	SOCKET comSocket = (SOCKET)pParam;
	while (true) {
		/*XInfo infotype = list_netPack_Send.GetAInfo();
		if (infotype != XInfo::XI_NoInfo) {
			send(comSocket, (char*)(list_netPack_Send.packs[infotype].pPack), list_netPack_Send.packs[infotype].packSize, 0);
		}*/

		//传输字节
		/*if (isNewMessageToSend) {
			send(comSocket, pChar_comData, strlen(pChar_comData), 0);
			isNewMessageToSend = false;
		}*/
		//传输对象，使用对象
		if (isNewMessageToSend) {
			send(comSocket, (char*)&pack, sizeof(XPack_Player), 0);
			isNewMessageToSend = false;
		}
	}
	return 0;
}
DWORD CALLBACK RecvThread(LPVOID pParam) {
	SOCKET comSocket =(SOCKET)pParam;
	char buf[256] = { 0 };
	XPack_Player recvpack;
	recvpack.controlSig = 99;
	recvpack.isExist = false;
	int comState = 0;
	cout << "开始消息传输" << endl;
	while (true) {
		//recv(comSocket, buf, 256, 0);//不分类型冗余接收
		//XPack* pPack = (XPack*)buf;
		//XInfo infoType = pPack->infoType;//infoType必在有效队列中，不判断有效性
		//list_netPack_Recv.packs[infoType].isNew = true;
		//memcpy(list_netPack_Recv.packs[infoType].pPack, buf, GetInfoPackSize(infoType));

		//传输字节
		//comState =recv(comSocket, buf, 256, 0);//冗余接收
		//传输类对象//缓冲区使用字节
		comState = recv(comSocket, buf, 256, 0);//冗余接收
		//传输类对象//缓冲区使用对象
		//comState = recv(comSocket, (char*)&recvpack, sizeof(XPack_Player), 0);//对等接收
		if (comState == 0) {
			cout << "连接断开" << endl;
			break;
		}
		else if (comState < 0) {
			int errCode = WSAGetLastError();
			cout << "发生错误！" << errCode << endl;
			
			//WSANOTINITIALISED	10093
			//WSAENETDOWN		10050
			//WSAEFAULT			10014
			//WSAENOTCONN		10057
			//WSAEINTR			10004
			//WSAEINPROGRESS	10036
			//WSAENETRESET		10052
			//WSAENOTSOCK		10038	recv参数1不是套接字
			//WSAEOPNOTSUPP		10045
			//WSAESHUTDOWN		10058
			//WSAEWOULDBLOCK	10035
			//WSAEMSGSIZE		10040
			//WSAEINVAL			10022
			//WSAECONNABORTED	10053
			//WSAETIMEDOUT		10060
			//WSAECONNRESET		10054	执行硬性或异常关闭的远程端重置了虚拟线路。 因为套接字不可再用，应用程序应关闭套接字


			break;
		}
		else {
			//字节
			//cout << ":" << buf << endl;
			//类对象，字节
			/*XPack_Player* pplayer = (XPack_Player*)buf;
			cout << "class:" << endl;
			cout << "\tcontrolSig" << (int)pplayer->controlSig << endl;
			cout << "\tinfoType" << (int)pplayer->infoType << endl;
			cout << "\tisExist"<< (int)pplayer->isExist << endl;*/
			//类对象，对象
			/*cout << "class:" << endl;
			cout << "\tcontrolSig" << (int)recvpack.controlSig << endl;
			cout << "\tinfoType" << (int)recvpack.infoType << endl;
			cout << "\tisExist" << (int)recvpack.isExist << endl;*/

			//内存拷贝(字节->对象),字节空间接收，内存拷贝到对象空间
			memcpy(&recvpack, buf, sizeof(recvpack));
			cout << "\tcontrolSig" << (int)recvpack.controlSig << endl;
			cout << "\tinfoType" << (int)recvpack.infoType << endl;
			cout << "\tisExist" << (int)recvpack.isExist << endl;

		}
	}
	return 0;
}

DWORD CALLBACK ServerAcceptThread(LPVOID pParam) {
	SOCKET serverSocket = (SOCKET)pParam;
	//s6.接收客户端连接
	sockaddr_in clientInfo = { 0 };
	int len_clientInfo = sizeof(clientInfo);
	SOCKET comSocket = accept(serverSocket, (sockaddr*)&clientInfo, &len_clientInfo);
	//s7.创建收发线程
	cout << "收到连接" << inet_ntoa(clientInfo.sin_addr) << endl;
	CreateThread(NULL, 0, SendThread, (LPVOID)comSocket, 0, nullptr);
	CreateThread(NULL, 0, RecvThread, (LPVOID)comSocket, 0, nullptr);
	isConnected = true;
	return 0;
}

int main() {
	//预知信息
	cout << "sizeof(XPack)=" << sizeof(XPack) << endl;
	cout << "sizeof(XPack_Player)=" << sizeof(XPack_Player) << endl;

	int type = 0;
tag_start:
	cout << "通信端类型？（0.client,1.server）" << endl;
	cin >> type;
	if (type != 0 && type != 1) {
		cout << "输入的通信端类型无效，请重新输入" << endl;
		goto tag_start;
	}
	//cs1.初始化套接字通信系统
	WSAData wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (type == 0) {//客户端
		//c2.创建端口通信套接字
		SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP);
		//c3.向服务端请求连接
		sockaddr_in serverInfo = { 0 };
		serverInfo.sin_family = AF_INET;
		//serverInfo.sin_addr.s_addr = htonl(0xC0A80165);//192.168.1.101
		char pChar_serverIp[256] = { 0 };
	tag_inputServerIp:
		cout << "输入目标服务端IP：" << endl;
		cin >> pChar_serverIp;
		cout << "正在连接" << pChar_serverIp << "..." << endl;
		serverInfo.sin_addr.s_addr = inet_addr(pChar_serverIp);
		serverInfo.sin_port = htons(6666);
		int iRet_connect = connect(clientSocket, (sockaddr*)&serverInfo, sizeof(serverInfo));
		if (iRet_connect == SOCKET_ERROR) {
			cout << "连接到" << pChar_serverIp << "失败" << endl;
			goto tag_inputServerIp;
		}
		cout << "成功连接到" << pChar_serverIp << endl;
		//c4.创建收发线程
		CreateThread(NULL, 0, SendThread, (LPVOID)clientSocket, 0, nullptr);
		CreateThread(NULL, 0, RecvThread, (LPVOID)clientSocket, 0, nullptr);
		isConnected = true;
	}
	else if (type == 1) {//服务端
		//s2.服务端开放监听套接字
		SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP);
		//s3.监听套接字绑定指定端口
		sockaddr_in serverInfo = { 0 };
		serverInfo.sin_family = AF_INET;
		serverInfo.sin_addr.s_addr = htonl(INADDR_ANY);//绑定本机所有可得到的IP
		serverInfo.sin_port = htons(6666);
		bind(serverSocket, (sockaddr*)&serverInfo, sizeof(serverInfo));
		//s4.监听端口开启
		listen(serverSocket, SOMAXCONN);
		//s5.创建监听线程
		HANDLE hServerAcceptThread = CreateThread(NULL, 0, ServerAcceptThread, (LPVOID)serverSocket, 0, nullptr);
		//(sf.获取本地主机信息)
		//获取主机名
		char hostname[256] = { 0 };
		gethostname(hostname, sizeof(hostname));
		//获取主机ip
		HOSTENT* host = gethostbyname(hostname);
		char pChar_serverInfo[256];
		strcpy_s(pChar_serverInfo, inet_ntoa(*(in_addr*)*(host->h_addr_list)));
		cout << "server ip:" << pChar_serverInfo << endl;
	}
	
	
	pack.controlSig = 111;
	pack.isExist = true;

	while (true) {
		if (isConnected) {
			Sleep(1000);
			//字节
			//cin >> pChar_comData;
	
			//类对象
			cout << "controlSig:";
			int sig = 0;
			cin >> sig;
			pack.controlSig = sig;

			isNewMessageToSend = true;
		}
	}
}