#include<iostream>
using namespace std;

//在C和C++中，用0或NULL都可以表示空指针
//声明指针后，在赋值之前，让它指向空，表示没有指向任何地址

//使用空指针的后果：
//1.如果对空指针解引用，程序会崩溃

//注：
//如果对空指针使用delete运算符，系统将忽略该操作，不会出现异常。所以，内存释放后，也应该把指针指向空


void func(int* no, string* str) {
	if (no == 0 || str == 0)return;//在函数中，应该有判断形参是否为空指针的代码，目的是保证程序的健壮性

	cout << "hello" << *no << ":" << str << endl;
}
void test1() {
	int* p = 0;//用0或NULL都可以表示空指针

	cout << "p=" << p << endl;//0000 0000
	//cout << "*p=" << *p << endl;//1.如果对空指针解引用，程序会崩溃
	delete p;
	cout << "delete ok" << endl; //如果对空指针使用delete运算符，系统将忽略该操作，不会出现异常。所以，内存释放后，也应该把指针指向空

	int* bh = 0;// new int(3);
	string* message = 0;// new string("it's ok!");

	func(bh, message);

	delete bh;
	delete message;

	int* pn = nullptr;
	cout << "pn=" << pn << endl;//0000 0000
}
//delete后指针的值
void test2() {
	int* p = new int(10);
	cout << "p=" << p << endl;
	delete p;
	cout << "已delete p" << endl;
	cout << "p=" << p << endl;//0000 8123（野指针了，与之前的值还不一样）
	//delete p;//再次delete会异常
	
}

//C++11的nullptr
//用0和NULL表示空指针会产生歧义，C++11建议用nullptr表示空指针，也就是(void*)0
//NULL在C++中就是0
//建议用nullptr代表空指针，而NULL就当作0使用
//关于NULL和nullptr的区别
void funcc(char* p) { cout << "void func(char* p)" << endl; };
void funcc(int p) { cout << "void funcc(int p)" << endl; }
void test3() {
	funcc(10);
	funcc(NULL);//NULL默认会被当作int，NULL就是宏替换0
	funcc(nullptr);//nullptr会被当作指针，(void*)0
}

void main() {
	test2();
	//test3();
}