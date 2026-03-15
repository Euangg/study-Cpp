//共同体（共用体、联合体）
#include<iostream>
using namespace std;

union udata{
	int a;
	double b;
	char c[25];
};
//共同体占用内存的大小是它最大的成员占用内存的大小，且补内存对齐（win10中对齐大小为8字节的整数倍）
void pro_size() {
	udata data1;
	cout << "sizeof(data1)=" << sizeof(data1) << endl;//32（最大的是char c[25]，25byte，对齐到32）
	
	cout << "&data1.a:" << (void*)&data1.a << endl;
	cout << "&data1.b:" << (void*)&data1.b << endl;
	cout << "&data1.c:" << (void*)&data1.c << endl;
	//匿名共同体成员全部可.访问，但用同一块内存
}

//语法：匿名共同体
union {
	int a;
	double b;
	char c[25];
}data2;

void test1() {
	cout << data2.a << endl;
}

//语法：匿名共同体嵌入结构体
struct st_girl{
	int no;
	
	union {
		int a;
		double b;
		char c[21];
	};
};
void test2() {
	st_girl girl;
	//匿名共同体成员全部可当作结构体成员用，但用同一块内存
	cout << "&girl.a:" << (void*)&girl.a << endl;
	cout << "&girl.b:" << (void*)&girl.b << endl;
	cout << "&girl.c:" << (void*)&girl.c << endl;
}

int main() {
	//pro_size();
	test1();
}

//应用场景：
//用于回调函数的参数（相当于支持多种类型）