//1.可以为类的成员函数创建模板，但不能是虚函数和析构函数————析构函数没有参数
//#include<iostream>
//using namespace std;
//
//class CGirl {
//public:
//	template<typename T>
//	CGirl(T a) {
//		cout << "a=" << a << endl;
//	}
//};
//
//int main() {
//	CGirl g(67);
//
//}

//2.使用函数模板时，必须明确数据类型，确保实参与函数模板能匹配上
//#include<iostream>
//using namespace std;
//
//template<typename T>
//void Swap() {
//}
//
//int main() {
//	int a = 10;
//	int b = 30;
//	Swap<int>();//如果，没东西可推导，必须要显式指定
//
//}

//3.使用函数模板时，推导的数据类型必须适应函数模板中的代码
//#include<iostream>
//using namespace std;
//
//template<typename T>
//T Add(T a, T b) {
//	return a + b;
//}
//
//
//class A{};
//
//
//int main() {
//	int a = 10;
//	int b = 20;
//	int c = Add(a, b);
//	cout << "c=" << c << endl;
//
//	A a1, a2;
//	A a3 = Add(a1, a2);//可以推导，但是内部用到的+运算符在class A中没有重载（定义）
//	//即，这种数据类型不适应+运算
//	//函数模板可以接受任意数据类型，但函数中的代码不一定适应任意数据类型
//	//如果不适应，编译器会报错
//}



//4.使用函数模板时，如果是自动类型推导，不会发生隐式类型转换
//	如果显式指定了推导类型，可以发生隐式类型转换
//#include<iostream>
//using namespace std;
//
//template<typename T>
//T Add(T a, T b) {
//	return a + b;
//}
//
//int main() {
//	char a = 10;
//	char b = 20;
//	int c = Add<int>(a, b);//两个char被转换为两个int
//	cout << "c=" << c << endl;
//	int d = Add<char>(c, a);//不统一的参数类型被统一成指定推导类型
//	cout << "d=" << d << endl;
//
//}

//5.函数模板支持多个通用数据类型的参数
//#include<iostream>
//using namespace std;
//
//template<typename T1,typename T2>
//void show(T1 a, T2 b) {
//	cout << a << "," << b << endl;
//}
//
//int main() {
//	short a = 90;
//	string b = "hello world";
//	show(a, b);
//	show(b, a);
//	show(a, a);//虽然模板给了两种通用类型，但这两种通用类型能被推导成同一种数据类型
//}


//6.函数模板支持重载，可以有非通用数据类型的参数
#include<iostream>
using namespace std;

template<typename T>
void func(T a) {
	cout << "func(T a)" << endl;
}

template<typename T1,typename T2>
void func(T1 a, T2 b) {
	cout << "func(T1 a, T2 b)" << endl;
}

template<typename T1,typename T2>
void func(T1 a, T2 b, int c) {
	cout << "func(T1 a, T2 b, int c)" << endl;
}

int main() {
	func(1);
	func(12, 2.332);
	func(12, 23, 432);
}