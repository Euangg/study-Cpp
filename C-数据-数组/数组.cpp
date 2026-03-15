#include<Windows.h>
#include<iostream>
#include<string.h>
using namespace std;

void test() {
	int a[5]{ 5 };//只有第一个值是5
	int b[5]={ 5 };//只有第一个值是5
}

//拷贝数组
void test2() {
	int a[3] = { 4,5,6 };
	int* _b = new int(3);
	memcpy(_b, a, sizeof(a));//不要除sizeof(int)
	for (int i = 0; i < 3; i++)std::cout << *(_b + i) << std::endl;
}

//数组逻辑大小
void test3() {
	int a[] = { 1,2,5,7,88,5,5, };
	int size = ARRAYSIZE(a);
	cout << size << endl;

	//数组退化指针
	/*int* p = a;
	int size2 = ARRAYSIZE(p);
	cout << size2 << endl;*/
}

int main() {
	//test();
	//test2();
	test3();
}