//对于内置类型，如果两种数据类型是兼容的，C++可以自动转换
//如果从更大的数转换为更小的数，可能会被截断或损失精度
//long count=8;		//int转换为long
//double time=11;	//int转换为double
//int side=3.33;	//double转换为int的3

//C++不自动转换不兼容的类型，下面的语句是非法的：
//int* ptr=8;
//不能自动转换时，可以使用强制类型转换
//int* p=(int*)8;



//把某种数据类型转换为类的类型
#include<iostream>
using namespace std;


//仿照stl的string类做一个自己的字符串类
class mystring {
public:
	char* ptr;
	int num;
public:
	mystring() { ptr = nullptr; };
	mystring(const char pchar[]) { ptr = (char*)pchar; };//一个参数的构造函数，还有另一种身份——转换函数，允许把指定数据类型在需要时可以转换为类类型
	mystring(int n) { num = n; };
};

int main() {
	string cppstr = "hello world";
	//在C++中，将一个参数的构造函数用作自动类型转换的函数，它是自动进行的，不需要进行显式的转换
	//string是一种类的类型，而"hello world"是const char[12]，是一种数据类型

	mystring mystr = "sda";
	cout << "mystr.ptr:" << mystr.ptr << endl;

	//以下是转换函数发生作用的几种情况
	mystring mystr2(99999);
	mystring mystr3 = 9999;
	mystr3 = 6666666666888;//会先调用mystring(6666666666888)创建临时对象，再赋值给mystr3（提醒：不是拷贝）
}

//复习函数重载关于const修饰的问题——不算重载
//函数传数组，到底怎么传？————