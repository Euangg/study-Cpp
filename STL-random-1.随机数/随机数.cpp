#include<random>
#include<iostream>
using std::cout;
using std::endl;

//真·纯随机
void test1() {
	std::random_device rd;
	cout << rd.entropy() << endl;
	cout << rd.min() << "," << rd.max() << endl << endl;
	for (int i = 0; i < 10; ++i)cout << rd() << endl;//纯随机数
}

//伪随机
void test2() {
	std::mt19937 rd;
	cout << rd.min() << "," << rd.max() << endl << endl;
	for (int i = 0; i < 10; ++i)cout << rd() << endl;//伪随机数，每次都一样
}

//mt19937重设种子
void test3() {
	std::mt19937 rd(0);
	for (int i = 0; i < 10; ++i)cout << rd() << endl;//
	cout << endl;
	std::mt19937 rd2(8888);
	for (int i = 0; i < 10; ++i)cout << rd2() << endl;//
	cout << endl;
	rd2.seed(0);
	for (int i = 0; i < 10; ++i)cout << rd2() << endl;//
}

int main() {
	//test1();
	//test2();
	test3();
}