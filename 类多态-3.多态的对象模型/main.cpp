#include<iostream>
using namespace std;

//无虚成员函数（多态）
//class Hero {
//public:
//	int viability;
//	int atk;
//	void sk1() { cout << "sk1" << endl; };
//	void sk2() { cout << "sk2" << endl; };
//	void sk3() { cout << "sk3" << endl; };
//};
//内存模型：
//Hreo(8)
//viability		0
//atk           4



//有虚成员函数（多态）
class Hero {
public:
	int viability;
	int atk;
	virtual void sk1() { cout << "sk1" << endl; };
	virtual void sk2() { cout << "sk2" << endl; };
	virtual void sk3() { cout << "sk3" << endl; };

};
//内存模型：
//Hero(12)--x86   (16)--x64
//{vfptr}	0——————虚函数表指针——指向虚函数表(virtual function table)
//viability	4
//atk		8

//Hero虚函数表——————实例化对象时创建，存放各个虚函数的地址
//&Hero::skill1	0
//&Hero::skill2	1
//&Hero::skill3	2
//注：调用普通函数的效率比调用虚函数高，如果不考虑多态，不要把普通函数设置为虚函数


class XYY :public Hero {
public:
	void sk1() { cout << "X--sk1" << endl; };
	void sk2() { cout << "X--sk2" << endl; };
	void sk3() { cout << "X--sk3" << endl; };
};
//内存模型：
//XYY(12)--x86   (16)--x64
//{vfptr}	0——————虚函数表指针——指向虚函数表(virtual function table)
//viability	4
//atk		8
//虚函数表指针会被继承
//实例化的对象，虚函数表中的函数地址在基类的基础上会被替换
//如果在派生类中没有重定义基类的虚函数，那么虚函数表中对应的那个函数还将使用基类的虚函数

class XYY2 :public XYY {//二级继承，仍有多态，使用其父级的多态
public:
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
		delete ptr;
	}
	cout << "二级继承：" << endl;
	Hero* ptr2 = new XYY2;
	ptr2->sk1();
	ptr2->sk2();
	ptr2->sk3();
}


//静态多态与动态多态
//静态多态：也称为编译时的多态；在编译时就已经确定要执行的函数的地址了；主要方式有函数重载和函数模板
//动态多态：即动态绑定，在运行时才去确定对象类型和选择需要调用的函数，一般用于解决基类指针或引用  指向 派生类，并调用类中重写的方法时出现的问题