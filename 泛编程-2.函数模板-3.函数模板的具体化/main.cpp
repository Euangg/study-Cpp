//可以提供具体化的函数定义，当编译器找到与函数调用匹配的具体化定义时，将使用该定义，不再寻找模板
//这种操作叫做函数模板的具体化（特例化、特化）————函数模板通用版本之外的一个特殊版本
//语法：
//template<> 模板函数返回值 模板函数名(参数列表) {
//	//具体化函数定义
//}

//#include<iostream>
//using namespace std;
//
//class CGirl {
//public:
//	int m_bh;
//	string m_name;
//	int m_rank;
//
//};
//
//
////函数模板声明
//template<typename T>
//void Swap(T& a, T& b);
////{
////	T tmp = a;
////	a = b;
////	b = tmp;
////	cout << "调用了Swap(T& a,T& b)\n";
////}
//
//template<> void Swap<CGirl>(CGirl& g1, CGirl& g2);
////{
//////template<> void Swap(CGirl& g1, CGirl& g2) {//两种方法一样
////	int tmp = g1.m_rank;
////	g1.m_rank = g2.m_rank;
////	g2.m_rank = tmp;
////	cout << "调用了具体化的Swap(CGirl& g1, CGirl& g2)\n";
////
////}
//
//int main() {
//	int a = 10, b = 20;
//	Swap(a, b);
//	cout << "a=" << a << ",b=" << b << endl;
//
//	CGirl g1, g2;
//	g1.m_rank = 1;
//	g2.m_rank = 2;
//	Swap(g1, g2);
//
//}
//
//
////函数模板定义
//template<typename T>
//void Swap(T& a, T& b) {
//	T tmp = a;
//	a = b;
//	b = tmp;
//	cout << "调用了Swap(T& a,T& b)\n";
//}
//
//template<> void Swap<CGirl>(CGirl& g1, CGirl& g2) {
//	//template<> void Swap(CGirl& g1, CGirl& g2) {//两种方法一样
//	int tmp = g1.m_rank;
//	g1.m_rank = g2.m_rank;
//	g2.m_rank = tmp;
//	cout << "调用了具体化的Swap(CGirl& g1, CGirl& g2)\n";
//
//}


//对于给定的函数名，可以有普通函数、函数模板和具体化的函数模板，以及它们的重载版本
//编译器使用函数的规则：
//1)普通函数优先于模板，具体化模板优先于常规模板
//2)如果希望使用函数模板，可以用空模板参数强制使用函数模板
//3)如果函数模板能产生更好的匹配，将优先于非模板函数


#include<iostream>
using namespace std;

void Swap(int a, int b) {
	cout << "调用普通函数" << endl;
}

template<typename T>
void Swap(T a, T b) {
	cout << "调用通用类型函数模板" << endl;
}

template<>
void Swap(int a, int b) {
	cout << "调用具体化函数模板" << endl;
}

int main() {

	Swap(1, 2);//普通函数》具体化函数模板》通用类型函数模板

	Swap<>(1, 2);//具体化函数模板》通用类型函数模板

	Swap('c', 's');//模板产生更好的匹配（即不需要类型转换）:模板》普通函数
}