#include<iostream>
using namespace std;



class CGirl;//1.类声明前置（友元成员函数）

//友元类（定义）
//2.友元成员函数所属类声明放在目标类之前（友元成员函数）
class CBoy {
public:
	void func1(const CGirl& g);
	/*{
		cout << "mg name：" << g.m_name << endl;
		cout << "mg x：" << g.m_x << endl;
		g.showname();
		g.showx();
	}*/
	void func2(const CGirl& g);
	/*{
		cout << "mg x：" << g.m_x << endl;
	}*/
};


class CGirl {
	friend int main();
	friend void func();
	//friend class CBoy;
	//4.成员函数声明为友元（友元成员函数）
	friend void CBoy::func1(const CGirl& g);
	friend void CBoy::func2(const CGirl& g);
public:
	string m_name;
	CGirl() { m_name = "dream"; m_x = 60; };
	void showname()const { cout << "name：" << m_name << endl; };

private:
	int m_x;
	void showx() const { cout << "x：" << m_x << endl; };
};


//3.外置友元成员函数的函数体，并放在目标类定义之后（友元成员函数）
void CBoy::func1(const CGirl& g) { cout << "mg x：" << g.m_x << endl; }
void CBoy::func2(const CGirl& g) { cout << "mg x：" << g.m_x << endl; }



//友元全局函数（定义）
void func() {
	CGirl g;
	g.showname();

	g.showx();
}

int main() {
	//func();
	CGirl g;
	CBoy b;
	b.func1(g);
	return 0;
}