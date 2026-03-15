//C++标准库有定长数组和可变数组
//定长数组：array容器（C++11标准新增）
//可变数组：vector容器


//类模板的非通用类型参数:
//注：
//1).通常是整型(C++20标准可以支持其他数据类型)
//2).创建对象的时候必须用常量表达式
//3).模板中不能修改非通用参数的值


#include<iostream>
using namespace std;
//#define MAXLEN 10


//定长数组
template<class T,int len=10>
class Array {
private:
	//T items[MAXLEN];//使用宏
	T items[len];//使用类模板的通用类型参数
public:
	Array() {
		//memset(items, 0, sizeof(items));
	}

	~Array(){}//这个类没有用到堆区内存，所以析构函数什么都不用做

	T& operator[](int ii) {//重载操作符[]，可以修改数组中的元素
		//判断ii合法性
		return items[ii];
	}

	const T& operator[](int ii) const {//重载操作符[]，可以修改数组中的元素
		//判断ii合法性
		return items[ii];
	}
};


//可变数组
template<class T>
class Vector {
private:
	int len;
	T* items;//数组元素
public:
	//默认构造函数，分配内存
	Vector(int size = 10) :len(size) {
		items = new T[len];
	}

	~Vector() {
		delete[] items;
		items = nullptr;
	}
	//扩展数组内存空间
	void resize(int size) {
		if (size <= len)return;//只能往更大扩展
		T* tmp = new T[size];
		for (int ii = 0; ii < len; ii++) {
			tmp[ii] = items[ii];
		}
		delete[] items;//释放原来的数组
		items = tmp;//让数组指针指向新数组
		len = size;
	}
	int size()const { return len; };

	T& operator[](int ii) {//重载操作符[]，可以修改数组中的元素
		//判断ii合法性,如果超过数组长度就扩展
		if (ii >= len)resize(ii + 1);
		return items[ii];
	}

	const T& operator[](int ii) const {//重载操作符[]，可以修改数组中的元素
		//判断ii合法性
		return items[ii];
	}
};

int main() {

	//Array<int>aa;//创建模板类Array的对象
	//aa[0] = 5; aa[1] = 8; aa[2] = 3; aa[3] = 2; aa[4] = 7;

	//for (int ii = 0; ii < 10; ii++) {
	//	cout << aa[ii] << "\t";
	//}
	//cout << endl;


	//Array<string>aa;//创建模板类Array的对象//string是类，里面有一个指向堆区的指针，不能用memset初始化
	//aa[0] = "hello"; aa[1] = "world"; aa[2] = "this"; aa[3] = "is"; aa[4] = "SUU";

	//for (int ii = 0; ii < 10; ii++) {
	//	cout << aa[ii] << "\t";
	//}
	//cout << endl;



	Vector<string> aa(1);//创建模板类Vector对象
	aa[0] = "hello"; aa[1] = "world"; aa[2] = "this"; aa[3] = "is"; aa[4] = "SUU";

	for (int ii = 0; ii < 10; ii++) {
		cout << aa[ii] << "\t";
	}
	cout << endl;
}


//Araay:
//优：在栈上分配内存，容易维护，执行速度快，适合小型数组
//缺：在程序中，不同的非通用类型参数将导致编译器生成不同的类
//		Array<int,10>aa;Array<int,11>aa;Array<int,12>aa

