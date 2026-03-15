//2）.显式链接（程序员负责使动态库运行）
//		1.定义函数指针类型  typedef
//		2.加载动态库
//			HMODULE LoadLibrary(
//				LPCTSTR lpFileName//动态库文件名或全路径
//			);//返回dll的实例句柄（HINSTANCE）
//		3.获取函数（绝对）地址
//			FARPROC GetProcAddress(
//				HMODULE hModule,//dll的实例句柄
//				LPCSTR lpProcName//函数名称
//			);//成功则返回目标函数地址
//		4.调用函数
//		5.卸载动态库
//			BOOL FreeLibrary(
//				HMODULE hModule//dll的实例句柄
//			)


#include<iostream>
using namespace std;
#include<Windows.h>

//1.定义函数指针
typedef int(*ADD)(int, int);
typedef int(*SUB)(int, int);
typedef int(*MUL)(int, int);

int main() {
	//2.加载动态库
	HINSTANCE hDll = LoadLibrary(L"X-动态库-2.创建动态库.dll");
	cout << "hDll:" << hDll << endl;

	//3.获取函数地址   4.调用
	//ADD myAdd = (ADD)GetProcAddress(hDll, "CPPdll_add");//无法获取函数地址
	//C++函数换名机制
	//查找dll的函数是根据dll的文件头查找，文件头中的函数名经过C++换名机制转换
	ADD myAdd = (ADD)GetProcAddress(hDll, "?CPPdll_add@@YAHHH@Z");//换名规则后的函数名，这种方式要求对微软的换名机制非常了解
	cout << "myAdd:" << myAdd << endl;
	int sum = myAdd(5, 4);
	cout << "sum=" << sum << endl;

	SUB mySub = (SUB)GetProcAddress(hDll, "CPPdll_sub");//不过换名规则的函数名（在创建动态库时使用模块定义文件）
	cout << "mySub:" << mySub << endl;
	int sub = mySub(5, 4);
	cout << "sub=" << sub << endl;

	MUL myMul = (MUL)GetProcAddress(hDll, "CPPdll_mul");
	cout << "myMul:" << myMul << endl;
	int mul = myMul(5, 4);
	cout << "mul=" << mul << endl;

	//5.卸载动态库
	FreeLibrary(hDll);
}