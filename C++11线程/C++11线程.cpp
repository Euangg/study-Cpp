#include<iostream>
#include<thread>
#include<Windows.h>
using namespace std;

//编程语言级别的支持
//C++编译器自带头文件<thread>，里面封装了thread类

//线程是一种特别的类，线程对象不允许拷贝
//在thread类定义中有如下代码：
//thread(const thread&)=delete;
//表示删除拷贝构造函数，不允许线程对象之间拷贝

//thread(thread&& other)noexcept;
//表示移动构造函数，将线程other的资源所有权转移给新创建的线程对象，转移之后，原来的线程对象不再代表线程
//thread& operator=(thread&& other)noexcept;
//thread& operator=(const other&)=delete;
//线程中的资源不能被复制，所以删除了参数为左值的赋值函数
//但是，可以转移，保留了参数为右值的赋值函数


//1.普通函数
void task1() {
	for (int ii = 1; ii <= 20; ii++) {
		cout << "task:" << ii << endl;
		Sleep(10);
	}
}
void test1() {
	thread t(task1);
	t.join();
	cout << "执行完成" << endl;//join函数会阻塞，等待子线程完成
}


//2.仿函数
struct task2 {
	//仿函数的本质是重载()运算符
	void operator()(int a) {
		for (int ii = 1; ii <= 10; ii++) {
			cout <<"task2:" << ii  << endl;
			Sleep(10);
		}
	}
};
void test2() {
	thread t(task2(),4);//仿函数必须有参//仿函数作为副线程执行体传入要加()
	t.join();
}


//3.成员函数
struct task3 {
	void task() {
		for (int ii = 1; ii <= 10; ii++) {
			cout << "task3:" << ii << endl;
			Sleep(10);
		}
	}
};
void test3() {
	//必须实例化类的对象，必须保证对象的生命周期比该副线程长
	task3 st;
	thread t(&task3::task, &st);
	//第一个参数填成员函数的地址，紧跟类（引用或地址都可），这二者将保证出正常的函数
	//随后跟参数包
	t.join();
}

//4.匿名函数
void test4() {
	//创建线程
	auto f = []() {
		for (int ii = 1; ii <= 10; ii++) {
			cout << "task4:" << ii << endl;
			Sleep(10);
		}
	};
	thread t(f);
	t.join();
}


int main() {
	//test1();
	//test2();
	//test3();
	test4();
}