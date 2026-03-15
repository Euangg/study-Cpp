//在多线程环境中，某些函数只能被调用一次，
//例如：初始化某个对象，而这个对象只能被初始化一次

//在线程的任务函数中，可以用std::call_once()来保证某个函数只被调用一次

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

#include<Windows.h>


once_flag onceflag;//once_flag全局变量，本质是取值为0和1的锁
//在主线程中，打算只调用一次的函数
void once_func(const int bh, const string& str) {
	cout << "once_func() bh=" << bh << ",str=" << str << endl;
}

void func(int bh, const string& str) {
	//保证函数只调用一次
	call_once(onceflag, once_func, 999, "******************");
	

	for (int ii = 1; ii <= 3; ii++) {
		cout << "线程" << bh << "第" << ii << "次输出：" << str << endl;
		this_thread::sleep_for(chrono::seconds(1));//休眠1s
	}
}

int main() {
	thread t1(func, 3, "CPP子线程中");
	thread t2(func, 666, "测试交换的子线程");
	
	t1.join();
	t2.join();

	return 0;
}