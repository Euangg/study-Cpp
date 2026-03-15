#include<iostream>
using namespace std;
#include"../X-动态库-4.动态库中封装类/动态库中封装类.h"
#pragma comment(lib,"../Debug/X-动态库-4.动态库中封装类.lib")

int main() {
	CMath math;
	int sum = math.Add(5, 6);
	int sub = math.Sub(5, 6);
	cout << "sum=" << sum << endl;
	cout << "sub" << sub << endl;

}