//派生类构造函数的要点如下：
//1.创建派生类对象时，程序首先调用基类构造函数，然后调用派生类构造函数
//2.如果没以指定基类构造函数，将使用基类的默认构造函数
//3.可以用初始化列表指明要使用的基类构造函数
//4.基类构造函数负责初始化被继承的数据成员；派生类构造函数主要用于初始化新增的数据成员
//5.派生类的构造函数总是调用一个基类构造函数，包括拷贝构造函数


#include<iostream>
using namespace std;

class A {//基类
public:
	int m_a;
private:
	int m_b;
public:
	A() :m_a(0), m_b(0)//基类的默认构造函数
	{
		cout << "调用了基类的默认构造函数A()\n";
	}
	A(int a, int b) :m_a(a), m_b(b) //基类的有参构造函数
	{
		cout << "调用了基类的有参构造函数A(int a, int b)\n";

	}
	A(const A& a) :m_a(a.m_a + 1), m_b(a.m_b + 1) //基类的拷贝构造函数
	{
		cout << "调用了基类的拷贝构造函数A(const A& a)\n";
	}


	void showA() { cout << "m_a=" << m_a << ",m_b=" << m_b << endl; };

};

class B :public A {//派生类
public:
	int m_c;
	B() :m_c(0),A() {
		cout << "调用了派生类的默认构造函数B()\n";
	}

	B(int a, int b, int c) :A(a, b), m_c(c + 2) {//3.可以用初始化列表指明要使用的基类构造函数
		cout << "调用了派生类的有参构造函数B(int a, int b, int c)\n";
	}

	B(const A& a, int c) :A(a), m_c(c)//5.派生类的构造函数总是调用一个基类构造函数，包括拷贝构造函数
	{
		cout << "调用了派生类的有参构造函数B(const A& a, int c)\n";
	}

	void showB() { cout << "m_c=" << m_c << endl; }

};


int main() {
	B b1(3,4,5);
	b1.showA();
	b1.showB();

	B b2(A(3, 3), 3);
	b2.showA();
	b2.showB();

}