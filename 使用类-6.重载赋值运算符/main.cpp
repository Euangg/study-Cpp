//C++编译器可能会给类添加4个函数
//1).默认构造函数（空实现）
//2).默认析构函数（空实现）
//3).默认拷贝构造函数，对成员变量进行浅拷贝
//4).默认赋值函数，对成员变量进行浅拷贝				如果类的定义中没有重载赋值函数，编译器就会提供一个默认的赋值函数

//对象的赋值运算是用一个已经存在的对象，给另一个已存在的对象赋值
//如果类中重载了赋值函数，编译器将不提供默认赋值函数
//重载赋值函数的语法：类名& oprator=(const 类名& 源对象)

//注：编译器提供的赋值函数是浅赋值

//赋值运算和拷贝构造不同：
//拷贝构造是指原来的对象不存在，用现有的对象构造
//赋值运算是指已存在了两个对象，把其中一个对象的成员变量赋值给另一个对象的成员变量

#include<iostream>
using namespace std;

class A {
public:
	int m_bh;
	string m_name;
	int* m_ptr;

	A() { m_ptr = nullptr; };
	~A() { if (m_ptr)delete m_ptr; }
	void show() { cout << "bh:" << m_bh << ",name:" << m_name << ",address:" << m_ptr /*<< ",value:" << *m_ptr*/ << endl; };
	A& operator=(const A& a) {
		if (this == &a)return *this;	//如果给自己赋值 直接return

		this->m_bh = a.m_bh;
		this->m_name = a.m_name;
		if (a.m_ptr == nullptr) {	//如果源对象指针为空，则清空目标对象的指针
			if (m_ptr != nullptr) {
				delete m_ptr;
				m_ptr = nullptr;
			}
		}
		else {						//如果不为空，保证目标指针指向空间，且指向空间的值与源对象的相等
			if (m_ptr == nullptr) {
				m_ptr = new int;
			}
			memcpy(m_ptr, a.m_ptr, sizeof(int));
		}
		cout << "调用了赋值函数" << endl;
		return *this;
	}
};

int main() {
	A a1, a2;
	a1.m_bh = 8; a1.m_name = "asdsad";
	a1.m_ptr = new int(3);
	a1.show();
	a2.show();

	a2 = a1;	//如果未重载赋值运算符，相当于a2.m_bh=a1.m_bh ;a2.m_name=a1.m_name
	a2.show();
}


