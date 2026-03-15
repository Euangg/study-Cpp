//自动推导的思想是函数模板和类模板的基础

//C语言和C++98中，auto关键字用于修饰变量（自动存储的局部变量）
//在C++11中，赋予了auto全新的含义，不再用于修饰变量，
//而是作为一个类型指示符，指示编译器在编译时推导 auto声明的变量 的数据类型（在Linux平台下，编译需要加-std=c++11参数）

//注：
//1).auto声明的变量必须在定义时初始化————如果没有初始值，拿什么来推导？
//2).初始化的右值可以是具体数值，也可以是表达式和函数的返回值
//3).auto不能作为函数的形参类型
//4).auto不能直接声明数组
//5).auto不能定义类的非静态成员变量（静态成员变量在全局区有强制初始化）

//不要滥用auto，auto在编程时的真正作用如下：
//1).代替冗长复杂的变量声明
//2).在模板中，用于声明依赖模板参数的变量
//3).函数模板依赖模板参数的返回值
//4).lambda表达式



#include<iostream>
using namespace std;

double func(int a, double b, const char* c, float d, short e, long f) {
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
	cout << "d=" << d << endl;
	cout << "e=" << e << endl;
	cout << "f=" << f << endl;
	return 5.5;
}

int main() {
	//声明并初始化变量的时候，如果不指明数据类型，使用auto关键字，编译器会根据赋值的数据类型推导该变量的类型
	auto a = 3;
	auto* pa = &a;
	auto pa2 = &a;
	cout << "a=" << a << endl;
	auto b = 7.213123;
	cout << "b=" << b << endl;
	auto c = "asdfasdf";
	cout << "c=" << c << endl;
	//以上都是对auto的滥用，实际操作时勿如此操作

	//注.1)
	double (*pf)(int a, double b, const char* c, float d, short e, long f);//声明函数指针pf
	pf = func;
	pf(1, 2.32323, "sdasd", 2.5, 32, 86778678678);

	auto pf1 = func;//编译器自动推导函数指针
	pf1(123, 123123.123, "hello", 555.66, 123, 769678967896);
	//如果修改了函数定义的参数（类型，数量，顺序），这里也会自动推导！（而上面也要跟着修改参数表）

}