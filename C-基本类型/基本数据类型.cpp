#include<iostream>
using namespace std;


void pro_bool() {
	bool b1{ true }, b2{ false };
	cout << b1 << "," << b2 << endl;//1,0
	cout << sizeof(b1) << endl;//1

	auto temp = b1 + b2;//可以进行算术运算，返回值为int
	cout << b1 + b2 + b1 << endl;//2

	bool b3 = 99, b4 = 0;//非0转换为true(1)
	cout << b3 << "," << b4 << endl;//1,0//赋值会被归回01
}

int main() {
	pro_bool();
}