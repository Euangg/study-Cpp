//构造函数只能用于某种类型到类的转换
//如果要进行相反的转换，可以使用转换函数

//语法 operate 数据类型();
//注：必须是成员函数；无参，返回值类型不指定（与转换数据类型统一）



#include<iostream>
using namespace std;
class Answer {
public:
	int key_;
public:
	operator int() { return key_; };
	operator string() { return "hello world"; };
};

int main() {
	Answer a1;

	a1.key_ = 99;
	cout << "key:" << a1 << endl;

	string s = a1;
	cout << s << endl;

	
	//不推荐使用，更推荐使用成员函数
	//stl中的string，获取字符串指针使用的是成员函数.c_str()
}

//复习explicit关键字————
