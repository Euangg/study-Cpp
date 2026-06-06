
#include<string>
#include<iostream>
using namespace std;

void test1() {
	wstring s1 = L"abcdefghijklmnopqrstuvwxyz";
	wstring s2 = L"";

	cout << "s1.size()=" << s1.size() << endl;//26
	cout << "s2.size()=" << s2.size() << endl;//0
	//结：.size()求取当前字符串中的字符数

	cout << "s1[1]=" << s1[1] << endl;//98(b的ascii)
	//结：支持随机访问，取字符的值

	for (int i = 0; i < s1.size(); i++) {
		s2.push_back(s1[i]);
		wcout << "第" << i << "次流:" << s2 << endl;
	};
}

//判断相等
void test2() {
	string s1 = "asdfd";
	if (s1 == "asdf")cout << "=asdf" << endl;
	else cout << "!=asdf" << endl;
}

//bool判断，为空
void test3() {
	string s1 = "";
	string s2 = "a";

	if (s1.size()) { cout << "s1=true" << endl; }
	else cout << "s1=false" << endl;

	if (s2.size()) { cout << "s2=true" << endl; }
	else cout << "s2=false" << endl;
}

int main() {
	//test1();
	//test2();
	test3();
}