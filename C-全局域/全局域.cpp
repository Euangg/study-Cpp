#include<iostream>
using namespace std;

int a = 0;//全局作用域允许声明操作，声明允许初始化
//a = 99;//报错，全局作用域不允许赋值操作
int main() {

	cout << a;
}