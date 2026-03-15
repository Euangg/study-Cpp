//explict可以使转换函数的调用更明确、可控
//C++98中不能将explict用于转类型的转换函数，C++11消除了此限制


#include<iostream>
using namespace std;
class Cat {
public:
	int age_ = 99;
public:
	explicit operator int() { return age_; };
};

int main() {
	Cat cat1;
	//cout << cat1 << endl; 不再允许
	cout << (int)cat1 << endl;

}