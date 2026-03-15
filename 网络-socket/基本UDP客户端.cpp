//运行在计算机中的两个程序通过socket建立起一个通道，数据在通道中传输
//socket把复杂的TCP/IP协议族隐藏了起来，对程序员来说，只要用好socket相关的函数，就可以完成网络通信

//socket的类型：
//流式socket，TCP，可靠连接
//数据报socket，UDP，无连接
//原始socket

//socket的组成：
//IP地址
//端口号

//TCP socket的工作流程：
//服务端：创建socket——绑定IP和端口——监听连接——接受连接——收发数据——关闭连接
//客户端：创建socket——连接服务端——收发数据——关闭连接

//UDP socket的工作流程：
//服务端：创建socket——绑定IP和端口——收发数据——关闭连接
//客户端：创建socket——指定服务端——收发数据——关闭连接

#include<WinSock2.h>//WinSock核心头文件
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")//WinSock库

#include<iostream>
using std::cout;
using std::endl;

int main() {
	//1.初始化套接字通信WSAStartup
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) { 
		//参数：1.WinSock版本号
		//返回：成功返回0（NO_ERROR）
		cout << "WSAStartup失败" << endl;
		return -1; 
	}

	//2.创建socket
	SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//参数：1.指明地址描述方式，可填：AF_INET(2)——IPv4
	//		2.套接字类型，可填：SOCK_STREAM(1)——流式套接字、SOCK_DGRAM(2)——数据报套接字
	//		3.协议类型，可填：IPPROTO_TCP(6)——TCP、IPPROTO_UDP(17)——UDP
	//返回：成功返回套接字，失败返回INVALID_SOCKET
	if (clientSocket == INVALID_SOCKET) {
		cout << "socket失败" << endl;
		WSACleanup();
		return -1;
	}

	//3.指定服务端
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	//if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
	//	cout << "connect失败" << endl;
	//	closesocket(clientSocket);
	//	WSACleanup();
	//	return -1;
	//}

	//4.收发数据
	const char* content = "Hello from client";
	int sizeContent = strlen(content);
	int byteSent = sendto(clientSocket, content, sizeContent, 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
	//send
	//参数：1.通信套接字
	//		2.存放数据的缓冲区
	//		3.缓冲区大小
	//		4.控制发送行为的标志，通常置0
	//返回：成功，返回不为负，表示发送了多少字节的数据
	//		0表示连接中断
	//		错误，返回SOCKET_ERROR(-1)
	if (byteSent == SOCKET_ERROR) {
		cout << "sendto失败" << endl;
		closesocket(clientSocket);
		WSACleanup();
		return -1;
	}
	if (byteSent != sizeContent) {
		cout << "发送不对齐:" << sizeContent << "中" << byteSent << endl;
	}
	else {
		cout << "成功发送:" << byteSent << "bytes" << endl;
	}

	char buffer[1024];
	sockaddr_in fromAddr;
	int sizeFromAddr=sizeof(fromAddr);
	while (1) {
		int retRecv =recvfrom(clientSocket, buffer, sizeof(buffer), 0,(sockaddr*)&fromAddr,&sizeFromAddr);
		//recv
		//参数：1.通信套接字
		//		2.存放数据的缓冲区
		//		3.缓冲区大小（指明最多接收多少数据，多了不再接收）
		//		4.保留值，置0
		//返回：无错误发生，返回不为负，表示接收了多少字节的数据
		//		0表示连接中断
		//		错误，返回SOCKET_ERROR(-1)
		if (retRecv == SOCKET_ERROR) {
			cout << "recv失败" << endl;
			closesocket(clientSocket);
			WSACleanup();
			return -1;
		}
		else {
			cout << buffer << endl;
		}
		if (GetAsyncKeyState(VK_ESCAPE))break;
	}

	//5.关闭连接
	closesocket(clientSocket);
	WSACleanup();
}