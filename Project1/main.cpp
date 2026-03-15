//typeid运算符用于获取数据类型的信息
//语法：
//		1) typeid(数据类型);
//		2) typeid(变量名或表达式);
//typeid运算符返回type_info类对象的引用<typeinfo>
//type_info类的实现随编译器而异，但至少有name()成员函数，返回一个字符串（通常是类名）(一般用于调试，没什么大用)

//type_info重载了==和!=运算符，用于对类型进行比较


#include<iostream>

using namespace std;


class AA {
public:
	AA() {};

};

int main() {
	//typeid 用于内置数据类型
	int ii = 3;
	int* pii = &ii;
	int& rii = ii;


	cout << "typeid(int)=" << typeid(int).name() << endl;
	cout << "typeid(ii)=" << typeid(ii).name() << endl;
	cout << "typeid(int*)=" << typeid(int*).name() << endl;
	cout << "typeid(pii)=" << typeid(pii).name() << endl;
	cout << "typeid(int&)=" << typeid(int&).name() << endl;
	cout << "typeid(rii)=" << typeid(rii).name() << endl;
	

	cout << "-------------------------------------------------" << endl;
	//typeid用于自定义数据类型
	AA aa;
	AA* paa = &aa;
	AA& raa = aa;
	cout << "typeid(AA)=" << typeid(AA).name() << endl;
	cout << "typeid(aa)=" << typeid(aa).name() << endl;
	cout << "typeid(AA*)=" << typeid(AA*).name() << endl;
	cout << "typeid(paa)=" << typeid(paa).name() << endl;
	cout << "typeid(AA&)=" << typeid(AA&).name() << endl;
	cout << "typeid(raa)=" << typeid(raa).name() << endl;



	if (typeid(AA) == typeid(aa)) {
		cout << "类型符合1" << endl;
	}
	if (typeid(AA) == typeid(*paa)) {
		cout << "类型符合2" << endl;
	}
	if (typeid(AA) == typeid(raa)) {
		cout << "类型符合3" << endl;
	}
}


//注：
//1).type_info类的构造函数是private属性，也没有拷贝构造函数，所以不能直接实例化，只能由编译器在内部实例化
//2).不建议用name()成员的返回值作为判断数据类型的依据（编译器可能会转换类型名，而且不同编译器返回值不同）
//3).typeid运算符可以用于多态的场景，在运行阶段识别对象的数据类型——————typeid(基类指针解引用)==typeid(派生类)
//4).typeid(*ptr)，如果ptr是nullptr，而且ptr为多态类型，将发生bad_typeid异常