#include<iostream>
using namespace std;


void test() {
	typedef string AddressLines[4];

	string* pal = new AddressLines;//注意本质上是new string[4]
	delete[] pal;//很好！
	//为避免这种容易犯错的情况，
	//最好尽量不要对数组形式做typedef
}

int main() {
	string* stringArray = new string[100];
	delete stringArray;//删除一个对象
	delete[] stringArray;//删除一个由对象组成的数组

	//当使用new（也就是通过new动态生成一个对象）：
	//1.内存被分配出来（通过名为operate new的函数）
	//2.针对此内存会有一个（或更多）构造函数被调用
	//delete反之

	//数组所用的内存通常还包括“数组大小”的记录
	//以便delete知道需要调用多少次析构函数
}