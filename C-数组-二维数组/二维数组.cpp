#include<iostream>
using namespace std;
//二维数组创建，下标的意义
void test() {
	int a[][3] = {
		{1,2,3}
	};

	/*int b[3][] = {
		{1,2,3}
	};*///错误

	//第一个[]：元素数量
	//第二个[]：子元素大小
}

//二维数组访问，下标的意义
void test2() {
	int a[][3]{
		{1,2,3},
		{4,5,6}
	};
	cout << a[1][1] << endl;
	//第一个[]：元素索引
	//第二个[]：子元素索引

	cout << *(a[0]) << endl;//输出1
	cout << *(a[1]) << endl;//输出4
	//单独[]，仍然是元素索引，不能越界
}

int main() {
	test2();
}