//创建常量的方法（3）
//·宏常量，用预处理命令#define创建
//·用const修饰的变量
//·枚举

//指定类型的枚举
enum Etest1 :char {
	E_a=97,
	E_b,
	E_c,
	E_d,
	E_e,
};
struct Point{
	int x;
	int y;
};

//enum ECPoint :Point {//不行啊，枚举的基础类型必须是整型
//};

//enum			不限定范围的枚举类型
//enum class	枚举类（限定作用域的枚举类）+

#include<iostream>
using namespace std;
int main() {
	cout << E_a << endl;

	return 0;
}

