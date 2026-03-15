#pragma once
#include<list>
using namespace std;

#include"Common.h"

//自定义协议头
class CMsgHead {
public:
	char m_type;
	UINT m_cntLen;//协议体的长度

	CMsgHead() {
		m_type = -1;
		m_cntLen = 0;
	}
	CMsgHead(char nType) {
		m_type = nType;
		m_cntLen = 0;
	}
	CMsgHead(char nType, UINT cntLen) {
		m_type = nType;
		m_cntLen = cntLen;
	}
};


class CClientItem {
public:
	SOCKET m_Socket;
	TCHAR m_szIpAddr[MAX_IP_LEN];
	HANDLE m_hThread;

	CClientItem() {
		m_Socket = INVALID_SOCKET;
		ZeroMemory(m_szIpAddr, MAX_IP_LEN);
		m_hThread = NULL;
	}
	bool operator==(const CClientItem& client)const {
		if (this->m_Socket != client.m_Socket)return false;
		if (wcscmp(this->m_szIpAddr, client.m_szIpAddr) != 0)return false;
		return true;
	}
};

class CServer {
public:
	UINT m_nPort;
	SOCKET m_ListenSock;
	list<CClientItem*>m_ClientList;

public:
	static UINT acceptProc(LPVOID pParam);
	static DWORD WINAPI ClientThreadProc(LPVOID pParam);
	
	CServer();
	BOOL StartServer(UINT nPort);
	void RemoveTargetClient(CClientItem* pItem);
	BOOL ProcessMsg(CMsgHead& msg, TCHAR* pCnt, CClientItem* pClient);

};




CServer* GetServer();