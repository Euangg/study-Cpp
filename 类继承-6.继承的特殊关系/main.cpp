//派生类和基类之间有一些特殊关系（其他类是没有的）
//可以把派生类对象赋值给基类对象，但是会舍弃非基类成员————可以用派生类构造基类
//    如果函数的形参是基类，实参可以是派生类
//    ————本质上是调用基类的赋值函数
//基类指针可以在不进行显式转换的情况下指向派生类对象
//基类引用可以在不进行显式转换的情况下引用派生类对象

//注：
//基类指针只能调用基类的方法，不能调用派生类的方法
//C++要求指针和引用与赋值的类型匹配，这一规则对继承来说是个例外
//   但是这个例外是单向的，只能基类指针指向派生类，派生类指针不能指向基类

#include<iostream>
using namespace std;

class A {
public:
	int m_a = 0;
private:
	int m_b = 0;
public:
	void show() { cout << "A::show(): m_a=" << m_a << ",m_b=" << m_b << endl; };
	void setb(int b) { m_b = b; };
};

class B :public A {
public:
	int m_c = 0;
	void show() { cout << "B::show(): m_a=" << m_a << ",m_c=" << m_c << endl; };

};


int main() {

	A a;
	B b;

	b.m_a = 10;
	b.setb(20);
	b.m_c = 30;

	a.show();
	a = b;
	a.show();
	

	A* pa = &b;
	pa->show();//调用的是A类的show函数
}
