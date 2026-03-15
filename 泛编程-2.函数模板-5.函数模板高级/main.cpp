//#include<iostream>
//using namespace std;
//
//template<typename T1,typename T2>
//void func(T1 x, T2 y) {
//
//	auto tmp = x + y;
//	cout << "tmp=" << tmp << endl;
//	//如果要返回tmp函数声明&定义处的返回值怎么写？
//}
//
//int func1() {
//
//	cout << "调用int func()" << endl;
//	return 0;
//}
//
//int main() {
//	short a = 5;
//	decltype(a) da;
//	decltype((a)) da2=a;//加括号，是引用了
//	decltype(func1()) ffff;//不会执行func
//	auto pf_auto = func1();//auto会执行func
//	decltype(func1)* pf = func1;
//	pf();
//
//	decltype(++a) ppa=a;//表达式是左值，定义的变量类型是引用
//
//	char b = 3;
//	func(a, b);
//
//
//}

//C++11新标准
//----1).decltype关键字
//语法：
//decltype(expression) var;
//注：decltype只分析表达式，不执行表达式——函数调用也是一种表达式，因此不必担心在使用decltype时执行了函数
//decltype推导规则：（4个步骤）
//1).如果expression是一个没有用括号括起来的标识符(decltype本身的俩括号不算)，则var的类型与该标识符的类型相同，包括const等限定符
//2).如果expression是函数调用，则var的类型与函数的返回值类型相同（函数不能返回void，但可以返回void*）
//3).如果expression是左值（能取地址）（要排除第一种情况）、或者用括号括起来的标识符，那么var的类型是expression的引用
//4).如果上述条件都不满足，则var的类型与expression类型相同
//总的来说decltype要么和表达式类型相同，要么是表达式类型的引用
//如果要多次使用decltype，可以结合typedef和using————可以给推导出来的类型起别名


//----2).函数后置返回类型
//C++11标准中：
//int func(int x,double y);
//等同于：
//auto func(int x,double y)->int;//将函数的返回类型移到了函数声明后面
//这种语法也可以直接用于函数定义:
//auto func(int x,double y)->int{
//			//函数体
//	}
//auto是一个占位符（C++11给auto新增的角色），为函数的返回值占了一个位置

//#include <iostream>
//using namespace std;
//
////这个模板之前写不下去了，因为不知道怎么写返回值
//template<typename T1,typename T2>
//auto func(T1 x, T2 y)->decltype(x + y) {//后面在参数的作用域内，前面不在参数的作用域内
//	decltype(x + y) tmp = x + y;
//	cout << "tmp=" << tmp << endl;
//	return tmp;
//}
//
//int main() {
//	func(3, 6.666);
//}



//C++14的auto关键字：
//C++14标准对函数返回类型推导规则做了优化，函数的返回值可以用auto，不必尾随返回值类型


#include <iostream>
using namespace std;

//这个模板之前写不下去了，因为不知道怎么写返回值
template<typename T1, typename T2>
auto func(T1 x, T2 y) {
	decltype(x + y) tmp = x + y;
	cout << "tmp=" << tmp << endl;
	return tmp;
}

int main() {
	func(3, 6.666);
}