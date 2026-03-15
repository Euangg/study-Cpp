#include<iostream>
using namespace std;
//long 4byte -2147483648~2147483647
//Ïàµ±ÓÚint
int main(int argc, char* argv[]) {
	long l;
	cout << "sizeof(l)=" << sizeof(l) << endl;
	l = INT32_MAX;
	cout << l << endl;
	l++;
	cout << l << endl;

}