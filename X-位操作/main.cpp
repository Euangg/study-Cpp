#include<Windows.h>
#include<iostream>
using namespace std;

//左移运算符
void test1() {
	unsigned char a = 8;//0000 1000
	cout << "a<<1=" << (a << 1) << endl;	//0001 0000 (16)
	cout << "a=" << (int)a << endl;//a=8，不会修改a的值
	cout << "a<<2=" << (a << 2) << endl;	//0010 0000 (32)
	cout << "a<<3=" << (a << 3) << endl;	//0100 0000 (64)
	cout << "a<<4=" << (a << 4) << endl;	//1000 0000 (128)

	//移位可以超越原数据类型的位数大小限制
	cout << "a<<5=" << (a << 5) << endl;	//0001 0000 0000 (256)
	cout << "a<<6=" << (a << 6) << endl;	//0010 0000 0000 (512)
	cout << "a<<7=" << (a << 7) << endl;	//0100 0000 0000 (1024)
	cout << "a<<8=" << (a << 8) << endl;	//1000 0000 0000 (2048)
	cout << "a<<9=" << (a << 9) << endl;	//0001 0000 0000 0000 (4096)
	cout << "a<<10=" << (a << 10) << endl;	//0010 0000 0000 0000 (8192)
	cout << "a<<11=" << (a << 11) << endl;	//0100 0000 0000 0000 (16384)
	cout << "a<<12=" << (a << 12) << endl;	//1000 0000 0000 0000 (32768)
	cout << "a<<13=" << (a << 13) << endl;	//0001 0000 0000 0000 0000 (65536)
	
}

void test2() {
	unsigned char a = 8;//0000 1000
	for (int i = 1; i < 50; i++) {
		cout << "a<<" << i << "=" << (a << i) << endl;
	}
}
//右移运算符
void test3() {
	unsigned char a = 8;//0000 1000
	for (int i = 1; i < 50; i++) {
		cout << "a>>" << i << "=" << (a >> i) << endl;
	}
}

void test4() {
	for (int i = 0; i < 8; i++) {
		cout << "(1u<<" << i << ")=" << (1u << i) << endl;
	}
	for (int i = 0; i < 8; i++) {
		cout << "(1u<<" << i << ")-1u=" << (1u << i)-1u << endl;
	}

}

//实例：
//针对16位short位操作
#define GetBit(v,n)( ((v)&((UINT16)1<<(n)))>>n )//取v的第n位，返回按位与运算后的值（不会改变v的值）
void test() {
	short val = 255;
	//cout << "调用GetBit后val为" << val << endl;
	for (int i = 0; i < 16; i++) {
		short temp_val1 = GetBit(val, i);
		cout << "val的第" << i << "位为" << temp_val1 << endl;
	}
}


int main(void) {
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}