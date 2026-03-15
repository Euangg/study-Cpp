#include<iostream>
#include<vector>
using namespace std;

//遍历容器范围
void test() {
	vector<int> v1 = { 1,2,3,4,5,6,7,8,9,10 };

	for (auto it = v1.begin(); it != v1.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	//对于一个有范围的集合来说，在程序代码中指定循环范围有时候是多余的，还可能犯错误
	//C++11中引入了基于范围的for循环
	//语法：
	//for(迭代的变量类型 迭代的变量名:迭代的范围){/*循环体*/}
	//迭代的范围：可填数组名、容器名、统一初始化列表或者其他可迭代对象

	for (int val : v1) {
		cout << val << " ";
	}
	cout << endl;
}

//遍历栈数组
void test2() {
	//遍历数组
	int cArry1[] = { 1,2,3,4,5,6,7,8,9,10 };
	for (int val : cArry1)
		cout << val << " ";
	cout << endl;
}
//遍历堆数组
void test3() {
	int* arr = new int[5]{ 1,2,3,4,5 };
	//for (auto& i : *arr) {}//不行
}

//遍历统一初始化列表
void test4() {
	//遍历统一初始化列表
	for (int val : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 })
		cout << val << " ";
	cout << endl;
}

int main() {
	
}
//注：	1.数组名传入函数后，已退化成指针，不能作为容器名
//		2.如果容器中的元素是结构体或类，迭代器变量应声明为引用（可以大大提高访问效率），加const约束表示只读
//		3.注意迭代器失效的问题