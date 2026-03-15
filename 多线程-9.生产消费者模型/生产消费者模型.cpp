//C++11的条件变量提供了两个类：
//1.condition_variable：只支持与普通mutex搭配，效率更高
//2.condition_variable_any：一种通用的条件变量，可以与任意mutex搭配（包括用户自定义的锁类型，例如timed_mutex）


//1.condition_variable类
//主要成员函数：
//	notify_one()通知一个等待的线程
//	notify_all()通知全部等待的线程
//	wait(unique_lock<mutex> lock)阻塞当前线程，直到通知到达
//		·把互斥锁解锁
//		·阻塞，等待被唤醒
//		·重新给互斥锁加锁
//	wait(unique_lock<mutex> lock,Pred pred)循环的阻塞当前线程，直到通知到达且谓词满足
//	wait_for(unique_lock<mutex>,时间长度)
//	wait_for(unique_lock<mutex>,时间长度,Pred pred)
//	wait_until(unique_lock<mutex>,时间点)
//	wait_until(unique_lock<mutex>,时间点,Pred pred)


//2.unique_lock类
//template<class Mutex> class unique_lock是模板类，模板参数为互斥锁类型
//unique_lock和lock_guard都是管理锁的辅助类，都是RAII风格（构造时获得锁，析构时释放锁）
//它们的区别在于：为了配合条件变量condition_variable，unique_lock还有lock()和unlock()成员函数，用于手动上锁或解锁

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
		//m_cond.notify_one();//唤醒一个被当前条件变量阻塞的线程——一次多条数据由一个线程处理
		m_cond.notify_all();//唤醒所有被当前条件变量阻塞的线程
	};


	//消费者线程任务函数
	void outcache() {
		while (true) {
			//把互斥锁转换成unique_lock<mutex>，并申请加锁
			unique_lock<mutex> lock(m_mutex);

			//条件队列可能存在虚假唤醒的情况：即消费者线程被唤醒后，缓存队列中没有数据（可能被同时唤醒的其它线程取走）
			//所以要通过循环反复检查和等待，必须用循环，不能用if
			
			//while (m_q.empty())		//如果数据队列为空
			//	m_cond.wait(lock);	//通过该条件变量等待生产者的唤醒信号

			m_cond.wait(lock, [this] {return !m_q.empty(); });//效果同上面的循环
			//参数2为谓词，重载的wait内部封装了一个循环

			//同时，条件变量的wait函数需要一把互斥锁，执行时会释放该互斥锁
			//·把互斥锁解锁
			//·阻塞，等待被唤醒
			//·重新给互斥锁加锁

			//数据元素出队
			string message = m_q.front(); m_q.pop();//取；出
			cout << "线程" << this_thread::get_id() << "：" << message << endl;
			lock.unlock();	//手动解锁（限定作用域，自动解锁）

			//处理出队的数据（消耗掉数据）
			this_thread::sleep_for(chrono::milliseconds(1));//假设处理数据需要1ms
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