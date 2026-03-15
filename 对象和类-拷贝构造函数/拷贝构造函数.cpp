//用一个已经存在的对象，创建新的对象，不会调用构造函数，而是调用拷贝构造函数
//类名 新对象名(已存在对象名);
//类名 新对象名=已存在对象名;
//参数传递，传值
//返回值
 
//拷贝构造函数是一个包含以同类对象引用为参数的构造函数
//类似于构造函数，如果没有定义拷贝构造函数，编译器会提供一个拷贝构造函数，功能是直接把一个对象的成员变量赋值给要创建的对象
//拷贝构造函数也是构造函数的一种，只要定义，就不会再有编译器提供的默认无参构造函数



#include<iostream>
using namespace std;


class Book{
public:
	int pages_=0;
public:
	//Book() {};
	//Book(const Book& book) {};
};

class Apple {
public:
	int size_;
public:
	Apple() {};
	//Apple(const Apple& apple){};
};

class Crayon {
public:
	int color_;
public:
	//Crayon() {};
	Crayon(const Crayon& crayon) {};
};

class Desk {
public:
	int height_=0;
public:
	Desk() {};
	Desk(const Desk& desk) {};
};


//编译器可能会提供的四种成员函数：
//无参构造函数		程序员没有定义任何构造函数的情况下
//拷贝构造函数		程序员没有定义拷贝构造函数
//析构函数			程序员没有定义析构函数
//赋值函数			程序员没有定义赋值函数（重载赋值运算符）

class Egg {
public:
	int size_;
public:
	Egg() {cout << "无参构造函数" << endl;};
	~Egg() { cout << "析构函数" << endl; };
	Egg(const Egg& egg) { cout << "拷贝构造函数" << endl; };
	Egg& operator=(const Egg& egg) { cout << "赋值函数" << endl; return *this; };

};

int main() {
	Book book1;				//无参构造		编译器
	Book book2(book1);		//拷贝构造		编译器

	Apple apple1;			//无参构造		程序员
	Apple apple2(apple1);	//拷贝构造		编译器	

	Crayon* c1=nullptr;		//无参构造		无
	Crayon c2(*c1);			//拷贝构造		程序员

	Desk desk1;				//无参构造		程序员
	Desk desk2(desk1);		//拷贝构造		程序员

	Egg egg1;			//调用无参构造函数
	Egg egg2(egg1);		//调用拷贝构造函数
	Egg egg3 = egg1;	//调用拷贝构造函数
	egg3 = egg1;		//调用赋值函数
}




//函数重载，参数是否加const约束是否算同一种重载？——不算重载