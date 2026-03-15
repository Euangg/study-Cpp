#include"../../../../../../Program Files/Python39/include/Python.h"
#pragma comment(lib,"python39_d.lib")//包含库，需要移动到用户路径，访问系统路径需要管理员权限

//1.运行单行脚本代码
//int main() {
//	Py_Initialize();//初始化
//	PyRun_SimpleString("print('hello python')");//执行单条语句
//	Py_Finalize();//释放资源
//	return 0;
//}

//2.导入函数并运行
//#include<iostream>
//using namespace std;
//int main() {
//	//1.初始化Python接口
//	Py_Initialize();
//	if (!Py_IsInitialized()) {
//		cout << "python init failed" << endl;
//		return 1;
//	}
//	//2.初始化python系统文件路径
//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('C:/Users/you/source/repos/CppChengZhang/X-Cpp_Python')");
//
//	//3.调用python文件名，不用写后缀
//	PyObject* module = PyImport_ImportModule("testFunc");
//	if (module == nullptr) {
//		cout << "未找到模块: testFunc" << endl;
//		return 1;
//	}
//
//	//4.获取函数对象
//	//PyObject* func = PyObject_GetAttrString(module, "say");
//	PyObject* func = PyObject_GetAttrString(module, "add");
//
//
//	if (!func || !PyCallable_Check(func)) {
//		cout << "未找到函数: add" << endl;
//		return 1;
//	}
//
//
//	//5.调用函数
//	//传递参数，函数调用的参数传递均是以组元的形式打包的
//	PyObject* args = PyTuple_New(2);//2表示两个参数
//	PyTuple_SetItem(args, 0, Py_BuildValue("i", 1));//"i"表示int
//	PyTuple_SetItem(args, 1, Py_BuildValue("i", 2));
//
//	//PyObject_CallObject(func, nullptr);
//	PyObject* ret = PyObject_CallObject(func, args);
//
//	//接收返回值
//	int result = 0;
//	PyArg_Parse(ret, "i", &result);
//	cout << "CPP得到结果：" << result << endl;
//
//
//	cout << "调用成功" << endl;
//	//6.结束，回收资源
//	Py_Finalize();
//
//	return 0;
//}

//3.导入py类
//#include<iostream>
//using namespace std;
//int main() {
//	//s1.初始化Py接口
//	Py_Initialize();
//	if (!Py_IsInitialized()) {
//		cout << "py初始化失败" << endl;
//	}
//	//2.初始化python系统文件路径（目标py文件所在路径）
//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('C:/Users/you/source/repos/CppChengZhang/X-Cpp_Python')");
//
//	//3.导入Py文件，不用写后缀
//	PyObject* pyModule = PyImport_ImportModule("testFunc");
//	if (pyModule == nullptr) {
//		cout << "未找到模块" << endl;
//		return 1;
//	}
//
//	//4.获取模块中的类
//	PyObject* cls = PyObject_GetAttrString(pyModule, "Person");
//	if (!cls) {
//		cout << "未获取到类" << endl;
//		return 1;
//	}
//
//	//5.实例化
//	//构造函数参数
//	PyObject* args = PyTuple_New(2);
//	PyTuple_SetItem(args, 0, Py_BuildValue("s", "jack"));//"s"表示C风格字符串
//	PyTuple_SetItem(args, 1, Py_BuildValue("i", 18));
//	//构造
//	//PyObject* obj = PyEval_CallObjectWithKeywords(cls, args, (PyObject*)0);//py3.9已弃用
//	PyObject* obj = PyObject_CallObject(cls, args);
//
//	//获取对象成员
//	PyObject* func = PyObject_GetAttrString(obj, "foo");
//	if (!func || !PyCallable_Check(func)) {
//		cout << "未找到成员函数" << endl;
//		return 1;
//	}
//
//	//调用成员
//	PyObject_CallObject(func, nullptr);
//
//
//	//f.释放
//	Py_Finalize();
//
//	return 0;
//}

//4.运行脚本文件
#include<iostream>
using namespace std;
int main() {
	//1.初始化Python接口
	Py_Initialize();
	if (!Py_IsInitialized()) {
		cout << "python init failed" << endl;
		return 1;
	}
	
	//2.运行
	cout << "准备打开脚本文件" << endl;

	//FILE* fp = fopen("C:/Users/you/source/repos/CppChengZhang/X-Cpp_Python/test2.py", "r");

	//PyObject* obj = Py_BuildValue("s", "C:/Users/you/source/repos/CppChengZhang/X-Cpp_Python/test2.py");
	PyObject* obj = Py_BuildValue("s", "C:/Users/you/source/repos/CppChengZhang/X-Cpp_Python/CppWinPyTest.py");
	FILE* fp = _Py_fopen_obj(obj, "r+");

	if (!fp) {
		cout << "脚本文件打开失败" << endl;
		return 1;
	}
	cout << "成功打开脚本文件" << endl;

	cout << "准备执行脚本文件" << endl;

	PyRun_SimpleFile(fp, "xxxxxxxxxx");
	cout << "成功执行脚本文件" << endl;
	

	//3.结束，回收资源
	Py_Finalize();

	return 0;
}