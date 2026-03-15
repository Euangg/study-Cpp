//public:
//	基类public-public
//	基类protected-protected
//	基类private-不可见（就像没有一样）


//protected:
//	基类public-protected
//	基类protected-protected
//	基类private-不可见（就像没有一样）


//private:
//	基类public-private
//	基类protected-private
//	基类private-不可见（就像没有一样）


//private和protected会导致继承关系变复杂，在实际开发中，一般使用public


#include<iostream>
using namespace std;


//在派生类中，可以通过调用基类的公有成员函数间接访问基类的私有成员

class A {
private:
	int m_a = 10;
protected:
	int m_p = 22;

public:
	int m_b = 20;
	void func() { m_a = 11; cout << "m_a=" << m_a << endl; }
};


class B :public A {
	//使用using关键字可以改变基类成员在派生类中的访问权限
	//	注：using只能改变基类中public和protected成员的访问权限，因为基类中的private成员在派生类中不可见
public:
	using A::m_p;	//把m_p的权限改为公有
private:
	using A::m_b;	//把m_a的权限改为私有

};

int main() {
	B b;
	//b.m_a = 11;
	b.func();
	//b.m_b = 11;
	b.m_p = 220;
}