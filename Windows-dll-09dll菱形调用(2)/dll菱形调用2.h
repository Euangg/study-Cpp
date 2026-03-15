#pragma once
//通常使用预编译开关切换类的导入导出定义
#ifdef DLL_EXPORTS_USE2
#define DLL_EXECUTE_USE2 _declspec(dllexport)
#else
#define DLL_EXECUTE_USE2 _declspec(dllimport)
#endif // DLLCLASS_EXPORTS


DLL_EXECUTE_USE2 void AddVar2();