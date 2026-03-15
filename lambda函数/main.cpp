//lambda函数，C++11标准新增，语法糖，也称为lambda表达式或匿名函数
//  例：[]            (const int& no)             ->void{cout<<"this is no."<<no<<endl;};
//语法：[capture list](parameters)mutable noexcept->return type{statement}
//		   捕获列表     参数列表      函数选项       返回类型    函数体

#include<iostream>
using namespace std;
//普通函数
void zsshow() {cout << "hello world——普通函数" << endl;}
int main() {
	zsshow();	//普通函数

	auto f = []() {cout << "hello world——匿名函数" << endl;};	//匿名函数的定义，赋予一个名称，供后续调用
	f();		//匿名函数

	auto f = [] {};//最简单的匿名函数，无参无返
}

//与普通函数相比：
//距离近：可以写在要用函数的地方的附近
//直接：直接展示功能，没有声明与定义区分的说法