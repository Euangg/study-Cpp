

#include<iostream>
using namespace std;
void func(int& i) { cout << "L参数为左值：" << i << endl; };
void func(int&& i) { cout << "R参数为右值：" << i << endl; };

void func2(int i) { func(i); };//传值，必为左值
void func3(int& i) { func(i); };//传左引用，要求为左值
void func4(int&& i) { func(i); };//传右引用，要求为右值
//多级函数传引用参，如何保持参数的左右性？

//苯方法
void func5(int& i) { func(i); };//传左值
void func5(int&& i) { func(move(i)); };//传右值，参数变成右值引用（左值），再move成右值

//正解
template<typename TT>
void func6(TT&& i) {
	func(forward<TT>(i));
}

int main() {
	int i = 9;
	func(i);
	func(9);


	func2(i);
	func2(9);

	cout << "多级传引用参，参数保持左右性的问题：" << endl;
	func3(i);
	//func3(9);报错，要求左值

	//func4(i);报错，要求右值
	func4(9);

	cout << "解决方法1：" << endl;
	func5(i);
	func5(99); 
	cout << "解决方法2：" << endl;
	func6(i);
	func6(999);
}