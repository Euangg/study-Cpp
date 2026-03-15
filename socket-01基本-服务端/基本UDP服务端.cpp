#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#include<iostream>
using std::cout;
using std::endl;

int main() {
	//1.初始化套接字通信WSAStartup
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		cout << "WSAStartup失败" << endl;
		return -1;
	}

	//2.创建socket
	SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "socket失败" << endl;
		WSACleanup();
		return -1;
	}

	//3.绑定地址和端口
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(8080);
	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		cout << "bind失败" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	//4.监听连接
	//if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
	//	cout << "listen失败" <<WSAGetLastError()<< endl;
	//	closesocket(serverSocket);
	//	WSACleanup();
	//	return -1;
	//}

	//5.接受客户端连接
	//sockaddr_in clientAddr;
	//int sizeClientAddr = sizeof(clientAddr);
	//SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &sizeClientAddr);
	//if (clientSocket == INVALID_SOCKET) {
	//	cout << "accept失败" << endl;
	//	closesocket(serverSocket);
	//	WSACleanup();
	//	return -1;
	//}

	//6.收发数据
	char buffer[1024];
	sockaddr_in clientAddr;
	int sizeClientAddr = sizeof(clientAddr);
	while (1) {
		int retRecv = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (sockaddr*)&clientAddr, &sizeClientAddr);

		if (retRecv == SOCKET_ERROR) {
			cout << "recv失败" << endl;
			closesocket(serverSocket);
			WSACleanup();
			return -1;
		}
		else {
			char clientIP[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
			cout << clientIP << ":" << buffer << endl;
			//响应
			const char* content = "Hello from server";
			int sizeContent = strlen(content);
			sendto(serverSocket, content, sizeContent, 0, (sockaddr*)&clientAddr, sizeClientAddr);
		}

	}


	//7.关闭连接
	closesocket(serverSocket);
	WSACleanup();
}