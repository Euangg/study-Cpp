#include<iostream>
using namespace std;

class CGirl {
public:
	string m_name;
	static int m_age;

	//静态成员变量不会在创建对象的时候初始化，必须在程序的全局区用代码清晰地初始化（用范围解析运算符::）

	CGirl(const string& name, int age) { m_name = name; m_age = age; };;
	void showname() { cout << "姓名" << m_name << endl; };
	static void showage() { cout << "年龄" << m_age << endl; }
};

int CGirl::m_age = 18;//初始化静态成员变量，必须位于全局区

int main() {
	//静态成员不用实例化对象就能访问（普通成员必须实例化对象才能访问）
	cout << "CGirl::m_age =" << CGirl::m_age << endl;
	//静态成员变量与静态成员函数都适用
	CGirl::showage();

	CGirl g1("icey", 22);

	g1.showname();
	g1.showage();
}