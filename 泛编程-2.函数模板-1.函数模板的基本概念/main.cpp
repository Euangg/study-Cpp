//函数模板是通用的函数描述
//编译的时候，编译器推导实参的数据类型，根据实参的数据类型和函数模板，生成该函数的定义
//生成函数定义的过程被称为实例化



#include<iostream>
using namespace std;


//void Swap(int& a, int& b) {//交换两个int类型
//	int temp = a;
//	a = b;
//	b = temp;
//}
//void Swap(double& a, double& b) {//交换两个double类型
//	double temp = a;
//	a = b;
//	b = temp;
//}


//创建交换两个变量的函数模板
template <typename T>//区分函数和函数模板的关键
void Swap(T& a, T& b) {
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

int main() {

	int a = 10, b = 30;
	Swap(a, b);
	cout << "a=" << a << ",b=" << b << endl;
	double c = 12.233, d = 98.21381;
	Swap(c, d);
	cout << "c=" << c << ",d=" << d << endl;
	string e = "hello", f = "world";
	Swap<string>(e, f);//手动指定推导类型
	cout << "e=" << e << ",f=" << f << endl;
}


//在C++98添加关键字typename之前，C++使用关键字class来创建模板
//考虑到向后兼容，函数模板应该使用typename，而不是class