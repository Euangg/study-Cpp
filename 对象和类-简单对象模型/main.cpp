#include<iostream>
#include<stdio.h>
using namespace std;

class CGirl {
public:
	int m_bh;
	char m_name[3];//内存对齐（所占空间大小为4的倍数）
	static int m_age;//静态成员不占用具体对象的内存，静态成员变量属于类，不属于对象

	//默认构造函数
	CGirl() { memset(m_name, 0, sizeof(m_name)); m_age = 0; }
	//默认析构函数
	~CGirl() {};

	void showname() { cout << "姓名" << m_name << endl; };
	void showname2() { cout << "姓名" << "dream" << endl; };

	void showage() { cout << "年龄" << m_age << endl; };
};

int CGirl::m_age = 10;
int aaa;//全局变量与静态成员变量在一起（全局区）
void func() {};//普通函数与成员函数在一起（代码段）

int main() {
	CGirl g;
	cout << "对象g占用内存大小是：" << sizeof(g) << endl;
	cout << "对象g的地址是：" << &g << endl;
	cout << "成员变量m_bh的地址是：" << &g.m_bh << endl;
	cout << "成员变量m_name的地址是：" << &g.m_name << endl;
	cout << "成员变量m_age的地址是：" << &g.m_age << endl;
	cout << "全局变量aaa的地址是：" << &aaa << endl;

	printf("成员函数showname的地址是：%p\n", &CGirl::showname);
	printf("成员函数showage的地址是：%p\n", &CGirl::showage);
	printf("函数func的地址是：%p\n", &func);

	CGirl* g1 = nullptr;
	g1->showname2();//用为空的类对象指针变量可以正常调用没有用到this指针的非静态成员函数

}