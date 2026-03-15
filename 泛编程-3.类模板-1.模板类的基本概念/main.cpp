//类模板===模板类   函数模板===模板函数

//类模板是通用类的描述，使用任意类型来描述类的定义。
//使用模板类的时候，指定具体的类型，让编译器生成该类型的定义

//语法：
//template<class T>
//class 类模板名 {
//	//类的定义
//};

//函数模板建议用typename描述通用数据类型，类模板建议用class

//注意；
//1).在创建对象的时候必须指明数据类型(必须显式指定，这点不同于模板函数)
//2).使用类模板时，数据类型必须适应类模板中的代码
//3).适应类模板时可以为通用数据类型指定缺省数据类型——————函数模板其实也可以，但是要C++11标准（其实对函数意义不大）
//4).模板类的成员函数可以在类外实现
//5).可以用new创建模板类对象（语法有点奇怪）
//6).在程序中，模板类的成员函数使用了才会创建（这就是为什么有的数据类型不适应模板类中的成员函数的代码，但能通过编译的原因）

#include<iostream>
using namespace std;

template<class T1,class T2=string>//注3
class AA {
public:
	T1 m_a;//通用类型用于成员变量
	T2 m_b;//通用类型用于成员变量

	AA() {};
	AA(T1 a, T2 b) :m_a(a), m_b(b) {};

	//通用类型用于成员函数的返回值和代码
	T1 geta() {
		T1 a = 2;
		return m_a + a;
	}

	T2 getb();
};

//template<class T1, class T2 = string>//虽然编译器报错说不能在类外的类模板成员声明上指定默认模板参数，但编译能通过
template<class T1, class T2>
T2 AA<T1,T2>::getb() {
	//T2 b = 1;
	//return m_b + b;

	return m_b;

}//注4

int main() {
	AA<int, double>a;//用模板类创建对象a
	a.m_a = 20, a.m_b = 30;
	cout << "a.geta()=" << a.geta() << ",a.getb()=" << a.getb() << endl;


	AA<string, double>b;
	b.m_a = 90, a.m_b = 100;
	//cout << "b.geta()=" << b.geta() << ",b.getb()=" << b.getb() << endl;//注2(注6):如果getb成员函数不改的话

	AA<int>c;//第二个通用类型为string——注3


	AA<int, string>* d = new AA<int, string>(3, "hello world");//——注5
	auto d2 = d;
	//AA不是类名，是模板名，，AA<int, string>才是类名
	cout << "d->geta()=" << d->geta() << endl;
	cout << "d->getb()=" << d->getb() << endl;
	delete d;
}