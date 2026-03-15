#include<iostream>
using namespace std;

int main2(int argc, char* argv[]) {
	cout << "hello world" << endl;
	cout << "argc:" << argc << endl;
	for (int i = 0; i < argc; i++) {
		cout << "argv["<<i<<"]:" << argv[i] << endl;
	}
	return 0;
}

//如果Console项目没有main函数
//会报“无法解析的外部符号 _main，函数 "int __cdecl invoke_main(void)" (?invoke_main@@YAHXZ) 中引用了该符号”

//如果窗口项目没有写WinMain
//会报“无法解析的外部符号 _WinMain@16，函数 "int __cdecl invoke_main(void)" (?invoke_main@@YAHXZ) 中引用了该符号”