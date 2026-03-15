#include<iostream>
using namespace std;
//优先级
void test1() {
	cout << "5+3>4="<< (5 + 3 > 4) << endl;//输出1，表示真，5+3先算
	cout << "5+(3>4)="<< (5 + (3 > 4)) << endl;//输出5，表示5+false(0)

	//算数运算符 优先级 高于 关系运算符
}

int main() {
	test1();
}
