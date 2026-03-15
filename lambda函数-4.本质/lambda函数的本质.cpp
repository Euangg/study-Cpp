//只有无捕获的lambda才能用作函数指针（隐式转换为函数指针）


//lambda的本质，是【函数对象】，是【类】的实例
//捕获列表-成员变量
//()调用-重载()运算符

#include<iostream>
using namespace std;

typedef void(*Func)();

struct MyStruct {
	void operator()() {cout << "hello world——重载()运算符" << endl;}
};

struct MyStruct2 {
	static void f() { cout << "hello world——静态成员函数" << endl; }
};

int main() {
	Func f;
	MyStruct func;
	//Func = MyFunction::operator();不是静态函数，重载运算符不能是静态，不行
	//Func = func();实例化后就是闭包对象，不行
	//Func = func.operator();//更不行

	MyStruct2 func2;
	f = MyStruct2::f;//静态成员函数，类名访问
	f = func2.f;//静态成员函数，实例访问

	//无捕获的lambda
	auto l = []() {};
	f = l;
	f = []() {};
	//特性：可以隐式转换为函数指针，就像是重载()是静态的（本质上不是，是编译器提供的转换）
}