#include<iostream>
using namespace std;

//引用是指针常量的伪装（不能修改指向的指针——数据类型* const 变量名）
//程序员拥有引用，而编译器只拥有指针

//指针常量：数据类型* const 变量名——指向的对象不可改变
//1.由于指向的对象不可变，所以在定义的时候必须初始化，否则没有意义——（不初始化，改指向）编译都会报错
//2.可以通过解引用的方法修改内存中的值

int main() {
	int a = 3;				//声明普通的整型变量
	int& ra = a;			//创建引用ra，让其成为a的别名
	int* const rb = &a;		//声明指针常量rb，让它指向变量a

	cout << "a=" << a << ",&a=" << &a << endl;
	cout << "ra=" << ra << ",&ra=" << &ra << endl;
	cout << "*rb=" << *rb << ",rb=" << rb << endl;
}