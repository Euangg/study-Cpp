
#include<iostream>
using namespace std;


struct MyStruct {
	int a = 0;
	//MyStruct() { cout << "call 无参构造" << endl; }
};


int main() {

	MyStruct m;
	MyStruct m2{};
	MyStruct m3{ 6 };//统一初始化列表会看构造函数
}