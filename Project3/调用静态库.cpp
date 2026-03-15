//C++调用函数，函数必须要有声明，否则无法通过编译（与C不同）
//这就是为什么C++调用库时要包含头文件（一般与库同名），里面存放的是库函数的声明
//因为C++存在换名机制，与C不同，但又同时要能使用C的静态库，这是C++调用库时需要函数声明的原因（声明时区分是C静态库的函数还是C++静态库的函数）

#include<iostream>
using namespace std;

int CPPlib_add(int, int);
int CPPlib_sub(int, int);
//有声明则可以通过编译，但没添加库则无法通过接下来的链接（通过编译器）
#pragma comment(lib,"../Debug/X-静态库-3.C++-创建静态库.lib")
//指定库，链接时可以进库找相关函数代码（链接器指令，通过链接器）

extern "C" int Clib_add(int, int);
extern "C" int Clib_sub(int, int);
//调用C静态库，仍然需要函数声明
//extern "C"以C的方式编链接此函数（函数不会被换名）
//C++的方式编译链接函数，函数会被按一定规则换名
#pragma comment(lib,"../Debug/X-静态库-2.C-创建静态库.lib")//C静态库中的函数不会换名


int main() {
	//C++调C++静态库
	int sum = CPPlib_add(5, 4);
	int sub = CPPlib_sub(5, 4);
	cout << "sum=" << sum << endl << "sub=" << sub << endl;
	//C++调C静态库
	sum = Clib_add(5, 3);//?Clib_add@@YAHHH@Z
	sub = Clib_sub(5, 3);//?Clib_sub@@YAHHH@Z
	//C++编译器换名机制（Linux与Windows换名规则不一样）
	//C++编译器编译链接时会将其代码内所有函数的名字按一定规则更换
	cout << "sum=" << sum << endl << "sub=" << sub << endl;
}