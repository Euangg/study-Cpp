#define DLL_EXPORTS_USE1
#include"dll菱形调用1.h"

#include<iostream>
using namespace std;
#include"../Windows-dll-07动态库封装变量/dll变量.h"
//#pragma comment(lib,"../Debug/Windows-dll-07动态库封装变量.lib")
#pragma comment(lib,"../Release/Windows-dll-07动态库封装变量.lib")

void AddVar1() {
	a++;
	cout << "调用了AddVar1，a的值为" << endl;
	cout << a << endl;
}