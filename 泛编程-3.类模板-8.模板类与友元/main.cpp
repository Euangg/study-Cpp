//模板类的友元函数有三类：
//1).非模板友元：友元函数不是模板函数，而是利用模板类参数生成的函数
//2).约束模板友元：模板类实例化时，每个实例化的类对应一个友元函数
//3).非约束模板友元：模板类实例化时，如果实例化了n个类，也会实例化n个友元函数，每个实例化的类都拥有n个友元函数

#include<iostream>
using namespace std;

//【约束模板友元】：模板类实例化时，每个实例化的类对应一个友元函数
//2-1.在模板类的定义前面，声明友元函数模板
template<typename T>
void show4(T& a);
//目的是为了让模板类AA知道友元函数模板的存在

template<class T1,class T2>
class AA {
	//2-2.在模板类中，再次声明友元函数模板
	friend void show4<>(AA<T1, T2>& a);
	//目的是为了让编译器知道需要实例化的友元函数模板
	//类模板和函数模板本来是扯不上关系的，这行代码让它们扯上了关系
	//导致：编译器在实例化某种数据类型的模板时，也会实例化这种数据类型的模板函数

	T1 m_x;
	T2 m_y;
public:
	AA(const T1 x, const T2 y) :m_x(x), m_y(y) {};
	friend void show();
	friend void show2(const AA<int, string>& a);


	friend void show3(const AA<T1, T2>& a) {
		cout << "x=" << a.m_x << ",y=" << a.m_y << endl;
	}//编译器利用模板参数帮我们生成友元函数
	//但是，这个函数不是模板函数
	//如果与show1()、show2()同名，将会出现重定义错误
	//编译器创建模板类实例的时候，会用这些代码生成友元函数的实体，会和同名的友元的代码冲突，所以出现了重定义
	//所以，如果想为某种数据类型创建特别版本的友元函数（具体化），这种方法是做不到的——还会阻碍其他想要使用的特别版本
	//还有，这种方法生成的友元函数只能用于这个模板类，不能用于其他模板类
	//这种友元叫【非模板友元】，只能在类内实现（特点）
};

AA<int, string>a(999, "xyy");

void show() {
	cout << "x=" << a.m_x << ",y=" << a.m_y << endl;
}
void show2(const AA<int,string>& a) {
	cout << "x=" << a.m_x << ",y=" << a.m_y << endl;

}

//2-3友元函数模板的定义
template<typename T>
void show4(T& a) {
	cout << "通用：x=" << a.m_x << ",y=" << a.m_y << endl;
}
//满足2-1与2-2，可以用于多个模板类
//1.可以具体化
//2.可以用于多个模板类
//这种友元方案更有价值，语法稍微麻烦一点

//2-3-x因为友元函数是函数模板，所以可以有具体化版本
template<>
void show4(AA<int, string>& a) {
	cout << "具体<int,string>:x=" << a.m_x << ",y=" << a.m_y << endl;
}


//3.【非约束模板友元】：模板类实例化时，如果实例化了n个类，也会实例化n个友元函数，每个实例化的类都拥有n个友元函数——不合理
template<class T1,class T2>
class BB {
	template<typename T>friend void show5(T& a);
	T1 m_x;
	T2 m_y;
public:
	BB(const T1 x, const T2 y) :m_x(x), m_y(y) {};

};

template<typename T>
void show5(T& b) {
	cout << "通用：x=" << b.m_x << ",y=" << b.m_y << endl;
}

template<>
void show5(BB<int, string>& b) {
	cout << "具体化BB<int, string>：x=" << b.m_x << ",y=" << b.m_y << endl;
}
//与2表面上没有任何区别


int main() {
	show();

	AA<int, string>a2(666, "Suu");
	show2(a2);

	AA<char, string>a3(97, "shiningsung");
	show3(a3);

	AA<int, string>a4(98, "1asy");
	show4(a4);//将使用具体化版本
	AA<char, string>a5(99, "xxxx");
	show4(a5);//将使用通用化版本


	BB<int, string>b4(98, "1ase");
	show5(b4);
	BB<char, string>b5(99, "xxxx");
	show5(b5);
}