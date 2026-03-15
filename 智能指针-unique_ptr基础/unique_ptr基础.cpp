//普通指针的不足
//1.new和new[]的内存需要用delete和delete[]释放——繁琐
//2.程序员主观失误，会忘记释放——内存泄露
//3.程序员有时也不确定合适释放——不易控制好

//智能指针的设计思路
//1.智能指针是模板类，在栈上创建智能指针对象
//2.把普通指针交给智能指针对象
//3.智能指针对象过期时，通过调用其析构函数释放普通指针的内存

//智能指针的类型
//auto_ptr，C++98标准，C++17已弃用
//unique_ptr、shared_ptr、weak_ptr，C++11标准

//unique_ptr，独占其指向的对象，一个对象只能被一个unique_ptr管理，当这个unique_ptr被销毁时，指向的对象也随之销毁
//性能接近裸指针

#include<memory>
#include<iostream>
using std::cout;
using std::endl;
using std::unique_ptr;

//基本操作
void test1() {
	auto ptr = std::make_unique<int>(42);
	cout << *ptr << endl;//42	
	(*ptr)++;
	auto ptr2 = std::move(ptr);//所有权转移,ptr1归1
	cout << ptr.get() << endl;
	cout << *ptr2 << endl;	
	ptr2.reset();//ptr2归0
	cout << ptr2.get() << endl;
}

//赋值替换
void test2() {
	unique_ptr<int> ptr = std::make_unique<int>(55);
	int* p1 = ptr.get();
	cout << p1 <<":"<<*p1 << endl;
	ptr= std::make_unique<int>(5555);//原来的被释放了
	cout << p1 << ":" << *p1 << endl;
}


int main() {
	//test1();
	test2();
}
