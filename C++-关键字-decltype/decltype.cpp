//declare type 声明类型
//decltype是操作符，用于查询表达式的数据类型

#include<iostream>
using namespace std;

template<typename T1,typename T2>
auto func(T1 x, T2 y) {
	auto temp = x + y;
	return temp;
}
void test1() {
	double a = 5.5;
	int b = 3;
	cout << func(a, b) << endl;
}
//标准，函数返回类型后置
template<typename T1, typename T2>
auto func2(T1 x, T2 y)->decltype(x + y) {
	auto temp = x + y;
	return temp;
}
//C++14

void test2() {
	char a = 'a';
	short b = 9;
	decltype(a + b) c = a + b;//decltype分析表达式，不会计算执行表达式
	//函数也是一种表达式，因此不用担心使用decltype时执行了函数：
	decltype(++a) da = a;//左值是引用
	decltype((a)) da2 = a;//加括号分析出来也是引用
	cout << a << endl;//还是'a'
}

int func() {
	cout << "func()被调用" << endl;
	return 0;
}
void test3() {
	auto f = func();//用auto推导会执行表达式
}

int main() {
	//test2();
	test3();
}