#include<iostream>
using namespace std;

int main() {
	int a = -99;
	int b = 0;
	int c = 0;
	a < 0 ? cout << "<0" : cout << ">=0";//具备执行性

	cout << endl;
	a < 0 ? b = 99 : c = 99;
	cout << "b=" << b << ",c=" << c << endl;
}
