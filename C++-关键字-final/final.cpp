//限制某个类不能被继承
//限制某个虚函数不能被重写

#include<iostream>
using namespace std;

class Base final {};
//class Child : public Base {};//final类型不能用作基类

class Base2 {
public:
	virtual void test() {cout << "Base class ..." << endl;}
};
class Child :public Base2 {
public:
	void test()override final { cout << "Child class ..." << endl; };//这里是最后一次重写
};
class Grandson :public Child {
public:
	//void test()override {};//无法重写final函数
};