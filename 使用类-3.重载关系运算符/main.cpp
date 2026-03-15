#include<iostream>
using namespace std;	//指定缺省命名空间

class CGirl {
	string m_name;
	int m_yz;
	int m_sc;
	int m_acting;
public:
	CGirl(string name, int yz, int sc, int acting) { m_name = name; m_yz = yz; m_sc = sc; m_acting = acting; };

	bool operator==(const CGirl& g1) {
		if ((m_yz + m_sc + m_acting) == (g1.m_yz + g1.m_sc + g1.m_acting))return true;
		return false;
	}

	bool operator>(const CGirl& g1) {
		if ((m_yz + m_sc + m_acting) < (g1.m_yz + g1.m_sc + g1.m_acting))return true;
		return false;
	}

	bool operator<(const CGirl& g1) {
		if ((m_yz + m_sc + m_acting) > (g1.m_yz + g1.m_sc + g1.m_acting))return true;
		return false;
	}
};

int main() {
	CGirl g1("xs",1,3,6), g2("dream",3,4,3);
	if (g1 == g2) {
		cout << "相等" << endl;
	}
	else if (g1 > g2) {
		cout << "xs" << endl;
	}
	else if (g1 < g2) {
		cout << "dream" << endl;
	}
}