#include<iostream>
using namespace std;

//左移运算符——<<
//用于输出自定义对象的成员变量，在实际开发中很有价值（调试和日志）
//	C++主要用于开发后台服务程序，服务程序运行的时候是没有界面的，甚至不会把信息输出到控制台，一般是写日志文件——把对象的对象写日志文件也是常见的调试手段


//重载左移运算符只能使用非成员函数版本，如果要输出私有成员，可以配合友元一起使用


class C1 {
	//friend ostream& operator<<(ostream& cout, const C1& g);


	string m_name;
	int m_x;
	int m_score;
public:
	//默认构造函数
	C1() { m_name = "David"; m_x = 24; m_score = 0; };
	void Show() { cout << "name:" << m_name << ",x:" << m_x << ",score" << m_score << endl; }
	ostream& operator<<(ostream& cout) {//对象指针this作为第一个形参，隐式传递了——意味着，使用这个重载的时候，cout要写在右边
		cout << "name:" << this->m_name << ",x:" << this->m_x << ",score" << this->m_score << endl;
		return cout;
	}
};


//重载cout作用的<<
//ostream& operator<<(ostream& cout, const C1& g) {
//	cout << "name:" << g.m_name << ",x:" << g.m_x << ",score" << g.m_score << endl;
//	return cout;
//}

int main() {
	C1 g;


	//cout功能强大：识别多种数据类型，字符串拼接，这些功能就是通过重载“<<”运算符实现的


	//cout的本质，在<iostream>头文件中声明的一个全局对象
	//所以关于<<重载而成的函数原型：
	//参数表：一个是cout所属的类型，另一个是要输出的数据类型
	//返回值：cout对象
	//根据<<定义可以发现有15个不同数据类型重载——这是cout能识别多种数据类型的原因


	//如果想让cout支持自定义数据类型，就需要在类中重载“<<”
	//cout << g << endl;//——非成员函数的左移运算符重载

	g << cout;//——成员函数的左移运算符重载

	//但这不是我们想要的结果，所以左移运算符只能使用全局函数的方式，而不能用成员函数


	return 0;
}

