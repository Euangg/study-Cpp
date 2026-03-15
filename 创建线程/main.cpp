#include<iostream>
#include<thread>
#include<Windows.h>
using namespace std;

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



//副线程任务(普通函数)
void func(int id,const string& name) {
	cout << "副线程标识：" << id << endl;
	cout << "副线程名称：" << name << endl;
	for (int i = 1; i <= 20; i++) {
		cout << "副线程" << name << "(" << id << ")" << "第" << i << "次处理..." << endl;
		Sleep(100);
	}
}

//副线程任务(仿函数)
class myThread1 {
public:
	void operator()(int id, const string& name) {
		cout << "副线程(仿函数)标识：" << id << endl;
		cout << "副线程(仿函数)名称：" << name << endl;
		for (int i = 1; i <= 20; i++) {
			cout << "副线程(仿函数)" << name << "(" << id << ")" << "第" << i << "次处理..." << endl;
			Sleep(100);
		}
	};
};

//副线程任务(成员函数)
class myThread2 {
public:
	static void st_func(int id, const string& name) {
		cout << "副线程(静态成员)标识：" << id << endl;
		cout << "副线程(静态成员)名称：" << name << endl;
		for (int i = 1; i <= 20; i++) {
			cout << "副线程(静态成员)" << name << "(" << id << ")" << "第" << i << "次处理..." << endl;
			Sleep(100);
		}
	};

	void co_func(int id, const string& name) {
		cout << "副线程(普通成员)标识：" << id << endl;
		cout << "副线程(普通成员)名称：" << name << endl;
		for (int i = 1; i <= 20; i++) {
			cout << "副线程(普通成员)" << name << "(" << id << ")" << "第" << i << "次处理..." << endl;
			Sleep(100);
		}
	};
};


int main() {
	//用普通函数创建线程
	thread t1(func, 1278, "APPLE");
	thread t2(func, 8001, "STRAWBERRY");

	//用lambda函数创建线程
	auto f = [](int id, const string& name) {
		cout << "副线程(lambda函数)标识：" << id << endl;
		cout << "副线程(lambda函数)名称：" << name << endl;
		for (int i = 1; i <= 20; i++) {
			cout << "副线程(lambda函数)" << name << "(" << id << ")" << "第" << i << "次处理..." << endl;
			Sleep(100);
		}
	};
	thread t4(f, 1812, "ORANGE");

	//用仿函数创建线程
	thread t3(myThread1(), 24, "PEAR");//仿函数作为副线程执行体传入要加()

	//用类的成员函数创建线程
	//静态成员
	thread t5(myThread2::st_func, 5555, "CHERRY");
	//普通成员
	myThread2 mythread;//必须实例化类的对象，必须保证对象的生命周期比该副线程长
	thread t6(&myThread2::co_func, &mythread, 66661, "MELON");

	cout << "Start:" << endl;
	for (int i = 0; i < 20; i++) {
		cout << "主线程处理中..." << endl;
		Sleep(100);
	}

	//回收副线程资源
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
}