#include<iostream>
#include<codecvt>
#include<Windows.h>
using std::string;
using std::wstring;
using std::cout;
using std::endl;
//C++标准库
void test1() {
	wstring wstr = L"1234567890 abcdefg hijklmn opqrst uvwxyz 一二三四五六七八九十";
	std::wstring_convert<std::codecvt_utf8<wchar_t>>converter;
	string str = converter.to_bytes(wstr);//英文数字没问题
	
	cout << str << endl;
}
//C++标准库
void test2() {
	wstring wstr = L"1234567890 abcdefg hijklmn opqrst uvwxyz 一二三四五六七八九十";
	string str(wstr.size(), 0);
	std::wcstombs(&str[0], wstr.c_str(), wstr.size());
	cout << str << endl;
}
//Windows
void test3() {
	wstring wstr = L"1234567890 abcdefg hijklmn opqrst uvwxyz 一二三四五六七八九十";
	string str(wstr.size() * 2, 0);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), &str[0], str.size(), NULL, NULL);//完美
	cout << str << endl;
}
int main(){
	//test1();
	//test2();
	test3();
}