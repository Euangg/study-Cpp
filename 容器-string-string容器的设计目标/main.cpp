//string是以字节为最小存储单元的动态容器




#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int main() {
	char cc[8];//在栈上分配8byte的内存空间

	//把cc内存空间用于字符串
	strcpy(cc, "adsf");
	cout << "cc=" << cc << endl;

	//把cc内存空间用于int型整数
	int* a, * b;
	a = (int*)cc;//前4字节
	b = (int*)(cc + 4);//后4字节
	*a = 12345;
	*b = 54321;
	cout << "*a=" << *a << endl;
	cout << "*b=" << *b << endl;

	//把cc的内存空间用于double
	double* d = (double*)cc;
	*d = 12345.67;
	cout << "*d=" << *d << endl;

	//把cc的内存空间用于结构体
	struct stt {
		int a;
		char b[4];
	}*st;
	st = (struct stt*)cc;
	st->a = 38;
	strcpy(st->b, "abc");
	cout << "st->a=" << st->a << endl;
	cout << "st->b=" << st->b << endl;

	string str1;
	cout << "str1.capacity()=" << str1.capacity() << endl;
	cout << "str1.size()=" << str1.size() << endl;
	str1.append("x");
	cout << "str1:" << str1 << endl;
	cout << "str1.capacity()=" << str1.capacity() << endl;
	cout << "str1.size()=" << str1.size() << endl;
	str1.append("qewrtyuipioasdfgjhk");
	cout << "str1:" << str1 << endl;
	cout << "str1.capacity()=" << str1.capacity() << endl;
	cout << "str1.size()=" << str1.size() << endl;

	return 0;
}