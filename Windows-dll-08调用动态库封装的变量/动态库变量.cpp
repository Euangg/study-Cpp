#include<iostream>
using namespace std;
#include"../Windows-dll-07动态库封装变量/dll变量.h"
//#pragma comment(lib,"../Debug/Windows-dll-07动态库封装变量.lib")
#pragma comment(lib,"../Release/Windows-dll-07动态库封装变量.lib")

int main() {
	cout << a << endl;
	a++;
	cout << a << endl;

	int b;
	cin >> b;
}