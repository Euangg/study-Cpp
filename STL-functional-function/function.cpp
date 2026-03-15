#include<functional>
#include<iostream>
using namespace std;
void func1() { cout << "func1-普通函数" << endl; }
auto func2 = []() { cout << "func2-lambda函数" << endl; };
struct sss {
	void func3() { cout << "func3-成员函数" << endl; }
};

int main() {
	function<void()>f{};
	//f();//空调用会报错

	f = func1;
	f();
	f = func2;
	f();

	sss t;

	f = [&t] {t.func3(); };//通过lambda绑定成员函数，最优雅、简洁、现代
	f();

	f = bind(&sss::func3, &t);//通过bind绑定成员函数
	f();

	auto f2 = mem_fun(&sss::func3);//通过mem_fun绑定成员函数（类型擦除不完全）
	f2(&t);
}


//function，用纯库代码实现了革命性的抽象，没有依赖编译器的特殊支持