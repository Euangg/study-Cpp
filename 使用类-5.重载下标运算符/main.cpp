#include<iostream>
using namespace std;

//下标运算符必须以成员函数的形式重载
//语法（2）：
//1：返回值类型& operate[](参数);//——可访问可修改
//2.const 返回值类型& operate[](参数)const;//——可访问，不可修改
//在实际开发中应该同时提供这两种形式，为了适应const对象，因为通过const对象只能调用const成员函数

//在重载函数中可以对下标做合法性检查，防止访问越界
//但是如果下标不合法如何处理，返回什么？————所以也不用检查（低级错误）

class C1 {
	string rel[3];
public:
	string name;
	//默认构造函数
	C1() { rel[0] = "qewr", rel[1] = "asdf", rel[2] = "zxcv"; };
	void Show() { cout << rel[0] << "、" << rel[1] << "、" << rel[2] << endl; };
	string& Rel(int ii) {
		return rel[ii];
	}//函数返回值是引用类型，函数调用可以当变量使用（可以直接赋值，访问并改变私有成员）
	
	string& operator[](int ii) {
		return rel[ii];
	}

	const string& operator[](int ii)const {
		return rel[ii];
	}
};

int main() {

	string a = "abcd";
	//C++的string本质上是封装了字符数组的类，a是一个实例
	//并且类中重载了下标运算符，如下：
	cout << "a=" << a << endl;
	cout << "a[0]=" << a[0] << endl;
	cout << "a[1]=" << a[1] << endl;
	cout << "a[2]=" << a[2] << endl;
	cout << "a[3]=" << a[3] << endl;
	cout << "-----------------------------------------------------------" << endl;
	C1 g;
	cout << "no.1:" << g.Rel(1) << endl;
	g.Rel(1) = "uoip";
	g[0] = "xxxxx";

	g.Show();

	cout << "-----------------------------------------------------------" << endl;
	const C1 g2 = g;
	cout << "no.1:" << g2[1] << endl;
}