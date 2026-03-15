#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#include<iostream>
using namespace std;

int main() {
	//初始化WSA
	char ip[256] = { 0 };
	WSADATA wsaData;
	int iRet_startup = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet_startup == NO_ERROR) {
		//2.获取主机名
		char hostname[256];
		int iRet_gethostname = gethostname(hostname, sizeof(hostname));
		if (iRet_gethostname != SOCKET_ERROR) {
			cout << "主机名：" << hostname << endl;

			//3.获取主机ip
			HOSTENT* host = gethostbyname(hostname);
			if (host != NULL) {
				strcpy(ip, inet_ntoa(*(in_addr*)*(host->h_addr_list)));
				cout << ip << endl;
			}
		}
	}


	return 0;
}