#include<Windows.h>
#include"../../../../../../Program Files/Python39/include/Python.h"
#pragma comment(lib,"python39.lib")//包含库，需要移动到用户路径，访问系统路径需要管理员权限

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	//1.初始化Python接口
	Py_Initialize();
	if (!Py_IsInitialized()) {
		
		return 1;
	}

	//2.运行
	PyObject* obj = Py_BuildValue("s", "C:/Users/you/source/repos/CppChengZhang/X-Cpp_Python/CppWinPyTest.py");
	FILE* fp = _Py_fopen_obj(obj, "r+");

	if (!fp) {
		return 1;
	}
	PyRun_SimpleFile(fp, "xxxxxxxxxx");

	//3.结束，回收资源
	Py_Finalize();

	return 0;
}