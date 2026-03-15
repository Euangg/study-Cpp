#include<iostream>
using namespace std;

template<float i>
void Test() {
	float a = 0;
	a += i;
	cout << a << endl;
}
//要C++20才能支持浮点类型作为非类型模板参数

int main() {
	float x = 9.9f;
	x += 88;
	//Test<x>();//错误
	Test<9.9>();
}
//保证在编译期能推导出来，而非运行期