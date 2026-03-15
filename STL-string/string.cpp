
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

int main() {
	test1();

}