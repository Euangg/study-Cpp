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

DWORD CALLBACK SendThread(LPVOID psocket) {
	SOCKET* pSock = (SOCKET*)psocket;
	while (true) {
		if (GetAsyncKeyState('I')) {
			send(*pSock, "I", 1, 0);
		}
		if (GetAsyncKeyState('K')) {
			send(*pSock, "K", 1, 0);
		}
		if (GetAsyncKeyState('J')) {
			send(*pSock, "J", 1, 0);
		}
		if (GetAsyncKeyState('L')) {
			send(*pSock, "L", 1, 0);
		}
	}
	return 0;
}

DWORD CALLBACK RecvThread(LPVOID pParam) {
	pack_thread* pThreadPack = (pack_thread*)pParam;
	SOCKET sock = pThreadPack->m_socket;
	char data_recv[2] = { 0 };
	//datapack tpak = { 0 };
	//pack_net tpak;
	pack_net* pNetPack = pThreadPack->pNetPack;

	while (true) {
		/*int iRet_recv = recv(*pSock, data_recv, 1, 0);
		cout << data_recv;*/
		recv(sock, (char*)pNetPack, sizeof(pack_net), 0);
		//pNetPack->show();
	}
	return 0;
}

int main() {
	//1）初始化套接字通信
	WSADATA wsaData = { 0 };
	int iRet_startup = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet_startup == NO_ERROR) {
		cout << "WSA初始化成功" << endl;
	}
	else {
		cout << "初始化WSA失败！" << endl;
		return 0;
	}

	//2）创建监听用套接字
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "创建服务端SOCKET失败！" << endl;
		return 0;
	}
	else {
		cout << "SOCKET创建成功" << endl;
	}

	//3）绑定套接字到通信端口bind
	sockaddr_in serverInfo = { 0 };
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = htonl(INADDR_ANY);//绑定本机所有可得到的IP
	serverInfo.sin_port = htons(6666);
	int iRet_bind = bind(serverSocket, (sockaddr*)&serverInfo, sizeof(serverInfo));
	if (iRet_bind == SOCKET_ERROR) {
		cout << "绑定监听SOCKET到指定端口失败！" << endl;
		return 0;
	}
	else {
		cout << "端口绑定成功" << endl;
	}

	//4）端口监听listen
	int iRet_listen = listen(serverSocket, SOMAXCONN);
	if (iRet_listen == SOCKET_ERROR) {
		cout << "监听在指定端口失败！" << endl;
	}
	else {
		cout << "端口监听成功" << endl;
	}

	//5）接收客户端信号accept
	sockaddr_in clientInfo = { 0 };
	int len_clientInfo = sizeof(clientInfo);
	cout << "等待连接..." << endl;
	SOCKET communicateSocket = accept(serverSocket, (sockaddr*)&clientInfo, &len_clientInfo);
	cout << "收到一个连接" << clientInfo.sin_addr.S_un.S_addr << ":" << clientInfo.sin_port << endl;

	//6）读取客户端消息recv
	//char data_recv[256] = { 0 };
	//int iRet_recv = recv(communicateSocket, data_recv, 256, 0);
	//if (iRet_recv == SOCKET_ERROR) {
	//	cout << "接收数据错误！" << endl;
	//	return 0;
	//}
	//if (iRet_recv == 0) {
	//	cout << "连接中断" << endl;
	//	return 0;
	//}
	//else {
	//	cout << "接受了" << iRet_recv << "字节的数据" << endl;
	//	cout << "数据内容：" << data_recv << endl;
	//}
	pack_net NetPack;
	pack_thread ThreadPack;
	ThreadPack.m_socket = communicateSocket;
	ThreadPack.pNetPack = &NetPack;
	CreateThread(NULL, 0, RecvThread, &ThreadPack, 0, nullptr);

	while (true){
		NetPack.show();
	}

	CreateThread(NULL, 0, SendThread, &communicateSocket, 0, nullptr);
	getchar();

	//7）向客户端发送消息send
	/*char data_send[256] = { 0 };
	cout << "：";
	cin >> data_send;
	int iRet_send = send(communicateSocket, data_send, 256, 0);
	if (iRet_send == SOCKET_ERROR) {
		cout << "发送数据错误！" << endl;
		return 0;
	}
	if (iRet_send == 0) {
		cout << "连接中断" << endl;
		return 0;
	}
	else {
		cout << "发送了" << iRet_send << "字节的数据" << endl;
	}*/
	
	//8）关闭套接字
	closesocket(serverSocket);

	//9）关闭WSA
	WSACleanup();

	return 0;
}