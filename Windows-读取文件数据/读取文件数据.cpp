#include<iostream>
using namespace std;

#include<Windows.h>

void OpenAFile() {
	//文件打开方式1（使用下面这个非常变态的函数）
	HANDLE hFile = CreateFileW(L"atk_tang.wav", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	//创建或打开文件或 I/O 设备。
	//该函数返回一个句柄，该句柄可用于访问各种类型的 I/O 的文件或设备，具体取决于文件或设备以及指定的标志和属性。
	//lpFileName [in]:要创建或打开的文件或设备的名称
	//dwDesiredAccess [in]:请求对文件或设备的访问权限，可以汇总为读取、写入。最常用的值是 GENERIC_READ、GENERIC_WRITE或两者（GENERIC_READ | GENERIC_WRITE）
	//dwShareMode [in]:请求的文件或设备的共享模式
	//lpSecurityAttributes [in, optional]:可选的安全描述符。此参数可以 NULL。
	//dwCreationDisposition [in]:对存在或不存在的文件或设备执行的操作。参数通常设置为 OPEN_EXISTING
	//dwFlagsAndAttributes [in]:文件或设备属性和标志，FILE_ATTRIBUTE_NORMAL 是文件最常见的默认值
	if (hFile == INVALID_HANDLE_VALUE) {
		cout << "文件打开失败" << endl;
		return;
	}
	cout << "文件打开成功" << endl;
}
void OpenAFile2() {
	//文件打开方式2
	OFSTRUCT ofs;
	HFILE hf = OpenFile("atk_tang.wav", &ofs, OF_READ);
	//创建、打开、重新打开或删除文件。微软说：“此函数的功能有限，不建议使用。 对于新应用程序开发，请使用 CreateFile 函数。”md……
	//lpFileName [in]:文件的名称。
	//结构体不能省
	if (hf == HFILE_ERROR) {
		cout << "文件打开失败" << endl;
		return;
	}
	cout << "文件打开成功" << endl;

	//确实垃圾，不能支持宽字节路径，路径长度不能超128，还必须要准备一个结构体
}

int main() {
	HANDLE hFile = CreateFileW(L"atk_tang.wav", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		cout << "文件打开失败" << endl;
		return 0;
	}
	cout << "文件打开成功" << endl;

	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
	//移动指定文件的文件指针。
	//hFile [in]:文件的句柄。
	//lDistanceToMove [in]:有符号值的低序 32 位，指定移动文件指针的字节数。
	//lpDistanceToMoveHigh [in, out, optional]:指向要移动的有符号 64 位距离的高阶 32 位的指针。
	//dwMoveMethod [in]:文件指针移动的起点。
	DWORD dwReaded = 0;
	char buffer[4];
	ReadFile(hFile, &buffer, 4, &dwReaded, NULL);
	cout << (buffer) << endl;

	//小端序：低地址存储数据的低字节，便于机器处理
	//大端序：低地址存储数据的高字节，便于人类阅读
}