//运行阶段类型识别（RTTI RunTime Type Identification）为程序 在运行阶段 确定 对象的类型，只适用于包含纯虚函数的类
//dynamic_cast运算符：用指向基类的指针来生成派生类的指针
//		它不能回答“指针指向的是什么类的对象” 的问题
//		但能回答“是否可以安全地将对象的地址赋值给特定类型的指针” 的问题
//语法：
//派生类指针=dynamic_cast<派生类类型*>(基类指针)
//如果转换成功，dynamic_cast返回对象的地址，失败返回nullptr


//注：
//1.dynamic_cast只适用于包含虚函数的类——————dynamic_cast只为多态的场景而设计，在程序中使用dynamic_cast的时候，它要查虚函数表，如果不是多态类型，编译过不去
//2.dynamic_cast可以将派生类指针转化为基类指针，但这种画蛇添足的做法没有意义
//3.dynamic_cast可以用于引用，但是，没有与空指针对应的引用值(nullptr)，如果转换请求不正确，会出现bad_cast异常

#include<iostream>
using namespace std;

//有虚成员函数（多态）
class Hero {
public:
	int viability;
	int atk;
	virtual void sk1() { cout << "sk1" << endl; };
	virtual void sk2() { cout << "sk2" << endl; };
	virtual void sk3() { cout << "sk3" << endl; };

};

class XYY :public Hero {
public:
	void sk1() { cout << "X--sk1" << endl; };
	void sk2() { cout << "X--sk2" << endl; };
	void sk3() { cout << "X--sk3" << endl; };
	void show() { cout << "Hello!" << endl; };


};

class SUU :public Hero {
public:
	void sk1() { cout << "SUU--sk1" << endl; };
	void sk2() { cout << "SUU--sk2" << endl; };
	void sk3() { cout << "SUU--sk3" << endl; };

};

int main() {
	int id = 0;
	cout << "please input id(1,2):" << endl;
	cin >> id;


	Hero* ptr = nullptr;
	switch (id)
	{
	case 1:
		ptr = new XYY;
		break;
	case 2:
		ptr = new SUU;
		break;
	}

	if (ptr != nullptr) {
		ptr->sk1();
		ptr->sk2();
		ptr->sk3();
		//如果基类指针指向的是XYY对象，则调用里面的show()函数
		//ptr->show();//show()不是虚函数，ptr是基类指针，不能这么调用
		XYY* x = dynamic_cast<XYY*>(ptr);//把基类指针ptr转换为派生类指针x
		if (x != nullptr)x->show();

		delete ptr;
	}

}