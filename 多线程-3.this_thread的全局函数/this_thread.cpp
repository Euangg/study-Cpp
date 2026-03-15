//C++11提供了this_thread命名空间来表示当前线程
//该命名空间中有四个函数：
//1.get_id()获取线程ID
// thread::id get_id() noexcept;用于获取线程ID，thread类中也有同名的成员函数
//2.sleep_for()线程休眠指定时长，指定休眠多长时间，参数为时间长度
//3.sleep_until()线程休眠到指定时间点，可实现定时任务，参数为时间点
//4.yield()线程主动让出已获取的时间片

//thread类的其它成员函数(2)
//1.void swap(std::thread& other);//交换两个线程对象
//2.static unsigned hardware_concurrency() noexcept;//返回硬件线程上下文的数量


#include<iostream>
#include<thread>
using namespace std;

#include<Windows.h>

void func(int bh, const string& str) {
	cout << "子线程id(this_thread命名空间获取)" << this_thread::get_id() << endl;
	for (int ii = 0; ii <= 3; ii++) {
		cout << "线程" << bh << "第" << ii + 1 << "次输出：" << str << endl;
		this_thread::sleep_for(chrono::seconds(1));//休眠1s
	}
}

int main() {
	cout << "主线程id" << this_thread::get_id() << endl;
	thread t1(func, 3, "CPP子线程中");
	thread t2(func, 666, "测试交换的子线程");
	cout << "子线程1id(成员函数获取)" << t1.get_id() << endl;
	cout << "子线程2id(成员函数获取)" << t2.get_id() << endl;
	t1.swap(t2);
	cout << "子线程1id(成员函数获取)" << t1.get_id() << endl;
	cout << "子线程2id(成员函数获取)" << t2.get_id() << endl;
	


	//thread t3 = t2;//编译报错：thread的拷贝构造函数已删除
	thread t3 = move(t2);//移动构造函数，移动后，t2不再代表线程，转为t3代表，t2不能再进行线程操作

	t1.join();
	t3.join();//t2移动给t3，转由t3执行线程操作

	return 0;
}