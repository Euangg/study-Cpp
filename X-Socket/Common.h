#pragma once
#include<iostream>
#include<thread>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define MAX_IP_LEN 16

BOOL WinSockInit();
void WinSockUnLoad();