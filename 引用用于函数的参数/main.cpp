#include<iostream>
using namespace std;

//把函数的形参声明为引用，调用函数的时候，形参将成为实参的别名
//这种方法也叫按引用传递或传引用（传值，传地址，传引用只是说法不同，其实都是传值）
//引用的本质是指针，传递的是变量的地址，在函数中，修改形参会影响实参


//1.传引用的代码更简洁
//2.传引用不必使用二级指针
//3.引用的属性和独特之处

void func(int& ra, int& rb, int& rc) {
	ra = 21;
	rb = 12;
	rc = 6;
}

void func1(int no, string str) {//传值————创建局部变量接受值
	no = 1;
	str = "i";//开始就无依据改变接受参数的局部变量的值，那么传参将没有任何意义
	cout << "dear No." << no << "," << str << endl;
}

void func2(int* pno, string* pstr) {//传地址
	*pno = 2;
	*pstr = "ii";
	cout << "dear No." << *pno << "," << *pstr << endl;
}

void func3(int& no, string& str) {//传引用——调用与传值一样，效果同传地址
	no = 3;
	str = "iii";
	cout << "dear No." << no << "," << str << endl;
}

void pointerAlloc1(int** p) {//二级指针，存放指针的地址，要修改指针的值，要传入指针的地址（二级指针）
	*p = new int(3);
	cout << "alloc1分配的内存地址是：" << *p << "，内存中的值是：" << **p << endl;
}

void pointerAlloc2(int*& p) {//一级指针的引用（别名），实参直接传指针即可修改指针的值
	p = new int(9);
	cout << "alloc2分配的内存地址是：" << p << "，内存中的值是：" << *p << endl;
}

int main() {
	int a = 0;
	int b = 1;
	int c = 2;
	cout << "a=" << a << ",b=" << b << ",c=" << c << endl;

	func(a, b, c);
	cout << "a=" << a << ",b=" << b << ",c=" << c << endl;

	int no = 0;
	string str = "hello!";

	func1(no,str);//传值
	cout << "main:" << "dear No." << no << "," << str << endl;
	func2(&no,&str);//传地址
	cout << "main:" << "dear No." << no << "," << str << endl;
	func3(no, str);//传引用
	cout << "main:" << "dear No." << no << "," << str << endl;


	//2.传引用不必使用二级指针
	int* p = nullptr;
	pointerAlloc1(&p);//二级指针——指针的地址
	cout << "main:p=" << p << ",*p=" << *p << endl;
	pointerAlloc2(p);
	cout << "main:p=" << p << ",*p=" << *p << endl;

	return 0;
}