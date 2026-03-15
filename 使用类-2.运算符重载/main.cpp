//在C中已有运算符重载（*表示乘法和解引用）
//C++将运算符重载后的可操作元素扩展到自定义的数据类型（结构体、类）

#include<iostream>
using namespace std;

class CGirl {
	friend void  addScore(CGirl& g, int score);
	//friend void  operator+(CGirl& g, int score);
	//friend void  operator-(CGirl& g, int score);
	//friend int  operator-(CGirl& g, int score);
	friend CGirl&  operator-(CGirl& g, int score);

	int m_x;
	int m_score;
public:
	string m_name;

	//默认构造函数
	CGirl() { m_name = "name"; m_x = 65; m_score = 30; }
	void show() { cout << "name：" << m_name << "，x：" << m_x << "，score：" << m_score << endl; };

	//重载运算符描述运算（操作）规则————成员函数版本
	CGirl&  operator+(int score) {
		m_score += score;
		return *this;
	}
};

//友元全局函数实现运算（操作）规则
void  addScore(CGirl& g, int score) {
	g.m_score += score;
}

//重载运算符描述运算（操作）规则————非成员函数版本
//void  operator+(CGirl& g, int score) {
//	g.m_score += score;
//}
//void  operator-(CGirl& g, int score) {
//	g.m_score -= score;
//}
//int  operator-(CGirl& g, int score) {
//	g.m_score -= score;
//	return g.m_score;
//}
CGirl&  operator-(CGirl& g, int score) {
	g.m_score -= score;
	return g;
}

int main() {
	CGirl g;
	//g = +30;
	addScore(g, 30);
	g.show();

	//重载的调用方式（2）
	//operator+(g, 30);//1.函数方式调用
	g.show();

	g + 30;//2.运算符方式调用
	g.show();
	//对立运算符
	g - 20;
	g.show();

	//重载符号返回值为int型时
	/*int res = g - 20;
	cout << res << endl;*/

	//重载符号返回值为class
	CGirl g2;
	g2 = g - 20 - 3 - 4 - 5 - 6;//重载运算符连续调用，本质上是函数的多次调用(自左向右运算)
	g2 = operator-(operator-(operator-(operator-(g, 20), 3), 4), 6);//效果同上
	g2.show();

	//重载函数的参数列表中至少有一个是用户自定义的类型，为了防止程序员为内置数据类型重载运算符。否则编译会报错
	//如果运算符重载既可以是成员函数也可以是全局函数，应该优先考虑成员函数，这样才更符合运算符重载的初衷
	//重载函数不能违背运算符原来的含义和优先级
	//不能创建新的运算符

	/*以下运算符只能通过成员函数进行重载
		= ——赋值运算符
		()——函数调用运算符
		[]——下标运算符
		->——通过指针访问类成员的运算符*/

}


