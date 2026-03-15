//constexpr要求在【编译期】就可以确定其值。常量表达式。const expression
//极大提高效率和表达。
//const有两层含义：变量只读，常量表达。constexpr取const的常量表达含义

#include<iostream>
using namespace std;

//const int Getlen(int a, int b) { return a + b; };//不被数组初始化认可的常量
constexpr int Getlen(int a, int b) { return a + b; };//
void test0() {
	int array[Getlen(1, 2)];//参数不仅是int，还是constexpr int
	cout << sizeof(array) << endl;//12

	int a = 9;
	int b = time(0);
	//constexpr int arraysize = Getlen(a, b);//导出要求constexpr，要求传入的参数也是constexpr
	int x = Getlen(a, b);//导出要求constexpr可以根据导出要求弹性变化
	cout << x << endl;
}

void test1() {
	const int size = 10;
	int array[size];//const量认可的
}

//还能修饰构造函数，保证传递给该构造函数的所有参数都是constexpr
//那么产生的对象的所有成员都是constexpr，该对象就是constexpr对象
struct StEx {
	int a;
	//注意onstexpr构造函数的函数体必须为空，所有成员变量的初始化都放到初始化列表中:
	constexpr StEx() :a(5) { a = 99; };
};
void test2() {
	constexpr StEx st;
	cout << st.a << endl;
}


int main() {
	//test0();
	//test1();
	test2();
}