#include<Windows.h>
#include<iostream>
#include<ShlObj.h>
#pragma comment(lib,"shell32.lib")

using std::cout;
using std::wcout;
using std::endl;


//Windows、System32、temp等路径的获取：
void test() {
	wchar_t szPath[MAX_PATH] = { 0 };

	GetSystemDirectoryW(szPath, MAX_PATH);//C:\WINDOWS\system32
	wcout << szPath << endl;

	GetWindowsDirectoryW(szPath, MAX_PATH);//C:\WINDOWS
	wcout << szPath << endl;

	GetTempPathW(MAX_PATH, szPath);//C:\Users\you\AppData\Local\Temp//临时目录
	wcout << szPath << endl;

	GetModuleFileNameW(NULL, szPath, MAX_PATH);
	wcout << szPath << endl;

}

//桌面、AppData
void test1_2(){
	wchar_t path[100];

	SHGetSpecialFolderPathW(NULL, path, CSIDL_DESKTOP, FALSE);//桌面
	wcout << path << endl;
	SHGetSpecialFolderPathW(NULL, path, CSIDL_APPDATA, FALSE);//C:\Users\you\AppData\Roaming
	wcout << path << endl;
}

//AppData2、最好的函数SHGetKnownFolderPath
void test1_3() {
	wchar_t* path;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path);//C:\Users\you\AppData\Roaming
	wcout << path << endl;
	std::wstring ws = path;
	wcout << ws << endl;
}

//C++获取
void test2() {
	wchar_t* appdataPath;
	_wdupenv_s(&appdataPath, nullptr, L"APPDATA");
	std::wcout << appdataPath << std::endl;
	std::wstring path = appdataPath ;
	free(appdataPath);

	path += L"\\XYY\\XYZ";
	std::wcout << path << std::endl;

}


int main() {
	//test();
	test1_3();
}

// ShellExecute(NULL, "open", folderPath.c_str(), NULL, NULL, SW_SHOWNORMAL);//使用windows打开文件夹

