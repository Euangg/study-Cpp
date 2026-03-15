//list类模板的声明
//template<class T, class Alloc = allocator<T>>
//class list {
//private:
//	iterator head;
//	iterator tail;
//	..........
//};
//模板参数：1.class T：填链表元素的数据类型（C++内置的数据类型、结构体、类，都可以）
//			2.class Alloc = allocator<T>：指定分配器
//				缺省是STL提供的分配器，用new和delete分配和释放内存


#include<vector>
#include<list>
#include<iostream>
using namespace std;


int main() {
	//1）.list();//创建一个空的list容器
	list<int>l1;
	//链表没有容量的说法（没有capacity()成员函数）
	cout << "l1.size()=" << l1.size() << endl;
	//2）.list(initializer_list<T> il);//使用统一初始化列表创建list容器
	list<int>l2({ 1,2,3,4,5,6,7,8,9,10 });
	//list<int>l2={ 1,2,3,4,5,6,7,8,9,10 };
	//list<int>l2{ 1,2,3,4,5,6,7,8,9,10 };
	for (int value : l2) {
		cout << value << " ";
	}
	cout << endl;
	//3）.list(const list<T>& l);//拷贝构造函数
	list<int>l3(l2);
	for (int value : l3) {
		cout << value << " ";
	}
	cout << endl;
	//4）.list(iterator first,lterator last);//用迭代器创建list容器
	list<int>l4(l3.begin(), l3.end());
	for (int value : l4) {
		cout << value << " ";
	}
	cout << endl;
	//注：list的迭代器不支持随机访问

	vector<int>v1 = { 1,2,3,4,5,6,7,8,9,10 };
	list<int>l5(v1.begin() + 2, v1.end() - 3);//vector的迭代器支持随机访问
	for (int value : l5) {
		cout << value << " ";
	}
	cout << endl;

	int a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	list<int>l6(a1 + 2, a1 + 10 - 3);//用数组的指针作为迭代器创建list容器
	for (int value : l6) {
		cout << value << " ";
	}
	cout << endl;
	//注：数组的指针是天然的随机访问迭代器，支持迭代器的操作，但不支持迭代器的函数（如begin()、end()）

	
	//如果没有迭代器，在不同容器之间的转换是很麻烦的
	char str[] = "qwerasdfzxcv";//定义C风格字符串
	string s1(str + 1, str + 7);//用C风格字符串创建string容器(左开右闭（以光标为基准舍左取右）)
	for (auto value : s1) {
		cout << value<<" ";
	}
	cout << endl;
	cout << s1 << endl;
	//注：string容器很少使用迭代器，但是它也有迭代器，并且是性能最强的随机访问迭代器

	vector<int>v2(l3.begin(), l3.end());
	for (auto value : v2) {
		cout << value << " ";
	}
	cout << endl;
}

