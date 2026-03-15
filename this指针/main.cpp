#include<iostream>
using namespace std;

class CGirl {
public:
	string m_name;
	int m_yz;

	CGirl(const string &name, int yz) {
		m_name = name;
		m_yz = yz;
	};

	void show() const {
		
		cout << "姓名：" << m_name << endl;
	};

	const CGirl& pk(const CGirl& g)const{
		if (g.m_yz < m_yz)return g;
		return *this;
	}

	int aa;
	int func(int aa) {
		//aa = aa;//函数体内的变量名优先找形参
		this->aa = aa;
	}
};

const CGirl& pk(const CGirl& gg1, const CGirl& gg2) {//不需要修改形参，加const约束//C风格（非C++一切皆对象）
	if (gg1.m_yz < gg2.m_yz)return gg1;
	return gg2;
}

int main() {
	CGirl g1("icey", 5), g2("feng", 3), g3("3", 3), g4("4", 4), g5("dream", 2);
	//const CGirl& g3 = pk(g1, g2);
	//const CGirl& g3 = g1.pk(g2);
	const CGirl& g = g1.pk(g2).pk(g3).pk(g4).pk(g5);
	g.show();
}