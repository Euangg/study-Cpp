

//移动构造函数
// 语法：类名(类名&& 源对象)
//移动赋值函数
// 语法：类名& operator=(类名&&)


#include<iostream>
using namespace std;
class A {
	int num_;
	int* pnum_;
public:
	A() { cout << "调用无参构造" << endl; };

	A(A& a) { cout << "调用拷贝构造" << endl; };
	A(A&& a) { cout << "调用移动构造" << endl; };

	A& operator =(A& a) { cout << "调用赋值函数" << endl; };
	A& operator =(A&& a) { cout << "调用移动赋值" << endl; return *this; };
};
int main() {
	auto f = [] {
		A a; //无参构造
		return a; };
	A a1 = f();//移动构造
	cout << "-------------------" << endl;
	a1 = f();//移动构造+移动赋值

	cout << "-------------------" << endl;
	A a2 = move(a1);//移动构造，move会将左值转化为右值
}