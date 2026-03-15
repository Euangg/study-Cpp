#include<iostream>
using namespace std;

#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include"../VC-异步IO模型/Select模型Common.h"


SOCKET listenSocket = INVALID_SOCKET;
SOCKET communicateSocket = INVALID_SOCKET;

DWORD CALLBACK Thread(LPVOID) {
	cout << "启动线程" << endl;
	WinSockInit();


	sockaddr_in clientInfo;
	int iLenClientInfo;

	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET) {
		cout << "新建socket失败" << endl;
		goto __Error_End;
	}


	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(6666);

	if (bind(listenSocket, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		cout << "端口绑定失败" << endl;
		goto __Error_End;
	}
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "套接字设监听状态失败" << endl;
		goto __Error_End;
	}
	cout << "接收连接..." << endl;
	clientInfo = { 0 };
	iLenClientInfo = sizeof(clientInfo);
	communicateSocket = accept(listenSocket, (sockaddr*)&clientInfo, &iLenClientInfo);
	if (communicateSocket == INVALID_SOCKET) {
		//WSAEINVAL 10022 参数无效(套接字可能不是监听状态)

		cout << "收到失败连接" << WSAGetLastError() << endl;
		goto __Error_End;
	}
	cout << "收到连接" << endl;
	return TRUE;
	/*while (1) {
		if (SOCKE_Select(communicateSocket, 100, true)) {
			CHAR szBuf[MAX_BUF_SIZE] = { 0 };
			int iRet = recv(communicateSocket, (char*)szBuf, MAX_BUF_SIZE, 0);
			if (iRet > 0) {
				cout << szBuf << endl;
			}
			else {
				cout << "客户端已下线，请重启服务端等待连接" << endl;
				break;
			}
		}
	}*/

__Error_End:
	if (listenSocket != INVALID_SOCKET) {
		closesocket(listenSocket);
	}
	if (communicateSocket != INVALID_SOCKET) {
		closesocket(communicateSocket);
	}
	WSACleanup();
	return TRUE;
}

int main() {
	HANDLE sThread = CreateThread(NULL, 0, Thread, NULL, 0, nullptr);

	if (sThread) {
		WaitForSingleObject(sThread, INFINITE);
		
	}
	while (1) {
		if (SOCKE_Select(communicateSocket, 0, true)) {
			CHAR szBuf[MAX_BUF_SIZE] = { 0 };
			int iRet = recv(communicateSocket, (char*)szBuf, MAX_BUF_SIZE, 0);
			if (iRet > 0) {
				cout << szBuf << endl;
			}
			else {
				cout << "客户端已下线，请重启服务端等待连接" << endl;
				break;
			}
		}
	}
}