//基类的虚函数实现基本功能
//派生类重定义虚函数，扩展功能、提升性能
//		或者实现个性化功能

#include<iostream>
using namespace std;

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
	
}