#include<iostream>
using namespace std;

class CBoy {
public:
	string m_xm;
	CBoy() {//无参普通构造函数（默认构造函数）
		m_xm.clear(); cout << "调用了CBoy()构造函数\n";
	}
	CBoy(string xm) {//有一个参数的普通构造函数
		m_xm = xm;cout<< "调用了CBoy(string xm)构造函数\n";
	}
	CBoy(const CBoy& bb) {//拷贝构造函数
		m_xm = bb.m_xm; cout << "调用了CBoy(const CBoy& bb)拷贝构造函数\n";
	}
};

class CGirl {
public:
	string m_name;
	const int m_age;
	CBoy& m_boy;

	//构造函数
	/*CGirl() :m_name("西施"), m_age(23) {
		cout << "调用了CGirl()构造函数\n";
	};*/
	/*CGirl():m_age(0) {
		cout << "调用了CGirl()构造函数\n";
	};*///没有参数的普通构造函数，默认构造函数

	//CGirl(string name, int age, CBoy& boy) :m_name("漂亮的" + name), m_age(age - 2) {//初始化列表的值可以是具体值，可以是构造函数形参，也可以是表达式
	//	m_boy.m_xm = boy.m_xm;
	//	cout << "调用了CGirl(string name,int age,CBoy boy)构造函数\n";
	//};
	//CGirl(string name, int age, CBoy& boy) :m_name("漂亮的" + name), m_age(age - 2),m_boy(boy) {//初始化列表的类对象初始化将调用这个成员对象所属类的拷贝构造函数
	//	cout << "调用了CGirl(string name,int age,CBoy boy)构造函数\n";
	//};
	CGirl(string name, int age, CBoy& boy) :m_name("漂亮的" + name), m_age(age - 2), m_boy(boy) {//当m_age被定义为常量时，不能再赋值，当类的成员为引用时，必须使用初始化列表
		//m_age = age;//m_age被定义为常量时，不能再赋值，编译不通过
		cout << "调用了CGirl(string name,int age,CBoy boy)构造函数\n";
	};

	void show() { cout << "姓名：" << m_name << "，年龄：" << m_age << "，boy：" << m_boy.m_xm << endl; };
};

class Test_Array {
public:
	int a[2];
	int b;
public:
	Test_Array() :a{ 999,11 }, b{ 11111 }{};//数组的初始化列表用{}——统一初始化列表
};


int main() {
	/*CBoy boy("Suu");

	CGirl g1("icey", 18, boy);
	g1.show();*/

	Test_Array testArray;
	cout << "testArray:" << testArray.a[0] << "," << testArray.a[1] << "," << testArray.b << endl;

	cout << "退出main函数" << endl;
}