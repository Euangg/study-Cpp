#include<iostream>
using namespace std;

//常量是程序中固定不变的数据
//常量类型（2）
//1.宏常量//一般在main函数上声明，大写命名(约定习惯，非强制)
#define MONTHS	12
#define PI		3.1415926


//2.const修饰常量//在程序的任何地方都可声明
const int days = 7;

int main() {
	cout << "a year" << MONTHS << endl;
	cout << "a week" << days << endl;
	cout << "π" << PI << endl;

	return 0;
}