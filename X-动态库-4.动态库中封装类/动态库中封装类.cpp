//动态库中封装类
//在类名称前加_declspec(dllexport)定义（声明导出）
//可以模块定义文件导出，但一般不这么用，要充分了解换名规则
//导出类本质上是导出类的成员函数的地址

#define DLLCLASS_EXPORTS //开发者宏标识开关
#include"动态库中封装类.h"
int CMath::Add(int add1, int add2) {
	return add1 + add2;
}

int CMath::Sub(int sub1, int sub2) {
	return sub1 - sub2;
}



