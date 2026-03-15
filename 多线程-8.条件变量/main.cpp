//条件变量：当条件不满足时，相关线程被一直阻塞，直到某种条件出现 这些线程才会被唤醒
//·为了保护共享资源，条件变量需要和互斥锁结合一起使用
//·条件变量常用于实现【生产/消费者模型】，进而实现【高速缓存队列】

//C++11的条件变量提供了两个类：
//condition_variable：只支持与普通mutex搭配，效率更高
//condition_variable_any：一种通用的条件变量，可以与任意mutex搭配（包括用户自定义的锁类型）

#include<iostream>				
#include<string>
#include<thread>				//线程类头文件
#include<mutex>					//互斥锁类头文件
#include<deque>					//deque容器的头文件
#include<queue>					//queue容器的头文件
#include<condition_variable>	//条件变量的头文件
using namespace std;

class AA {
	mutex m_mutex;					//互斥锁
	condition_variable m_cond;		//条件变量
	queue<string, deque<string>>m_q;//缓存队列，底层容器用deque
public:
	//生产者线程
	void incache(int num) {//num指定生产数据的个数
		lock_guard<mutex>lock(m_mutex);//申请加锁
		for (int ii = 0; ii < num; ii++) {
			static int bh = 1;
			string message = to_string(bh++) + "号数据";
			m_q.push(message);//数据入队
		}
		m_cond.notify_one();//唤醒一个被当前条件变量阻塞的线程
	};


	//消费者线程任务函数
	void outcache() {
		while (true) {
			string message;//作用域外要用的，预先定义
			{//强制加作用域
				//把互斥锁转换成unique_lock<mutex>，并申请加锁
				unique_lock<mutex> lock(m_mutex);
				while (m_q.empty())		//如果数据队列为空，必须用循环，不能用if
					m_cond.wait(lock);	//通过该条件变量等待生产者的唤醒信号

				//数据元素出队
				message = m_q.front(); m_q.pop();//取；出
			}
			//处理出队的数据（消耗掉数据）
			this_thread::sleep_for(chrono::milliseconds(1));//假设处理数据需要1ms
			cout << "线程" << this_thread::get_id() << "：" << message << endl;
		}
	}
};

int main() {
	AA aa;

	thread t1(&AA::outcache, &aa);//创建消费者线程t1
	thread t2(&AA::outcache, &aa);//创建消费者线程t2
	thread t3(&AA::outcache, &aa);//创建消费者线程t3

	this_thread::sleep_for(chrono::seconds(2));//主线程休眠2s
	aa.incache(3);

	this_thread::sleep_for(chrono::seconds(3));//主线程休眠3s
	aa.incache(5);

	t1.join();
	t2.join();
	t3.join();
}