#include<iostream>
using namespace std;

//赋值运算表达式的返回值
void test1() {
	int a = 0;
	cout << (a = 5) << endl;

	bool b;
	cout << (b = 5) << endl;
	cout << (b = false) << endl;


	double d = 9.348535763;
	cout << (d = 3.141592653) << endl;
	//赋值什么表达式返回什么
}

//连续赋值操作
void test2() {
	int a = 0;
	int b = 0;
	int c = 0;
	a = b = c = 5;
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
}

int main() {
	test2();
}