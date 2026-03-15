//类模板具体化（特化、特例化）有两种：完全具体化和部分具体化
//具体化程度高的类优先于具体化程度低的类，具体化的类优先于没有具体化的类

#include<iostream>
using namespace std;

//类模板
template<class T1,class T2>
class AA {
public:
	T1 m_x;
	T2 m_y;

	AA(const T1 x, const T2 y) :m_x(x), m_y(y) {
		cout << "类模板：构造函数" << endl;
	}
	void show()const;//类内声明，类外实现

};


template<class T1,class T2>
void AA<T1, T2>::show()const {
	cout << "类模板:x=" << m_x << ",y=" << m_y << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
//类模板完全具体化
template<>
class AA<int, string> {
public:
	int m_x;
	string m_y;

	AA(const int x,const string y):m_x(x),m_y(y){
		cout << "完全具体化：构造函数" << endl;
	}

	void show()const;
};

void AA<int, string>::show() const {
	cout << "完全具体化：x=" << m_x << ",y=" << m_y << endl;
}
////////////////////////////////////////////////////////////////////////////////////////
//类模板部分具体化————（函数模板就没有部分具体化的说法，只有类模板才有）
template<class T1>
class AA<T1, string> {
public:
	T1 m_x;
	string m_y;

	AA(const T1 x, const string y) :m_x(x), m_y(y) {
		cout << "部分具体化：构造函数" << endl;
	}
	void show()const;
};
template<class T1>
void AA<T1, string>::show() const {//成员函数类外实现
	cout << "部分具体化：x=" << m_x << ",y=" << m_y << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////


int main() {
	//具体化程度高的类优先于具体化程度低的类，具体化的类优先于没有具体化的类
	AA<int, string>aa(8, "hello world");
	aa.show();
	AA<string, string>bb("this is", "xyy");
	bb.show();
	AA<string, int>cc("Suu", 999);
	cc.show();
}