#define DLL_EXPORTS_USE2
#include"dll菱形调用2.h"

#include<iostream>
using namespace std;
#include"../Windows-dll-07动态库封装变量/dll变量.h"
//#pragma comment(lib,"../Debug/Windows-dll-07动态库封装变量.lib")
#pragma comment(lib,"../Release/Windows-dll-07动态库封装变量.lib")

void AddVar2() {
	a++;
	cout << "调用了AddVar2，a的值为" << endl;
	cout << a << endl;
}