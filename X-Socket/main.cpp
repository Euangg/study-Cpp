
#include"Common.h"
#include"Server.h"

int main() {
	if (WinSockInit()) {
		cout << "Winsock初始化成功" << endl;
	}
	GetServer()->StartServer(7777);

	WinSockUnLoad();
}