//C++11提供了atomic<T>模板类（结构体）,用于支持原子类型
//模板参数可以bool、char、int、long、long long、指针类型，不支持浮点数和自定义数据类型
//原子操作由CPU指令提供支持，支持修改、读取、交换、比较并交换等操作
//它的性能比锁和消息传递更好，并且不需要程序员处理加锁和解锁问题

//----------------------demo1
//#include<iostream>
//#include<thread>
//#include<atomic>
//using namespace std;
//
//atomic<int> aa = 0;
//
//void func() {
//	for (int i = 1; i <= 1000000; i++)aa++;
//}
//
//int main() {
//	thread t1(func);
//	thread t2(func);
//	t1.join();
//	t2.join();
//
//	cout << aa << endl;
//	return 0;
//}


//---------------------demo2
//#include<iostream>
//#include<atomic>
//using namespace std;
//
//int main() {
//	//atomic<int>a = 3;					//atomic(T val)noexcept;//转换函数
//	//cout << "a=" << a.load() << endl;	//读取原子变量a的值
//	//a.store(8);							//把8存储到原子变量中
//	//cout << "a=" << a.load() << endl;	//读取原子变量a的值
//
//	//int old;//用于存放原值
//	//old = a.fetch_add(5);//把原子变量的值与5相加，返回原值
//	//cout << "old=" << old << "\ta=" << a.load() << endl;//old为a原来的值，a为+5后的值
//	//old = a.fetch_sub(2);
//	//cout << "old=" << old << "\ta=" << a.load() << endl;//old为a原来的值，a为-2后的值
//
//	atomic<int>ii = 3;	//原子变量
//	int expect = 3;		//期待值
//	int val = 5;		//打算存入原子变量的值
//
//	bool bret = ii.compare_exchange_strong(expect, val);
//	//比较原子变量的值和expect的值，
//	//如果两个值相等，ii=val，返回true
//	//如果两个值不相等，expect=ii，返回false
//	cout << "bret=" << bret << endl;
//	cout << "ii=" << ii << endl;
//	cout << "expect=" << expect << endl;
//
//}


//指针是原子类型，不表示指针指向的对象也是原子类型
//---------------------------------------------------demo3
#include<iostream>
#include<thread>
#include<atomic>
using namespace std;

int aa = 0;
atomic<int*>ptr = &aa;

void func() {
	for (int i = 1; i <= 1000000; i++)(*ptr)++;
}

int main() {
	thread t1(func);
	thread t2(func);
	t1.join();
	t2.join();

	cout << aa << endl;
	return 0;
}


//原子整型 可以用作计数器，原子布尔型 可以用作开关；如果要锁住一个对象或一段代码，还得用互斥锁
//CAS指令是实现无锁队列的基础