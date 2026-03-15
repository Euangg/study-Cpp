//如果派生类中的成员（包括成员变量和成员函数）与基类中的成员重名，通过派生类对象或者在派生类的成员函数中使用该成员时，将使用派生类新增的，而不是基类的
//基类的成员函数和派生类的成员函数不会构成重载，如果派生类有同名函数，那么就会遮蔽基类中的所有同名函数


//类是一种作用域，每个类都有自己的作用域
//在类的作用域之外，普通成员通过对象访问，静态成员不仅可以通过对象访问，还可以通过类访问

//原理：当存在继承关系时，基类的作用域就嵌套在了派生类的作用域中。如果成员在派生类作用域中已经找到，就不会在基类作用域中继续查找；
//如果没有找到，则前往基类继续查找

#include<iostream>
using namespace std;

class A {
public:
	int m_a = 30;
	int m_b = 31;
	void func() { cout << "调用了A的func()函数\n"; };
	void func(int a) {
		cout << "调用了A的func(int a)函数\n";
		A::m_a = 99;//在成员函数内部的成员也可以加域解析符
	};
};

class B :public A {
public:
	int m_a = 80;
	void func() { cout << "调用了B的func()函数\n"; };//遮蔽基类中的所有同名函数（包括重载）
	void func1() {
		A::m_a = 9;
		m_a = 10;
		cout << A::m_a << "\t" << m_a << endl;//在成员前加基类域解析符可以访问被遮蔽的成员

	}
};

class C :public B {
public:
	int m_a=333;

	void func() {
		/*A::m_a = 999;
		cout << A::m_a << endl;*/
		B::A::m_a = 999;
		cout << B::A::m_a << endl;//规范写法，孙子先找爸爸再找爷爷

		B::m_a = 888;
		cout << B::m_a << endl;
		m_a = 777;
		cout << m_a << endl;
	}


};

int main() {
	B b;
	b.func();

	A a;
	a.A::m_b = 11;
	a.A::func();
	a.A::func(1);//成员前可以加域解析符

	b.A::func(12);//如果要调用被遮蔽的基类成员，可以通过在成员前加基类域解析符来指定
	b.func1();


	C c;
	c.func();
}