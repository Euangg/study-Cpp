//select选择模型，是WinSocket中最常见的IO模型，核心便是利用select函数，实现IO管理
//利用select函数来判断某socket上是否有数据可读，或者能否向一个套接字写入数据，防止程序在socket处于锁定模式中时，
//再次IO调用（如send、recv、accept等）过程中，被迫进入“锁定状态”；send、recv、accept等函数有阻塞特性
//同时防止再套接字处于非阻塞模式中时，产生WSAEWOULDBLOCK错误

//int select(
//	[i]		int nfds,						//忽略，传0即可，只是为了与Berkeley套接字兼容
//	[io]	fd_set* readfds,				//用于检查可读性，集合包括符合下面任意一个条件的套接字：1.有数据可读入 2.连接已关闭、重设或中止 3.假如已调用了listen，而且一个连接正在建立，那么accept函数调用会成功
//	[io]	fd_set* writefds,				//用于检查可写性，任一条件：1.有数据可以发出2.如果已经完成了对一个非锁定连接调用的处理，连接就会成功
//	[io]	fd_set* exceptfds,				//例外数据
//	[i]		const struct timeval* timeout	//一个指向timeval结构的指针，用于指定select函数等待的最长时间
//												如果为NULL，表示select函数会一直阻塞，直到有文件描述符准备好或者被信号中断
//												如果timeval结构中的秒和微秒都为零，表示select函数会立即返回，不会阻塞
//);
// 返回：-1表示出错，0表示没有任何套接字准备好，正数表示有几个套接字准备就绪
//typedef struct fd_set{
//		u_int fd_count;
//		SOCKET fd_array[FD_SETSIZE] 
// }fd_set;
// #define FD_SETSIZE 64
//注：fd_set中最多放64个套接字



#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
using namespace std;

#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include"Select模型Common.h"


//全局变量
SOCKET communicateSocket = INVALID_SOCKET;

DWORD CALLBACK ThreadProc(LPVOID) {
	WinSockInit();
	

	sockaddr_in server = { 0 };


	communicateSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (communicateSocket == INVALID_SOCKET) {
		cout << "新建socket失败" << endl;
		goto __Error_End;
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(6666);
	server.sin_addr.s_addr = inet_addr("192.168.1.101");
	if (connect(communicateSocket, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		//10038 WSAENOTSOCK 第一个参数不是套接字
		//10049 WSAEADDRNOTAVAIL 远程地址不是有效地址
		//10060 WSAETIMEDOUT 尝试连接超时，而未能建立连接
		//10061 WSAECONNREFUSED 连接被拒绝，目标计算机主动拒绝连接(目标计算机accept出问题)
		
		
		cout << "连接失败-" << errno << "\t" << WSAGetLastError() << endl;
		goto __Error_End;
	}
	while (1) {
		if (SOCKE_Select(communicateSocket)) {
			CHAR szBuf[MAX_BUF_SIZE] = { 0 };
			int iRet = recv(communicateSocket, (char*)szBuf, MAX_BUF_SIZE, 0);
			if (iRet > 0) {
				cout << szBuf << endl;
			}
			else {
				cout << "服务端已下线，连接断开" << endl;
				break;
			}
		}
	}

__Error_End:
	if (communicateSocket != INVALID_SOCKET) {
		closesocket(communicateSocket);
	}
	WSACleanup();
	return TRUE;
}


int main() {

	HANDLE cThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, nullptr);

	bool isSendKeyAUp = false;
	bool isSendKeyDown = true;
	string str = "hello";
	while (1) {
		//按键抬起消息生成
		if (GetAsyncKeyState('A')) {
			isSendKeyDown = true;
		}
		else if (isSendKeyDown) {
			isSendKeyDown = false;
			isSendKeyAUp = true;
		}
		//发送
		if (isSendKeyAUp) {
			send(communicateSocket, str.c_str(), str.length(), 0);
		}


		//按键抬起消息回收
		isSendKeyAUp = false;
	}

	return 0;
}