#include<iostream>
using namespace std;
struct sPeople {
	int no_;
	string name_;

	void show() {
		cout << "号码:" << no_ << "\t姓名:" << name_ << endl;
	}
};

class cPeople {
public:
	int no_;
	string name_;

	void show() {
		cout << "号码:" << no_ << "\t姓名:" << name_ << endl;
	}
};

int main() {
	sPeople* pp1;
	pp1 = new sPeople({ 10,"asf" });
	//pp1 = new sPeople(99, "asda");//2.默认成员构造必须填统一初始化列表，所以结构体默认构造函数是以统一初始化列表为参数的

	pp1->show();

	cPeople* pp2;
	pp2 = new cPeople({ 99, "dasa" });
	//pp2 = new cPeople(99, "dasa");//3.类的默认构造函数也是以统一初始化列表为参数的
	pp2->show();
	

	(*pp1).no_ = 1;//1.运算符.的优先级高于解地址*，所有()不能少

}