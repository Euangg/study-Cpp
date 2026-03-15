//dll是最终文件，但和dll会配套生成lib

//声明导出（导出函数的地址）
//在要导出的函数定义前加_declspec(dllexport)
//有了这个后，会配套生成lib，里面存放导出的函数信息（地址）

//dll文件包含两部分：
//1.文件头：函数地址（列表，每条表目存放函数信息：编号、函数名（C++会换名）、函数地址
//2.正文：函数实现（源码）
//配套的lib：（与传统静态库相比，后缀名一样，里面存放的内容完全不一样）
// 1.配套的dll文件名
// 2.列表，每条表目存放函数信息：函数名、编号（与dll中的编号一致）


_declspec(dllexport) int CPPdll_add(int add1, int add2) {
	return add1 + add2;
}
//声明导出，导出的函数其函数名过换名规则



int CPPdll_sub(int sub1, int sub2) {
	return sub1 - sub2;
}
int CPPdll_mul(int mul1, int mul2) {
	return mul1 * mul2;
}
//使用模块定义文件.def导出，导出的函数不过换名规则



