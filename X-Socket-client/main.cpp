#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#include<iostream>
using namespace std;

class datapack {
public:
	int m_int;
	float m_float;
	char m_char;

public:
	void show() {
		cout << m_int << " " << m_float << " " << m_char << endl;
	}
};

struct pack_net {
public:
	float x;
	float y;
public:
	void show() {
		cout << x << " " << y << endl;
	}
};

struct pack_thread
{
	SOCKET m_socket;
	pack_net* pNetPack;
};

DWORD CALLBACK SendThread(LPVOID pParam) {
	pack_thread* pThreadPack = (pack_thread*)pParam;
	SOCKET sock = pThreadPack->m_socket;
	//datapack tpak = { 765,1.23456f,'X' };
	/*pack_net tpak;
	tpak.x = 1.23456f;
	tpak.y = 9.87654f;*/
	pack_net* pNetPack = pThreadPack->pNetPack;

	while (true) {
		/*if (GetAsyncKeyState('W')) {
			send(*pSock, "W", 1, 0);
		}
		if (GetAsyncKeyState('S')) {
			send(*pSock, "S", 1, 0);
		}
		if (GetAsyncKeyState('A')) {
			send(*pSock, "A", 1, 0);
		}
		if (GetAsyncKeyState('D')) {
			send(*pSock, "D", 1, 0);
		}*/
		if (GetAsyncKeyState('W')) {
			send(sock, (char*)pNetPack, sizeof(pack_net), 0);
		}
	}
	return 0;
}

DWORD CALLBACK RecvThread(LPVOID psocket) {
	SOCKET* pSock = (SOCKET*)psocket;
	char data_recv[2] = { 0 };
	while (true) {
		int iRet_recv = recv(*pSock, data_recv, 1, 0);
		cout << data_recv;
	}
	return 0;
}

int main() {
	datapack tstpack;
	tstpack.m_int = 666;
	tstpack.m_float = 1.23456f;
	tstpack.m_char = 'X';
	tstpack.show();

	WSADATA wsaData = { 0 };
	int iRet_startup = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet_startup == NO_ERROR) {
		cout << "WSA初始化成功" << endl;
	}
	else {
		cout << "初始化WSA失败！" << endl;
		return 0;
	}

	//SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//UDP
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "创建客户端SOCKET失败！" << endl;
		return 0;
	}
	else {
		cout << "SOCKET创建成功" << endl;
	}


	//确认
	cout << "确认并开始连接服务端？" << endl;
	getchar();
	cout << "开始连接..." << endl;

	//3）向服务端请求连接connect
	//服务端信息
	sockaddr_in serverInfo = { 0 };
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = htonl(0xC0A80165);//192.168.1.101
	//转换后为6501A8C0
	serverInfo.sin_port = htons(6666);
	//开始连接
	int iRet_connect = connect(clientSocket, (sockaddr*)&serverInfo, sizeof(serverInfo));
	//参数：1.套接字
	//		2.目标服务器的地址信息（含IP和端口）
	//		3.参数2的大小
	//返回：成功返回0，失败返回-1
	if (iRet_connect == SOCKET_ERROR) {
		cout << "连接服务端失败！" << endl;
		return 0;
	}
	else {
		cout << "服务端连接成功" << endl;
	}

	//4）向服务端发送信息send
	//char data_send[256] = { 0 };
	//cout << "：";
	//cin >> data_send;
	//int iRet_send = send(clientSocket, data_send, 256, 0);
	//if (iRet_send == SOCKET_ERROR) {
	//	cout << "发送数据错误！" << endl;
	//	return 0;
	//}
	//if (iRet_send == 0) {
	//	cout << "连接中断" << endl;
	//	return 0;
	//}
	//else {
	//	cout << "发送了" << iRet_send << "字节的数据" << endl;
	//}
	pack_net NetPack;
	NetPack.x = 1.23456f;
	NetPack.y = 9.87654f;
	pack_thread ThreadPack;
	ThreadPack.m_socket = clientSocket;
	ThreadPack.pNetPack = &NetPack;
	CreateThread(NULL, 0, SendThread, &ThreadPack, 0, nullptr);



	CreateThread(NULL, 0, RecvThread, &clientSocket, 0, nullptr);
	getchar();


	//5）从服务端接收消息recv
	/*char data_recv[256] = { 0 };
	int iRet_recv = recv(clientSocket, data_recv, 256, 0);
	if (iRet_recv == SOCKET_ERROR) {
		cout << "接收数据错误！" << endl;
		return 0;
	}
	if (iRet_recv == 0) {
		cout << "连接中断" << endl;
		return 0;
	}
	else {
		cout << "接受了" << iRet_recv << "字节的数据" << endl;
		cout << "数据内容：" << data_recv << endl;
	}*/
	
	//6）关闭套接字
	closesocket(clientSocket);

	//7）关闭WSA
	WSACleanup();
	
	return 0;
}