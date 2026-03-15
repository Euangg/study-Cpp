//线程的任务函数返回后，子线程将终止
//如果主程序（主线程）退出（不论正常还是意外），所有子线程将被强行终止
//子线程的资源一定要回收，如果不回收，会产生僵尸线程，程序还会报错

//回收子线程资源的两种方法
//1.在主程序中，调用join()成员函数等待子线程退出，回收它的资源。
//	如果子线程已退出，函数会立刻返回，否则会产生阻塞，直到子线程退出。
//2.在主线程中调用detach()函数分离子线程，子线程退出时，系统将自动回收资源。
//	分离后的线程不能使用join()
//	使用joinable()成员函数可以判断子线程的分离状态，函数返回布尔型

#include<iostream>
#include<thread>
using namespace std;


void func(const string& name) {
	cout << "子线程" << name << "开始..." << endl;

}


int main() {
	cout << "主线程开始..." << endl;
	

	thread t1(func, "APPLE");
	thread t2(func, "BANANA");
	//1.使用join()成员函数阻塞等待
	/*t1.join();
	t2.join();*/

	//2.使用detach()分离子线程
	t1.detach();
	t2.detach();

	for (int i = 0; i <= 100; i++) {
		cout << "主线程任务进度：" << i << "%" << endl;
	}

	return 0;
}