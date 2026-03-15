//继承构造函数
//一个类的构造函数可以调用父类的构造函数
#include<iostream>
using namespace std;
class Base {
public:
	Base(int i) :m_i(i) {};
	Base(int i, double j) :m_i(i), m_j(j) {};
	Base(int i, double j, string k) :m_i(i), m_j(j), m_k(k) {};

	int m_i;
	double m_j;
	string m_k;
	void func(int i) {
		cout << "num:" << i << endl;
	}
};

class Child :public Base {
public:
	using Base::Base;//继承父类的构造函数
	using Base::func;//4.使被隐藏的父类在子类重新显现


	void func() {//1.函数与父类同名会隐藏父类同名函数
		cout << "hello!" << endl;
	}
};

int main() {
	Child c1(12);
	Child c2(12,8.8);
	Child c3(12, 9.01, "dsadj");

	c1.func();
	c1.func(1);//2.父类函数被隐藏，调用失败。5.使用using重现后可以正常调用
	c1.Base::func(1);//3.可以指定父类命名空间进行调用
}