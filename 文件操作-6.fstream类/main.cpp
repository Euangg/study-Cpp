#include<fstream>
using namespace std;
//fstream针对文件可读可写
//初始化与open
//	参数2模式，缺省值：ios::in|ios::out，不会清空原文件内容

int main() {



	fstream f;

	f.open("D:/test2.txt");



	//C语言中只有FILE*
	//C++做区分是遵循编程开发中的权限减法原则，只要需要的权限，操作时也仅启用所需要的权限

}