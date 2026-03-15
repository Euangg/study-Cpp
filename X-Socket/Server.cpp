#include"Server.h"
#include<atlstr.h>



BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut = 100, BOOL bRead = FALSE) {
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut > 1000 ? 1000 : nTimeOut;
	tv.tv_sec = 0;
	tv.tv_usec = nTimeOut;

	int iRet = 0;
	if (bRead) {
		iRet = select(0, &fdset, NULL, NULL, &tv);
	}
	else {
		iRet = select(0, NULL, &fdset, NULL, &tv);
	}
	if (iRet <= 0) {
		return FALSE;
	}
	else if (FD_ISSET(hSocket, &fdset)) {
		return TRUE;
	}
	return FALSE;
}

int SendData(SOCKET sock,char* buf,unsigned int len) {
	unsigned int offset = 0;
	while (offset < len) {
		int nSend = send(sock, buf + offset, len - offset, 0);
		//参数：1.通信套接字
		//2.缓冲区（待发送的数据存放的位置）
		//3.缓冲区大小
		//4.保留

		if (nSend == SOCKET_ERROR)return -1;
		if (nSend == 0)return 0;
		offset += nSend;
		//分多次发送
	}
	return 1;
}

int RecvData(SOCKET sock, char* buf, unsigned int len) {
	unsigned int offset = 0;
	while (offset < len) {
		int nRecv = recv(sock, buf + offset, len - offset, 0);
		//参数：1.通信套接字
		//2._out_ 缓冲区（接收的数据存放的位置）
		//3.缓冲区大小
		//4.保留值，置0即可
		//返回值：无错误发生，返回接收了多少字节的数据
		//						若为0表示连接中断
		//		发生错误，返回SOCKET_ERROR

		if (nRecv == SOCKET_ERROR)return -1;
		if (nRecv == 0)return 0;
		offset += nRecv;
		//分多次接收
	}
	return 1;
}

CServer* GetServer() {
	static CServer* pGServer = NULL;
	if (!pGServer) {
		pGServer = new CServer();
	}
	return pGServer;
}

CServer::CServer() {
	m_nPort = 0;
	m_ListenSock = INVALID_SOCKET;
}

BOOL CServer::StartServer(UINT nPort) {
	cout << "启动服务端" << endl;
	m_nPort = nPort;
	thread myThread(acceptProc, this);
	myThread.join();
	return TRUE;
}
void CServer::RemoveTargetClient(CClientItem* pItem) {
	if (!pItem)return;
	
	//在链表中删除该元素
	m_ClientList.remove(pItem);

	closesocket(pItem->m_Socket);
	CloseHandle(pItem->m_hThread);
	delete pItem;
}

BOOL CServer::ProcessMsg(CMsgHead& msg, TCHAR* pCnt, CClientItem* pClient) {
	switch (msg.m_type)
	{
	//case MSG_TYPE_LOGIN:
	//	break;
	default:
		break;
	}

	return TRUE;
}

UINT CServer::acceptProc(LPVOID pParam) {
	CServer* pThis = (CServer*)pParam;//静态成员函数没有this指针
	cout << "服务端副线程启动" << endl;
	pThis->m_ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//参数：1.int af 指明地址描述方式，可填：AF_INET(2)——IPv4
	//2.int type 套接字类型 SOCK_STREAM(1)：流式套接字  SOCK_DGRAM(2)：数据报套接字
	//3.int protocol 协议类型 IPPROTO_TCP(6)：TCP  IPPROTO_UDP(17)：UDP  
	//返回值：成功 返回创建的socket，失败 返回INVALID_SOCKET
	cout << "完成socket" << endl;
	if (pThis->m_ListenSock == INVALID_SOCKET) {
		cout << "创建监听SOCKET失败！" << endl;
		return FALSE;
	}


	cout << "服务端副线程绑定端口..." << endl;
	sockaddr_in sServer = { 0 };
	sServer.sin_family = AF_INET;
	sServer.sin_addr.s_addr = htonl(INADDR_ANY);//绑定本机所有可得到的IP
	//sServer.sin_addr.s_addr = inet_addr("127.0.0.1");//绑定指定IP
	sServer.sin_port = htons(pThis->m_nPort);
	if (bind(pThis->m_ListenSock, (sockaddr*)&sServer, sizeof(sServer)) == SOCKET_ERROR) {
		//参数：1.套接字句柄
		//2.要关联的本地地址
		//3.地址的长度
		cout << "绑定监听SOCKET到指定端口失败！" << endl;
		return FALSE;
	}
	cout << "服务端副线程绑定端口成功！" << endl;
	cout << "服务端副线程设置监听..." << endl;
	if (listen(pThis->m_ListenSock, SOMAXCONN) == SOCKET_ERROR) {
		//参数：1.套接字句柄
		//2.int backlog：监听队列中允许保持的尚未处理的最大连接数量，SOMAXCONN 最大值
		cout << "端口监听失败！" << endl;
		return FALSE;
	}
	cout << "服务端副线程开始监听" << endl;
	while (TRUE) {
		sockaddr_in clientAddr = { 0 };
		int iLen = sizeof(sockaddr_in);
		cout << "等待连接..." << endl;
		SOCKET accSock = accept(pThis->m_ListenSock, (sockaddr*)&clientAddr, &iLen);
		//参数：1.套接字句柄
		//2.sockaddr* addr：一个指向sockaddr_in结构的指针，用于取得对方的地址信息
		//3.一个指向地址长度的指针
		//返回值：成功 返回服务端与客户端通信的一个新的SOCKET，这个SOCKET用于后来与客户端通信
		// 失败 返回INVALID_SOCKET
		// 该函数会阻塞在此，直到有客户端连接才会继续往下执行
		//accSock与监听SOCKET无关，监听SOCKET只负责监听，不负责通信
		cout << "收到一个连接" << clientAddr.sin_addr.S_un.S_addr << ":" << clientAddr.sin_port << endl;
		CClientItem* pItem = new CClientItem();
		pItem->m_Socket = accSock;
		CString strIp;
		strIp = inet_ntoa(clientAddr.sin_addr);
		_tcscpy_s(pItem->m_szIpAddr, MAX_IP_LEN, strIp);
		pThis->m_ClientList.push_back(pItem);

		pItem->m_hThread = CreateThread(NULL, 0, ClientThreadProc, pItem, 0, NULL);
		

		if (accSock == INVALID_SOCKET)continue;
	}


	return TRUE;
}



DWORD CServer::ClientThreadProc(LPVOID pParam) {
	CClientItem* pClient = (CClientItem*)pParam;
	while (TRUE) {
		if (SOCKET_Select(pClient->m_Socket)) {//检查客户端通信套接字是否有信号响应
			CMsgHead msg;//首次接收，先接收协议头
			int iRet = RecvData(pClient->m_Socket, (char*)&msg, sizeof(msg));
			if (iRet <= 0) {
				cout << "传输异常，清除客户端..." << endl;
				//清除客户端
				GetServer()->RemoveTargetClient(pClient);
				return FALSE;
			}
			//recv ok成功接收到协议头
			TCHAR* pszBuf = new TCHAR[msg.m_cntLen];//根据协议头申请用于接收协议体的内存空间
			ZeroMemory(pszBuf, msg.m_cntLen);
			iRet = RecvData(pClient->m_Socket, (char*)pszBuf, msg.m_cntLen);
			if (iRet <= 0) {
				delete[] pszBuf;
				//清除客户端
				GetServer()->RemoveTargetClient(pClient);
			}
			//处理信息

			delete[] pszBuf;
		}
	}
	return TRUE;
}