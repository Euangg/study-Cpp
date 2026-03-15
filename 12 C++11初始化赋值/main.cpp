#include<iostream>
using namespace std;


int main() {
	int a = 10;
	int b = (10);
	int c(10);

	//C++11标准，统一初始化列表————提高效率
	int e = { 10 };
	int f{ 10 };
	//注：在Linux平台下，如果采用C++11标准，编译需要加-std=c++11参数


	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
	cout << "e=" << e << endl;
	cout << "f=" << f << endl;


	return 0;
}