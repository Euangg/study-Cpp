//模板类可以用于函数的参数和返回值，有三种形式：
//1.普通函数，参数和返回值是模板类的实例化版本
//2.函数模板，参数和返回值是某种模板类
//3.函数模板，参数和返回值是任意类型（支持普通类和模板类和其他类型）


#include<iostream>
using namespace std;

template<class T1,class T2>
class AA {//模板类AA
public:
	T1 m_x;
	T2 m_y;
	AA(const T1 x, const T2 y) :m_x(x), m_y(y) {};
	void show()const { cout << "show() x=" << m_x << ",y=" << m_y << endl; }

};

//1-1.采用普通函数，参数和返回值是模板类的实例化版本
//也就是说，这个func()函数只能处理模板类AA无数种数据类型中的一种
AA<int, string> func(AA<int, string>& aa) {
	aa.show();
	cout << "调用了func(AA<int, string>& aa)函数" << endl;
	return aa;
}

//2额外测试
class BB {
public:
	void show() { cout << "调用了BB的show()方法" << endl; }
};

//2.函数模板，参数和返回值用模板类AA
//template<typename T1,typename T2>
//AA<T1, T2> func(AA<T1, T2>& aa) {
//	aa.show();
//	cout << "调用了func(AA<T1, T2>& aa)函数" << endl;
//	return aa;
//}
////其实简单问题复杂化，规范操作如下
//template<typename T>
//T func(T& aa) {
//	aa.show();
//	cout<< "调用了func(T& aa)函数" << endl;
//	return aa;
//}
//上一种方法只支持AA模板类，这一种方法支持任意模板类，还支持普通类
//	但函数中用到了show方法，那么，只要对象有show方法，它都支持

//2-x
void show() {
	cout << "调用了show()函数" << endl;
}
class BB2 {//普通类
public:
	void operator()() {//重载了()运算符（仿函数）
		cout << "调用了BB类的仿函数" << endl;
	}
};
template<typename T>
void func(T tt) {
	tt();
}

int main() {
	AA<int, string> aa(999, "xyy");//能同时匹配普通函数和函数模板，将优先使用普通函数
	func(aa);

	/*AA<char, string>aa2(97, "Suu");
	func(aa2);
	BB bb;
	func(bb);*/

	//2-x
	BB2 bb2;
	func(bb2);//实参是类
	func(show);//实参是函数指针
	//func是函数模板，不管传进去的是什么，只要适应函数中的代码就行
}