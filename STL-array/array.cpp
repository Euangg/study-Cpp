//使用 std::array 可以避免传统C风格数组在函数参数传递中可能出现的类型错误，因为 std::array 会保持其大小信息。
//高效性：std::array 是一个轻量级的封装，它没有额外的内存开销（与传统数组相同），并且在大多数情况下，它的操作性能与传统数组相当。
//这是因为 std::array 通常只包含一个指向数组的指针和一个表示数组大小的编译时常量。
#include<algorithm>
#include<numeric>

#include<array>
#include<iostream>
using namespace std;

//array的意义
//1.硬化静态数组
void test1() {
	array<int, 3>a1{ 1,2,3 };//必须在声明时就指定大小
	int a2[]{ 1,2,3 };//原生数组可以自动推导大小

	int size = 5;
	//array<int, size>a3;//不行，必须常量
	int* a4 = new int[size];//原生可以用变量分配堆内存
	array<int, 5>* a5 = new array<int, 5>;//分配堆内存也必须使用常量！

	//优点：清晰
	//缺点：生硬
}
//2.STL容器外观，可以用基于范围的for循环
void test2() {
	int* a = new int[5];//原生数组退化指针，不能用范围for
	array<int, 5>* a2 = new array<int, 5>{1, 2, 3, 4, 5};
	for (auto& d : *a2)cout << d << endl;
	//注：太硬了，真的没有必要用array的退化指针
}
//3.防止越界访问
void test3() {
	array<int, 10>arr{};
	cout << arr[10] << endl;//越界访问，运行时报错
}
//特性
void pro1() {
	array<int, 10>arr1;//初始化为脏内存
	array<int, 10>arr2{};//初始化为全0
}

void Test0() {
	//创建array
	array<int, 10> a = { 11,22,33,44 };

	auto i = a.begin();
	for (; i != a.end(); i++) {
		cout << *i << endl;
	}
	cout << endl;

	a.back() = 9999999;
	a[a.size() - 2] = 42;
	i = a.begin();
	for (; i != a.end(); i++) {
		cout << *i << endl;
	}
	cout << endl;

	cout << "sum:" << accumulate(a.begin(), a.end(), 0) << endl;

	/*transform(a.begin(), a.end(), a.begin(), negate<int>());
	i = a.begin();
	for (; i != a.end(); i++) {
		cout << *i << endl;
	}
	cout << endl;*/
}

void Test1() {
	//2.创建
	//array<int, 10>x;//纯随机
	array<int, 10>x{};//0

	std::cout << "sizeof(x):" << sizeof(x) << std::endl;//40

	std::cout << "&x:" << &x << std::endl;
	std::cout << "&x[0]:" << &x[0] << std::endl;//二者一样，效果同C数组

	//下标
	for (int i = 0; i < x.size(); i++) {
		std::cout << x[i] << "\t";
	}std::cout << std::endl;
	//迭代器
	for (auto it = x.begin(); it != x.end(); it++) {
		std::cout << *it << "\t";
	}std::cout << std::endl;
	array<int, 10>::iterator iter;
	for (iter = x.begin(); iter != x.end(); iter++) {
		std::cout << *iter << "\t";
	}std::cout << std::endl;
}


//成员
void Test4() {
	array<int, 10>arr{};
	cout << arr.size() << endl;
	cout << arr.max_size() << endl;
	arr.empty();
	cout << arr.size() << endl;
	cout << arr.max_size() << endl;
	//固定大小，一直是10
}

int main() {
	test3();
}