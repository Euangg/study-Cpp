//异常规范
//C++98标准提出了异常规范，目的是为了让使用者知道函数可能会引发哪些异常
//void func1()throw(A,B,C);		//表示该函数可能会抛出A、B、C类型异常
//void func2()throw();			//表示该函数不会抛出异常
//void func3();					//该函数不符合C++98的异常规范

//C++11标准弃用了C++98的异常规范，使用新增的关键字noexcept指出函数不会引发异常
//void func4() noexcept			//表示该函数不会抛出异常
//在实际开发中，不会加，弃用异常已是共识，且没必要多此一举

//关键字noexcept也可以用作运算符，判断表达式（操作数 ）是否可能引发异常； 
//如果表达式可能引发异常，返回false
//否则返回true

#include<iostream>
using namespace std;

int main() {
	//分配一大块内存
	double* ptr = nullptr;
	/*try {
		ptr = new double[100000000];

	}
	catch(bad_alloc&){
		cout << "分配内存失败" << endl;

	}*/

	//new运算符不抛出异常版本
	ptr = new(std::nothrow)double[100000000];
	if (ptr == nullptr)cout << "分配内存失败" << endl;

	
	if (ptr != nullptr)delete[] ptr;


}
