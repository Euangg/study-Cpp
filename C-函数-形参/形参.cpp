#include<iostream>
using namespace std;

void test(int a) {
	a--;
	cout << a << endl;
}//形参的值可以被修改

void main() {
	test(5);
}
