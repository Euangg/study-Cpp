#include<iostream>
using namespace std;

//unsigned 4byte 翻译值：0~4294967295
//相当于 unsigned int    UINT

int main(int argc, char* argv[]) {
	unsigned us = 0;
	
	cout << "sizeof(unsigned)=" << sizeof(unsigned) << endl;
	//for (; us < UINT32_MAX; us++);
	us = UINT32_MAX;
	cout << us << endl;
	us++;
	cout << us << endl;

	//数值表达形式
	int mode10 = 988129;//十进制
	int mode2 = 0b01010;//二进制
	int mode8 = 0567332;//八进制
	int mode16 = 0x172a;//十六进制

}

//1字节
char;

//2字节
short; wchar_t;
//4字节
int;
unsigned; size_t;