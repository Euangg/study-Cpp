#pragma once
#include<winsock2.h>
#define MAX_BUF_SIZE 1024

//初始化WSA
bool WinSockInit() {
	WSADATA wsaData = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))return false;
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return false;
	}
	return true;
}
//异步IO选择模型
bool SOCKE_Select(SOCKET hSocket, int nTimeOut = 100, BOOL bRead = true) {
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);//将目标套接字放入条件队列
	nTimeOut = nTimeOut > 1000 ? 1000 : nTimeOut;
	tv.tv_sec = 0;
	tv.tv_usec = nTimeOut;

	int iRet = 0;
	if (bRead) {
		iRet = select(0, &fdset, NULL, NULL, &tv);//检查，套件字不满足条件会被淘汰出队列
	}
	else {
		iRet = select(0, NULL, &fdset, NULL, &tv);//检查，套件字不满足条件会被淘汰出队列
	}
	if (iRet <= 0) {
		return FALSE;
	}
	else if (FD_ISSET(hSocket, &fdset)) {//判断目标套接字是否还在条件队列中
		return TRUE;
	}
	return FALSE;
}