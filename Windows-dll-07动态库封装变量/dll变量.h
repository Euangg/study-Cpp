#pragma once

//通常使用预编译开关切换类的导入导出定义
//宏开关，保证开发者与用户使用同一个头文件
#ifdef DLL_EXPORTS_VAR
#define DLL_EXECUTE_VAR _declspec(dllexport)
#else
#define DLL_EXECUTE_VAR _declspec(dllimport)
#endif // DLLCLASS_EXPORTS

DLL_EXECUTE_VAR extern int a;