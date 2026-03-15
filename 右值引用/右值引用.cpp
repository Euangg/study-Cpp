//所有的值，不是左值就是右值
//左值：表达式结束后依然存在的持久化元素
//右值：表达式结束后就不再存在的临时对象

//区分： 
//有名字（标识符）的都是左值，右值没有名字
//能取地址的表达式为左值，不能取地址的为右值
//表达式的结果是否有固定的内存地址
//右值：字面量、临时对象（函数返回临时对象）、算术表达式

//C++11扩展了左右值的概念
//泛左值：有身份的表达式
//  左值：有身份且不能移动的表达式
//  将亡值：有身份且可以移动的表达式
//右值：可以移动的表达式
//  纯右值：
//	  非引用返回的临时变量：函数以值的方式返回 是纯右值
//	  运算表达式产生的结果
//	  字面常量（C风格字符串不算，它是地址）
//  将亡值：
//	  与右值引用相关的表达式

//右值引用的意义
//1.延长临时对象生命周期
//2.允许资源从右值中移走

#include<iostream>
using namespace std;

int func() { int a = 10; return a; }
void test1(){
	int ii = 3;		//ii是左值，3是右值
	int jj = ii + 8;//jj是左值，ii+8是右值
	int xx = func();//xx是左值，func()的返回值是右值
}

struct MyArray {
	int* data;
	size_t size;

	MyArray(size_t p_size = 0) :size(p_size) {data = size ? new int[size] : nullptr;}
	MyArray(MyArray& target) :size(target.size) { //深拷贝
		cout << "深拷贝函数" << endl;
		data = size ? new int[size] : nullptr;
		std::copy(target.data, target.data + size, data);
	}
	~MyArray() {
		cout << "析构函数" << endl;
		delete[] data; 
	}

	/////////////////////////////移动语义
	MyArray(MyArray&& target)noexcept :data(target.data), size(target.size) {target.data = nullptr; target.size = 0;}
};
//C++98/03之前的数据转移——拷贝
void test2() {
	MyArray arr(5);
	MyArray arr2 = arr;

	cout << arr2.size << endl;
	for (int o = 0; o < arr2.size; ++o)cout << arr2.data[o] << ",";
	cout << endl;

	arr2.data[1] = 99;
	for (int o = 0; o < arr.size; ++o)cout << arr.data[o] << ",";
	cout << endl;
}
//C++11转移数据——右值引用
void test3() {
	MyArray arr(5);
	MyArray arr2 = std::move(arr);//标记调用另一种拷贝构造函数

	cout << arr2.size << endl;
	for (int o = 0; o < arr2.size; ++o)cout << arr2.data[o] << ",";
	cout << endl;
}

//很多情况下，表现为指针的赋值和置空
//核心是内存所有权的转移
//增加了一种&&参数类型，增加函数重载的选择

//移动语义的意义：
//清晰表达转移所有权的意图


//左值引用（引用）
//语法：数据类型& 变量名=左值;
//右值引用
//语法：数据类型&& 变量名=右值;
void func2(int& a) { };
void func3(const int& a) { };
void test4() {
	int&& a = 3;

	int b = 7;		//b是左值
	int&& c = b + 5;//b+5是右值
	//int&& c2 = b;//报错：无法将右值引用绑定到左值
	cout << c << endl;
	c++;
	cout << c << endl;


	int&& d = func();//func()返回值为右值

	//右值有了名字以后就成了左值
	//int&& e = d; 报错，d是右值引用，右值引用是左值
	int& e = d;//左值引用成功


	//特殊的左值引用
	//int& f = 1;报错，要求必须为左值
	const int& f = 1;//常量左值引用可以赋右值
	//实际运用——函数传参	如果参数加&表示引用，那么传参只能用左值
	//						如果在前面加上const，就又能传右值（效果上又回到了普通传值，普通传值不能改变原传入，const直接不允许）
	//func2(5);报错，要求为左值
	func3(5);//可以，虽然不能修改参数了，但是可以传右值了
}

int main() {
	test3();
}



