//在实际开发中，多继承很少使用
//而虚继承又是为了解决多继承的问题才出现的，应用更少

//多继承语法
//class 派生类名 : [继承方式1] 基类1, [继承方式2] 基类2, [继承方式3] 基类3.......{派生类新增成员}


//菱形继承
//存在两个问题————数据冗余和名称二义
//虚继承

#include<iostream>
using namespace std;

class A1 {
public:
	int m_a = 10;
	int m_aa = 11;

};

class A2 {
public:
	int m_b = 20;
	int m_aa = 12;
};

class B :public A1, public A2 {
public:
	int m_c = 30;
	int m_aa = 13;
};

//菱形继承
//class AA {
//public:
//	int m_a = 10;
//};
//
//class BB :public AA {
//
//};
//
//class CC :public AA {
//
//};
//
//class DD :public BB, public CC {
//
//	//会继承两个m_a
//};

class AA {
public:
	int m_a = 10;
};

class BB :virtual public AA {//虚继承AA
	//会多出一个隐藏的虚基类指针
};

class CC :virtual public AA {//虚继承AA————今后在多继承中遇到同样虚继承AA的基类时，二者AA部分的内容会合并
	//会多出一个隐藏的虚基类指针
};


class DD :public BB, public CC {
	//大小12byte
	//原理：
	//虚基类AA单独取到内存模型的一块（保证不会重复）
	//继承虚基类（爷类）的父类们会各多出一个虚基类指针（4byte）
	
};


int main() {

	B b;
	cout << b.m_a << b.m_b << b.m_c << endl;
	cout << b.m_aa << b.A1::m_aa << b.A2::m_aa << endl;



	//
	DD d;
	cout << sizeof(d) << endl;
	//d.m_a = 111;//不使用虚继承，报错，访问不明确
	cout << d.CC::m_a << endl;
	d.m_a = 111;
	cout << d.m_a << endl;

}



//开发经验
//总的来说不提倡使用多继承，只有在比较简单和不出现二义性的情况时才使用多继承
//能用单一继承解决的问题就不要使用多继承

//如果继承的层次很多、关系很复杂，
//会增加程序的编写、调试和维护工作的难度
//由于这个原因，C++之后的很多面向对象的编程语言，如JAVA、C#、PHP等，都不支持多继承
