

//可重载的一元运算符：
//1).++自增		2).--自减		3).!逻辑非		4).&取地址
//5).~取反码	6).*解引用		7).+一元正		8).-一元负
//一元运算符通常出现在它们所操作的对象的左边
//++、--有前后置之分


#include<iostream>
using namespace std;

class A {
public:
	string m_name;
	int m_ranking;

	A() { m_name = "xxx"; m_ranking = 5; };
	void show()const { cout << m_name << "," << m_ranking << endl; };

	A& operator ++() {//无形参，重载前置
		m_ranking++;
		return *this;
	}

	//不符合后置优先级的++
	//A& operator ++(int) {//加一个int形参，重载后置
	//	m_ranking++;
	//	return *this;
	//}

	//符合后置优先级的++
	A operator++(int) {
		A tmp = *this;
		m_ranking++;
		return tmp;//临时对象不能返回引用
	}

};

int main() {
	int i = 0;
	++(++(++i));
	cout << i << endl;

	int x = 5, y = 5;
	int xx = ++(++(++x)); cout << "xx=" << xx << ",x=" << x << endl;//前置的自增可以嵌套
	int yy = y++; cout << "yy=" << yy << ",y=" << y << endl;//后置的自增不能嵌套

	A a1, a2;
	A a3 = ++(++(++a1)); cout << "a3:" << a3.m_ranking << ",a1:" << a1.m_ranking << endl;
	A a4 = a2++; cout << "a4:" << a4.m_ranking << ",a2:" << a2.m_ranking << endl;



	A a;
	a.show();
	++a;
	++(++(++a));
	a.show();
	a++;
	a.show();

	

}
