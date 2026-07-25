#include<iostream>
using namespace std;

int age = 9999;
struct cPeople {
	enum eSex {//类中定义枚举，叫匿名枚举
		MALE = 1,
		FEMALE
	};
	int sex = FEMALE;//5.可以为类的成员指定缺省值（C++11标准）
	int age = 0;
	cPeople() {
		sex = MALE;//6.但指定的缺省值可被构造函数再次指定，且构造函数优先级更高
	}//8.在类中定义的函数都将自动成为内联函数，如此处的构造函数
	void show();
	void test() {
		cout << age << endl;//使用成员变量
		cout << ::age << endl;//全局区变量
	}
};
inline void cPeople::show() {
	cout << "性别：" << sex << endl;
}//9.在类外定义的函数默认不是内联函数，但如果使用了inline限定符，则是内联函数

void test1() {
	cPeople people;
	//people.sex = people.MALE;//2.匿名枚举，以类为作用域，可以通过对象引出
	if (people.sex == cPeople::MALE) {//3.也可以通过类的命名空间引出
		cout << "性别为男" << endl;
	}
	else if (people.sex == cPeople::eSex::FEMALE) {//4.也可以逐级解析命名空间，总之不能直接调用(在类外直接使用MALE或FEMALE)，故称为匿名枚举
		cout << "性别为女" << endl;
	}

	cout << "sizeof(cPeople)" << sizeof(cPeople) << endl;
	cout << "sizeof(people)" << sizeof(people) << endl;//7.据说对类和对象使用sizeof运算符意义不大，但测试有用，估计意思是对对象指针意义不大

	people.show();
}


void test2() {
	cPeople p;
	p.age = 10;
	p.test();
}

int main() {
	test2();
}