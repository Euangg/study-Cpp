#pragma once
//动态库中封装类需要有头文件提交给使用者
//头文件内存放类声明

#ifndef _动态库中封装类_H
#define _动态库中封装类_H

//通常使用预编译开关切换类的导入导出定义
//宏开关，保证开发者与用户使用同一个头文件
#ifdef DLLCLASS_EXPORTS
#define EXT_CLASS _declspec(dllexport)
#else
#define EXT_CLASS _declspec(dllimport)
#endif // DLLCLASS_EXPORTS


class EXT_CLASS CMath {
	//_declspec(dllexport)本质上导出的是类的成员函数的相对地址
public:
	//头文件内只声明，不实现
	int Add(int add1, int add2);
	int Sub(int sub1, int sub2);
};

#endif // !_动态库中封装类_H
