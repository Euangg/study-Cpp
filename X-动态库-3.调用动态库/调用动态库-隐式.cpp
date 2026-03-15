#include<iostream>
using namespace std;

_declspec(dllimport) int CPPdll_add(int add1, int add2);
//_declspec(dllimport) int CPPdll_sub(int sub1, int sub2);
//_declspec(dllimport) int CPPdll_mul(int mul1, int mul2);
//_declspec(dllimport)告知编译器，函数从dll导入
#pragma comment(lib,"../Debug/X-动态库-2.创建动态库.lib")
//指示链接器，从哪里获取编号
// 参考静态库的原理，链接器如何确定是从lib中获取源码还是编号？链接器从lib中查找函数名（无论哪种lib都会有），有源码抓源码
// 有编号抓编号和配套dll文件名，如果是编号则打开配套dll根据编号调用
//微软规定，不可以直接到dll中获取内容。只能通过lib间接获取dll内容
int main() {
	int sum = CPPdll_add(5, 4);//0（编号）->“X-动态库-2.创建动态库.dll” 中的0号函数
	//int sub = CPPdll_sub(5, 4);//1（编号）->“X-动态库-2.创建动态库.dll” 中的1号函数
	//int mul = CPPdll_mul(5, 4);//2（编号）->“X-动态库-2.创建动态库.dll” 中的2号函数
	cout << "sum=" << sum << endl;
	//cout << "sub=" << sub << endl;
	//cout << ",mul=" << mul << endl;
}


//创建动态库部分改用模块定义文件导出函数后，该项目失效