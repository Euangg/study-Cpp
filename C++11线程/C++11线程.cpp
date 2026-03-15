#include<iostream>
#include<thread>
#include<Windows.h>
using namespace std;


//编程语言级别的支持
//C++编译器自带头文件<thread>，里面封装了thread类
//构造：
//	null：构造一个线程对象，不执行任何任务（不会创建/启动子线程）
//	<class Function,class... Args>(Function&& fx,Args&& args)：创建线程对象，在线程中执行函数fx，args是传给fx的参数
//	拷贝构造函数已删除
//	移动构造函数


void func(int bh, const string& str) {
	for (int ii = 1; ii <= 10; ii++) {
		cout << bh << "：第" << ii << "次输出：" << str << endl;
		Sleep(10);
	}
}

//仿函数创建线程
class fFunction {
public:
	//仿函数的本质是重载()运算符
	void operator()(int bh, const string& str) {
		for (int ii = 1; ii <= 10; ii++) {
			cout << bh << "：第" << ii << "次输出：" << str << endl;
			Sleep(10);
		}
	}
};

//类的普通成员函数创建线程
class cCommonClass {
public:
	int bh_;
public:
	void func(const string& str) {
		for (int ii = 1; ii <= 10; ii++) {
			cout << bh_ << "：第" << ii << "次输出：" << str << endl;
			Sleep(10);
		}
	}
};


int main() {
	thread t1(func, 3, "你好");

	//匿名函数创建线程
	auto f = [](int bh, const string& str) {
		for (int ii = 1; ii <= 10; ii++) {
			cout << bh << "：第" << ii << "次输出：" << str << endl;
			Sleep(10);
		}
	};
	thread t4(f, 888, "匿名函数就是6");


	thread t5(fFunction(), 111, "仿函数哟");

	cCommonClass c;
	c.bh_ = 10;
	thread t6(&cCommonClass::func, &c, "类的普通成员函数来的！！");
	//第一个参数填成员函数的地址，紧跟类（引用或地址都可），这二者将保证出正常的函数
	//随后在跟参数包


	t1.join();
	t4.join();
	t5.join();
	t6.join();
}


//复习匿名函数————
//复习仿函数————
//复习()运算符的重载————
//为什么要删除拷贝构造函数
//学习移动构造函数————
//赋值中，左值、右值、转移的概念————
//noexcept关键字