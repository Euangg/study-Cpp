//windows当中的C语言调用函数，如果没有函数声明编译器不会报错
//可以通过编译（ctrl+F7），但通不过链接

//C++调用函数必须有函数声明，否则无法通过编译



#include<stdio.h>
#pragma comment(lib,"../Debug/X-静态库-2.C-创建静态库.lib")
//指示链接器，链接时检查额外的静态库文件
//int ?Clib_add@@YAHHH@Z(int, int);
//int ?Clib_add@@YAHHH@Z(int, int);
//#pragma comment(lib,"../Debug/X-静态库-3.C++-创建静态库.lib")

int main() {
	int sum=0, sub=0;
	//调用C静态库
	sum = Clib_add(5, 3);
	sub = Clib_sub(5, 3);
	printf("sum=%d,sub=%d", sum, sub);

	//调用C++静态库
	//sum = CPPlib_add(9, 3);
	//sub = CPPlib_sub(9, 3);
	//printf("sum=%d,sub=%d", sum, sub);
	//C无法调用C++库，因为C++的换名机制（换名后的函数不符合C的语法）

	return 0;
}