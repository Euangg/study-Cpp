//线程同步：多个线程协同工作，协商如何使用共享资源

//C++11线程同步（3）：
//1.互斥锁（互斥量）
//	加锁和解锁，确保同一时间只有一个线程访问共享资源
//	访问共享资源之前加锁，访问完成后释放锁
//	如果线程持有锁，其它的线程形成等待队列
//2.条件变量
//3.生产/消费者模型


//C++11提供了4种互斥锁：
//1.mutex：普通互斥锁
//2.timed_mutex：带超时机制的互斥锁
//3.recursive_mutex：递归互斥锁
//4.recursive_timed_mutex:带超时机制的递归互斥锁
//使用互斥锁需#include<mutex>

//mutex类
//1.加锁lock()
//	互斥锁有锁定和未锁定两种状态
//	如果互斥锁是未锁定状态，调用lock()成员函数的线程会得到互斥锁的所有权，并将其上锁
//	如果互斥锁是锁定状态，调用lock()成员函数的线程就会阻塞等待，直到互斥锁变成未锁定状态
//2.解锁unlock()
//	只有持有锁的线程才能解锁
//3.尝试加锁trylock()
//	如果互斥锁是未锁定状态，则加锁成功，函数返回true
//	如果互斥锁是锁定状态，则加锁失败，函数立即返回false。（线程不会阻塞等待）

//timed_mutex类
//	增加了两个成员函数：
//		bool try_lock_for(时间长度)
//		bool try_lock_until(时间点)


//----------------------------------------------------------demo1
//#include<iostream>
//#include<thread>
//#include<mutex>
//using namespace std;
//
//mutex mtx;	//创建互斥锁，保护共享资源cout对象
//
//void func(const string& str) {
//	for (int i = 1; i <= 20; i++) {
//		mtx.lock();		//申请加锁
//		cout << "子线程" << this_thread::get_id() << "：第" << i << "次输出：" << str << "\t" << this_thread::get_id() << "\t" << i << endl;
//		mtx.unlock();	//用完解锁
//		//this_thread::sleep_for(chrono::seconds(1));
//	}
//}
//
//int main() {
//	thread t1(func, "qwertyui");
//	thread t2(func, "asdfghjk");
//	thread t3(func, "zxcvbnm,");
//	thread t4(func, "12345678");
//
//	t1.join();
//	t2.join();
//	t3.join();
//	t4.join();
//
//
//	return 0;
//}



//recursive_mutex类
//	递归互斥锁允许同一线程多次获得互斥锁，可以解决同一线程多次加锁造成的死锁问题

//---------------------------------------------------------------------------demo2
//#include<iostream>
//#include<mutex>
//using namespace std;
//
//class AA {
//	recursive_mutex m_mutex;
//public:
//	void func1() {
//		m_mutex.lock();
//		cout << "调用了func1()\n";
//		m_mutex.unlock();
//	}
//	void func2() {
//		m_mutex.lock();
//		cout << "调用了func2()\n";
//		func1();		//func2在持有锁的情况下调用func1，func1不可能申请到锁，即产生死锁，除非使用递归锁
//		m_mutex.unlock();
//	}
//};
//int main() {
//	AA aa;
//	aa.func1();
//	aa.func2();
//}


//lock_guard类
//lock_guard是模板类，可以简化互斥锁的使用，也更安全
//template<class Mutex>
//class lock_guard {
//	explicit lock_guard(Mutex& mtx);
//};
//lock_guard在构造函数中加锁，在析构函数中解锁
//lock_guard采用了RAII思想——在类构造函数中分配资源，在析构函数中释放资源，保证资源在离开作用域时自动释放
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int aa = 0;
mutex mtx;

void func() {
	for (int ii = 1; ii <= 1000000; ii++) {
		lock_guard<mutex> mlock(mtx);
		aa++;
		//锁在离开作用域时自动释放
	}
}

int main() {
	thread t1(func);
	thread t2(func);

	t1.join();
	t2.join();

	cout << aa << endl;
}