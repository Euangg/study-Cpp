//代码重用

//使用继承的场景

//1）新创建的类与现有的类相似，只是多出若干成员变量或成员函数时，可以使用继承
//2）当需要创建多个类时，如果它们拥有很多相似的成员变量或成员函数，可以将这些类共同的成员提取出来，定义为基类，然后从基类继承

#include<iostream>
using namespace std;

class CAllComers {
public:
	string m_name;
	string m_tel;

	//构造函数
	CAllComers() { m_name = "xx"; m_tel = "???"; };

	void sing() {
		cout << "some nights i stay up" << endl;
	}

	void setname(const string& name) { m_name = name; };

	void settel(const string& tel) { m_tel = tel; };

};


//":"表示继承，后面紧跟继承方式，再跟继承的类
//被继承的类称为父类或基类
//继承的类称为派生类或子类
//继承与派生是站在不同角度描述同一件事

class CGirl :public CAllComers {
public:
	int m_bh;
	CGirl() { m_bh = 8; };
	void show() { cout << "编号:" << m_bh << "，姓名:" << m_name << "，联系电话:" << m_tel << endl; };

};


int main() {
	CGirl g;
	g.setname("xs");
	g.show();

}