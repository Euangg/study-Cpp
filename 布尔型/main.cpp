#include<iostream>
using namespace std;
//C用0表示假，非0表示真（C++同样适用）
//为了提高代码的可读性，C++新增bool类型，占用1byte内存，用true表示真，false表示假
//bool类型本质上是1字节的整数（char、字符），取值只有1和0
//在程序中，书写的时候可以直接使用true和false，编译器把它们解释为1和0
//用cin输入和cout输出的时候，仍是1和0，不会解释为true和false

int main() {
	bool a = 100, b = false;//如果对bool型赋非0值，将转换为1
	
	cin >> a;
	// 输入1 a的值为1; 输入非0数值 a为1；
	//输入"true" a的值为0；输入字符或字符串 a为0

	cout << "sizeof(a)=" << sizeof(a) << ",sizeof(b)=" << sizeof(b) << endl;
	cout << "a=" << a << ",b=" << b << endl;
	cout << "a+b=" << a + a + a + a + a + +b << endl;

	//找到bool变量b的内存，把里面的数据强制
	char* c = (char*)&b;
	*c = 255;
	cout << "b=" << b << endl;
	//bool类型的本质是unsigned char 
	//true和false是C++在语法上的处理，上面的几行会绕过C++的解释
}