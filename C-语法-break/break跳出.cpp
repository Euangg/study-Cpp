#include<iostream>
using namespace std;

//测试break跳出几级循环
void test1() {
	int a = 0;
	int b = 0;
	for (; a < 10; a++) {
		b = 0;
		for (; b < 10; b++) {
			if (a == 5 && b == 5)break;
			cout << "(a,b):(" << a << "," << b << ")" << endl;
		}
	}
	//跳出一级
}

//循环与switch混用时
void test2() {
	int a = 0;
	while (a < 10) {
		switch (a){
		case 5:break;
		}
		
		cout << "a=" << a << endl;
		a++;
	}
	//也只跳出switch这一级
}

int main() {
	test2();
}