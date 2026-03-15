//1.创建派生类对象时，先调用基类的构造函数，再调用派生类的构造函数
//2.销毁派生类对象时，先调用派生类的析构函数，再调用基类的析构函数


#include<iostream>
using namespace std;

void* operator new(size_t size) {
	void* ptr = malloc(size);
	cout << "申请到的内存的地址是:" << ptr << "，大小是:" << size << endl;
	return ptr;

}

void operator delete(void* ptr) {
	if (ptr == 0)return;//保证对空指针delete安全
	free(ptr);
	cout << "内存已释放" << endl;
}

class A {
public:
	int m_a = 10;
protected:
	int m_b = 20;
private:
	int m_c = 30;


public:
	A() { 
		cout << "A的构造" << endl; 
		cout << "A的this指针是:" << this << endl;
		cout << "A中m_a的地址是:" << &m_a << endl;
		cout << "A中m_b的地址是:" << &m_b << endl;
		cout << "A中m_c的地址是:" << &m_c << endl;
	};
	~A() { cout << "A的析构" << endl; };
	void func() {
		cout << "m_a=" << m_a << ",m_b=" << m_b << ",m_c=" << m_c << endl;
	}
};

class A_A :public A {
public:
	int m_d = 40;

public:
	A_A() { 
		cout << "A_A的构造" << endl;
		cout << "A_A的this指针是:" << this << endl;
		cout << "A_A中m_a的地址是:" << &m_a << endl;
		cout << "A_A中m_b的地址是:" << &m_b << endl;
		//cout << "A_A中m_c的地址是:" << &m_c << endl;//基类的私有成员不可见，但占用内存；就像没有，被去掉了一样
		cout << "A_A中m_d的地址是:" << &m_d << endl;
	};
	~A_A() { cout << "A_A的析构" << endl; };
	void func1() {
		cout << "m_d=" << m_d << endl;

	}

};


int main() {

	cout << "基类A占用内存的大小是:" << sizeof(A) << endl;
	cout << "派生类A_A占用内存的大小是:" << sizeof(A_A) << endl;

	//A_A a;
	A_A* p = new A_A;//只申请了一次内存

	p->func(); p->func1();
	memset(p, 0, sizeof(A_A));//操作内存，突破语法限制（m_c在A类外不可访问，甚质在p中都不可见，但还是被修改了）
	p->func(); p->func1();
	*((int*)p + 2) = 555;//操作指针，突破语法限制，修改m_c
	p->func(); p->func1();
	delete p;
}


//3.创建派生类对象时只会申请一次内存，派生类对象包含了基类对象的内存空间，this指针相同
//4.创建派生类对象时，先初始化基类对象，再初始化派生类对象

