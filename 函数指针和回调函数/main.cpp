//函数的二进制代码存放在内存四区中的代码段
//函数的地址是它在内存中的起始地址
//把函数的地址作为参数传递给函数，就可以在函数中灵活调用其他的函数

//函数指针：使用步骤
//1.声明函数指针
//	声明普通指针时，必须提供指针类型。同样，声明函数指针时，也必须提供函数类型，函数的类型是指返回值和参数列表（函数名和形参名不是）
//2.让函数指针指向函数地址
//3.通过函数指针调用函数


#include<iostream>
using namespace std;

void func(int no, string str) {
	cout << "No." << no << " : " << str << endl;
}
void func2(int no, string str) {
}

//回调函数
void zs(int a) {
	cout << "sz函数个性化处理" << endl;
}

void ls(int a) {
	cout << "ls函数个性化处理" << endl;
}

//调用者函数（参数为回调函数）
//只约定回调函数的种类，不关心回调函数的功能
void show(void (*pf)(int)){
	cout << "通用初始化部分" << endl;
	int b = 3;//回调函数传参
	//个性化处理
	pf(b);

	cout << "通用释放" << endl;
}

int main() {
	int bh = 7;
	string name = "RedWolf";

	func(bh, name);//普通调用函数的方法

	void (*pfunc)(int, string);	//1.声明函数指针
	pfunc = func;				//2.对函数指针赋值，语法为函数指针名=函数名
	pfunc(bh, name);			//3.函数指针名调用函数   C++
	(*pfunc)(bh, name);			//3.函数指针名调用函数   C

	//
	cout << "func:" << func << endl;
	cout << "&func:" << &func << endl;
	cout << "*func:" << *func << endl;//同一种东西
	//func = func2;
	//&func = func2;
	//*func = func2;//不可修改

	//函数回调
	//回调函数是把一个函数的代码嵌入到另一个函数中
	show(zs);	//个性化1
	show(ls);	//个性化2

	return 0;
}
