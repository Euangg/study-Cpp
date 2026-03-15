#include<iostream>
using namespace std;


class CAllComers {
public:
	int m_bh = 0;
	virtual void show() {
		cout << "CAllComers::show(): " << m_bh << endl;
	}

	

};


class CGirl :public CAllComers {

public:
	int m_age = 0;
	void show() {
		cout << "CGirl::show(): " << m_bh << '\t' << m_age << endl;
	}

};


int main() {
	CGirl g;
	g.m_bh = 8;
	g.m_age = 23;
	g.show();
	CAllComers* pa = &g;
	pa->show();



	CAllComers a; a.m_bh = 3;
	CGirl gg; gg.m_bh = 8; g.m_age = 23;

	CAllComers* ppp;
	ppp = &a; ppp->show();
	ppp = &gg; ppp->show();
	//有了虚函数，基类指针指向基类对象时就使用基类的成员函数和数据，指向派生类对象时就使用派生类的成员函数和数据
	//这种基类指针表现出多种形式的现象称为多态


	CAllComers& yyy1 = a;
	yyy1.show();
	CAllComers& yyy2 = gg;
	yyy2.show();
	yyy2.CAllComers::show();
	//基类引用也可以使用多态
}

//注：
//1.只需要在基类的函数声明上加virtual关键字，函数定义时不能加virtual关键字（声明与定义合并时可以）
//2.在派生类中重定义同名虚函数时，函数特征要相同（参数表、函数名、  返回值）
//3.当在基类中定义了虚函数时，如果派生类没有重定义该函数，那么将使用基类的虚函数
//4.在派生类重定义了虚函数的情况下，如果想使用基类的虚函数，可以加类名和域解析符

//5.(exp)如果要在派生类中重新定义基类的函数，则将它设置为虚函数；否则，不要设置虚函数，
//有两个好处：普通函数效率更高、相当于指出不要重定义该函数（表达程序员意图）
//但是把基类的成员函数都设置为虚函数，语法上没有任何问题