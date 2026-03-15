//  例：[]            (const int& no)             ->void{cout<<"this is no."<<no<<endl;};
//语法：[capture list](parameters)mutable noexcept->return type{statement}
//		   捕获列表     参数列表      函数选项       返回类型    函数体

//返回类型如果不填，编译器会根据函数体中的代码推断出来（省略->return type）
//	如果有返回类型，最好显式指定，自动推断可能与预期不同

#include<iostream>
using namespace std;
int main() {

	auto f = []() {
		cout << "hello world" << endl;
		return 8;
	};// 可以自动推导返回值类型

	auto f2 = []()->double {
		cout << "hello world" << endl;
		return 5;
	};//显式指明返回值类型

}