#include<iostream>
using namespace std;

#include"../Windows-dll-07动态库封装变量/dll变量.h"
//#pragma comment(lib,"../Debug/Windows-dll-07动态库封装变量.lib")
#pragma comment(lib,"../Release/Windows-dll-07动态库封装变量.lib")

#include"../Windows-dll-09dll菱形调用(1)/dll菱形调用1.h"
//#pragma comment(lib,"../Debug/Windows-dll-07动态库封装变量.lib")
#pragma comment(lib,"../Release/Windows-dll-09dll菱形调用(1).lib")

#include"../Windows-dll-09dll菱形调用(2)/dll菱形调用2.h"
//#pragma comment(lib,"../Debug/Windows-dll-07动态库封装变量.lib")
#pragma comment(lib,"../Release/Windows-dll-09dll菱形调用(2).lib")



int main() {
	AddVar1();
	AddVar2();

	a++;
	cout << "文件自处理a" << endl;
	cout << a << endl;
}