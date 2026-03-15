#include<iostream>
using namespace std;

struct MyStruct {
	int a = 0;
}s, * ps{ &s };

struct {
	int a = 99;
}no_name;//不指定类型的结构体

int main() {
	cout << s.a << endl;
	cout << ps->a << endl;

	cout << no_name.a << endl;
}