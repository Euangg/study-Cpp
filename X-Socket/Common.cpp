#include"Common.h"

BOOL WinSockInit() {
	WSADATA wsaData = { 0 };
	cout << "WSA准备初始化..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == NO_ERROR) {
		cout << "WSA初始化成功" << endl;
		return TRUE;
	}
	return FALSE;
}

void WinSockUnLoad() {
	WSACleanup();
}

