//不定数的值组

#include<tuple>
#include<iostream>
#include<string>
using namespace std;

void test() {
	tuple<int, float, string> t1 = { 41, 6.3f, "niko" };
	cout << get<0>(t1) << endl;
	cout << get<1>(t1) << endl;
	cout << get<2>(t1) << endl;
	get<2>(t1) = "simple";//可以修改值
	cout << get<2>(t1) << endl;
}

int main() {
	test();
}