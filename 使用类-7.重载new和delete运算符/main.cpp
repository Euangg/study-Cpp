//重载new和delete目的是为了自定义内存分配细节
//内存池（快速分配和归还，无碎片）


//在C++中，使用new时，编译器做了两件事
//1)调用标准库函数 operator new()分配内存
//2)调用构造函数初始化内存

//使用delete时，编译器做了两件事
//1)调用析构函数
//2)调用标准库函数operator delete()释放内存

//构造函数和析构函数由编译器调用，我们无法控制
//但是我们可以重载内存分配函数operator new()和释放函数operator delete()
//1)重载内存分配函数的语法：void* operator new(size_t size);
//	参数必须是size_t，返回值必须是void*
//2)重载内存释放函数的语法：void operator delete(void* ptr);
//	参数必须是void*（指向由operator new()分配的内存），返回值必须是void
//重载的new和delete可以是全局函数，也可以是类的成员函数
//在全局区重载影响全局，在类中重载只影响此类

#include<iostream>
using namespace std;

void* operator new(size_t size) {
	cout << "调用了全局重载的new：" << size << "byte" << endl;
	void* ptr = malloc(size);
	cout << "申请到的内存地址是：" << ptr << endl;
	return ptr;
}

void operator delete(void* ptr) {
	cout << "调用了全局重载的delete" << endl;
	if (ptr == 0)return;//对空指针delete是安全的
	free(ptr);//释放内存
}


class CGirl {
public:
	int m_bh;
	int m_xw;

	CGirl(int bh, int xw) {
		m_bh = bh;
		m_xw = xw;
		cout << "调用了构造函数CGirl()" << endl;
	}

	~CGirl() { cout << "调用了析构函数~CGirl" << endl; }


	//不管写不写static，他俩都是静态成员函数，不能访问非静态成员
	void* operator new(size_t size) {
		cout << "调用了类重载的new：" << size << "byte" << endl;
		void* ptr = malloc(size);
		cout << "申请到的内存地址是：" << ptr << endl;
		return ptr;
	}

	void operator delete(void* ptr) {
		cout << "调用了类重载的delete" << endl;
		if (ptr == 0)return;//对空指针delete是安全的
		free(ptr);//释放内存
	}

};


int main() {
	int* p1 = new int(3);
	cout << "p1=" << p1 << "，*p1=" << *p1 << endl;
	delete p1;


	CGirl* p2 = new CGirl(3, 8);
	delete p2;
}

