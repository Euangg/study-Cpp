#include<iostream>
using std::cout;
using std::endl;
#include<filesystem>
namespace fs = std::filesystem;
#include<ShlObj.h>

//获取当前工作目录
void test1() {
	fs::path p = fs::current_path();
	cout << p << endl;
}

//赋值path
void test2() {
	fs::path p = "asdasd";
	cout << p << endl;

	std::wstring ws = L"qwerq";
	p = ws;
	cout << p << endl;
}

//路径拼接
void test2_2() {
	wchar_t* path_appdata_roaming;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path_appdata_roaming);
	fs::path path_data = path_appdata_roaming;
	path_data = path_data / L"XYY" / L"WH";
	cout << path_data << endl;
}

//检查文件存在
void test3() {
	fs::path p = fs::current_path();
	p /= "test";
	cout << p << endl;

	if (fs::exists(p)) cout << "存在" << endl;
	else cout << "不存在" << endl;
}

//补全路径文件夹
void test4() {
	fs::path p = fs::current_path();
	p /= "test";
	p /= "test2";
	cout << p << endl;
	
	if (fs::exists(p)) cout << "存在" << endl;
	else cout << "不存在" << endl;

	fs::create_directories(p);

	if (fs::exists(p)) cout << "存在" << endl;
	else cout << "不存在" << endl;
}

int main() {
	
	//test2();
	test2_2();
	//test3();
	//test4();
}