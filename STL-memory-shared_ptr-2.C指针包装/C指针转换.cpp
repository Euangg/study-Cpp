#include<memory>
using std::shared_ptr;
using std::make_shared;

#include<iostream>
using std::cout;
using std::endl;

//将从堆内存指针包装成shared_ptr
void test1() {
	int* p = new int(5);
	shared_ptr<int> sp(p);//所有权转移，最好不要再使用原指针p了，能用但千万不要通过原指针执行释放操作

	*sp = 15;
	cout << *p << endl;//可以通过原指针访问
	*p = 20;
	cout << *sp << endl;//可以通过原指针修改

	//delete p;//不能通过原指针释放！会导致重复释放
	cout << "end" << endl;
}

//不要用shared_ptr再去包装栈空间地址，危险且不规范
//栈会自动管理释放空间，shared_ptr是为堆内存设计的，栈内存完全不适用！
void test2() {
	int a = 10;
	shared_ptr<int>sp(&a);//危险，运行时会发生严重错误！
}

void main() {
	test2();
}



