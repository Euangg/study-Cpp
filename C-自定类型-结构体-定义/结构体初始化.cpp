#include<iostream>
using namespace std;

struct MyStruct{
	int a{9};
	int b;
	char c{'d'};
	short d{55};
	int e;
};

//={0}的效果
void test1() {
	MyStruct s = { 1 };//只影响第一个值
	cout << s.a << endl;
}
//={}的效果
void test2() {
	MyStruct s = {};//全部使用默认值，如果没设就是0
	cout << s.a << endl;
}

//子级={}的效果
void test3() {
	MyStruct s = { {},6 };
	cout << s.a << endl;//0，会使用0
}


int main() {
	test3();
}