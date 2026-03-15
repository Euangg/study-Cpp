//1)模板类继承普通类（常见）
//2)普通类继承模板类的实例版本
//3)普通类继承模板类（常见）
//4)模板类继承模板类
//5)模板类继承模板参数给出的基类（不能是模板类）

#include<iostream>
using namespace std;
class AA {//普通类AA
public:
	int m_a;
	AA(int a) :m_a(a) {
		cout << "调用了AA的构造函数" << endl;
	}
	void func1() { cout << "调用了func1()函数：m_a=" << m_a << endl; };
};

template<class T1,class T2>
class BB {//模板类BB
public:
	T1 m_x;
	T2 m_y;
	BB(const T1 x, const T2 y) :m_x(x), m_y(y) {
		cout << "调用了BB的构造函数" << endl;
	}
	void func2()const { cout << "调用了func2()函数：m_x=" << m_x << ",m_y=" << m_y << endl; };
};

//1)模板类继承普通类（常见）
//template<class T1, class T2>
//class BB:public AA {//模板类BB
//public:
//	T1 m_x;
//	T2 m_y;
//	BB(const T1 x, const T2 y,int a) :AA(a),m_x(x), m_y(y) {//因为基类没有默认构造函数，所以要在派生类构造函数中指明基类构造函数
//		cout << "调用了BB的构造函数" << endl;
//	}
//	void func2()const { cout << "调用了func2()函数：m_x=" << m_x << ",m_y=" << m_y << endl; };
//};

//2)普通类继承模板类的实例版本
//class CC :public BB<int, string> {
//public:
//	int m_c;
//	CC(int a, int x, string y) :BB(x, y), m_c(a) {
//		cout << "调用了CC的构造函数" << endl;
//	}
//	void func1() {
//		cout << "调用了func1()函数：m_c=" << m_c << endl;
//	}
//};

//3)普通类继承模板类（常见）
//template<class T1, class T2>//普通类要继承模板类，要先把自己变成模板类
//class CC :public BB<T1, T2> {
//public:
//	int m_c;
//	CC(int a, T1 x, T2 y) :BB<T1,T2>(x, y), m_c(a) {//指明的基类的构造函数不能直接写BB，要加<>填入T1 T2
//		cout << "调用了CC的构造函数" << endl;
//	}
//	void func1() {
//		cout << "调用了func1()函数：m_c=" << m_c << endl;
//	}
//};

//4)模板类继承模板类
//template<class T,class T1,class T2>//模板类继承模板类，根据需求调整通用类型表
//class CC :public BB<T1, T2> {
//public:
//	T m_a;
//	CC(const T a, const T1 x, const T2 y) :BB<T1, T2>(x, y), m_a(a) {
//		cout << "调用了CC的构造函数" << endl;
//	}
//	void func3() {
//		cout << "调用了func3()函数：m_a=" << m_a << endl;
//	}
//};

//5)模板类 继承 模板参数给出的基类（不能是模板类）————基类是不确定的，是可以改变的
class A {
public:
	A() { cout << "调用了A的构造函数A()" << endl; };
	A(int a) { cout << "调用了A的构造函数A(int a)" << endl; };
};

class B {
public:
	B() { cout << "调用了B的构造函数B()" << endl; };
	B(int a) { cout << "调用了B的构造函数B(int a)" << endl; };

};

class C {
public:
	C() { cout << "调用了C的构造函数C()" << endl; };
	C(int a) { cout << "调用了C的构造函数C(int a)" << endl; };

};

template<class T>
class D {
public:
	D() { cout << "调用了D的构造函数D()" << endl; };
	D(int a) { cout << "调用了D的构造函数D(int a)" << endl; };

};

template<class T>
class E :public T {
public:
	E() : T() { cout << "调用了E的构造函数E()" << endl; };

	E(int a) :T(a) { cout << "调用了E的构造函数E(int a)" << endl; };
};



int main() {
	//1.
	/*BB<int, string>bb(8, "hello",3);
	bb.func2();
	bb.func1();*/
	////////////////////////////////////////////////////////////////////
	//2.
	/*CC cc(3, 8, "hello");
	cc.func1();
	cc.func2();*/
	///////////////////////////////////////////////////////////////////////
	//3.
	/*CC<int, string>cc(1, 3, "helld");
	cc.func1();
	cc.func2();*/
	///////////////////////////////////////////////////////////////////////////
	//4.
	/*CC<int, int, string>cc(3, 4, "hello");
	cc.func2();
	cc.func3();*/
	////////////////////////////////////////////////////////////////////////////////////
	//5.
	E<A>ea1;//A作为模板参数并作为基类
	E<B>eb1;
	E<C>ec1;
	E<D<int>>ed1;


}