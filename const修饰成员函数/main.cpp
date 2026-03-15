#include<iostream>
using namespace std;

class CGirl {
public:
	mutable  string m_name;
	const int m_age;

	CGirl(string name, int age) :m_name("漂亮的" + name), m_age(age - 2) {//当m_age被定义为常量时，不能再赋值，当类的成员为引用时，必须使用初始化列表
		//m_age = age;//m_age被定义为常量时，不能再赋值，编译不通过
		cout << "调用了CGirl(string name,int age,CBoy boy)构造函数\n";
	};


	//const修饰成员函数 表示在成员函数中保证不会修改调用对象的成员变量
	//在实际开发中，如果成员函数不会修改成员变量，就应该加const修饰
	void show1()const{ 
		m_name = "西施show1";
		cout << "姓名：" << m_name << "，年龄：" << m_age << endl;
		//show3();//const函数只能调const函数，不能调非const函数（编译器会报错）
	};
	void show2()const {
		m_name = "西施show2";
		cout << "姓名：" << m_name << "，年龄：" << m_age << endl;
	};
	void show3() {
		m_name = "西施show3";
		cout << "姓名：" << m_name << "，年龄：" << m_age << endl;
		show1();
		show4();//非const函数能调const函数，也能调非const函数
	};
	void show4() {
		m_name = "西施show4";
		cout << "姓名：" << m_name << "，年龄：" << m_age << endl;
	};

};


int main() {
	
	const CGirl g1("icey", 18);//常对象
	g1.show1();
	//g1.show3();//const对象只能调用const函数（构造函数与析构函数除外）
	//g1.show();

	cout << "退出main函数" << endl;
}