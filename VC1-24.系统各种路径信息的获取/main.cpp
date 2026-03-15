#include<Windows.h>
#include<iostream>
#include<string>
#include<cstdlib>
#include<stdio.h>
#include<ShlObj.h>
#pragma comment(lib,"shell32.lib")

//C语言获取
//1.Windows、System32、temp等路径的获取：

//2.桌面目录、我的文档等目录的获取
//超强目录获取函数：SHGetSpecialFolderPath，是shell API

//3.应用程序当前目录的获取与设置
//获取当前进程的当前目录：GetCurrentDirectory————不一定是当前exe文件所在的目录
//设置当前进程的当前目录：SetCurrentDirectory

//4.可执行文件所在目录(exe、dll)
//GetModuleFileName————获得文件路径信息（包括文件本身在内）
//进一步封装函数（去掉尾巴）

//5.工程当前目录与debug目录的不同
//GetCurrentDirectory不同（当前活动目录不同）
void Test() {
	//1.Windows、System32、temp等路径的获取：
	wchar_t szPath[MAX_PATH] = { 0 };
	GetSystemDirectoryW(szPath, MAX_PATH);//C:\WINDOWS\system32
	wprintf(L"%s\n", szPath);
	GetWindowsDirectoryW(szPath, MAX_PATH);//C:\WINDOWS
	wprintf(L"%s\n", szPath);
	GetTempPathW(MAX_PATH, szPath);//C:\Users\you\AppData\Local\Temp//临时目录
	wprintf(L"%s\n", szPath);



	SHGetSpecialFolderPathW(NULL, szPath, CSIDL_DESKTOP, FALSE);//桌面
	wprintf(L"%s\n", szPath);
	SHGetSpecialFolderPathW(NULL, szPath, CSIDL_APPDATA, FALSE);//C:\Users\you\AppData\Roaming
	wprintf(L"%s\n", szPath);

	GetModuleFileNameW(NULL, szPath, MAX_PATH);
	wprintf(L"%s\n", szPath);

}

//C++获取
using std::cout;
using std::endl;
void Test2() {
	wchar_t* appdataPath;
	_wdupenv_s(&appdataPath, nullptr, L"APPDATA");
	std::wcout << appdataPath << std::endl;
	std::wstring path = appdataPath ;
	free(appdataPath);

	path += L"\\XYY\\XYZ";
	std::wcout << path << std::endl;

}
void Test3() {
	//_wgetenv_s()
	wchar_t path[MAX_PATH] = { 0 };
	SHGetSpecialFolderPathW(NULL, path, CSIDL_APPDATA, TRUE);
	std::wstring pathSave = path;
	pathSave += L"\\XYY\\RTY";
	std::wcout << pathSave << std::endl;
}

int main() {
	//Test2();
	Test3();
}

// ShellExecute(NULL, "open", folderPath.c_str(), NULL, NULL, SW_SHOWNORMAL);//使用windows打开文件夹

