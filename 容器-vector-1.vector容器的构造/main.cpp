//vector容器封装了动态数组
//之前的string容器也封装了动态数组，但它是数组的一个特例，只封装了字符数组

//vector类模板的声明：
//template<class T,class Alloc=allocator<T>>
//class vector{
//private:
//	T* start_;
//	T* finish_;//已使用空间的尾地址（从该地址起（包含该地址）往后的内存空间为其他内存）
//	T* end_;//动态分配内存块的尾地址（注意点同上，范围和边界）
//	.......
//}
//模板参数1：容器存放的数据类型
//			2：指定分配器，缺省使用STL提供的分配器
//分配器：分配器是一个管理内存的模板类，STL提供的分配器叫allocator，用new和delete分配和释放内存


#include<iostream>
#include<vector>
using namespace std;

void pro_construct() {
	vector<int> v1;
	cout << v1.capacity() << "," << v1.size() << endl;//0,0
	//vector容器缺省不会分配内存空间

	vector<int>v2{};
	cout << v2.capacity() << "," << v2.size() << endl;//0,0
	//vector容器空白初始化列表不会分配内存空间

	vector<int>v3{1,2,3};
	cout << v3.capacity() << "," << v3.size() << endl;//3,3

	vector<int>v4(5);
	cout << v4.capacity() << "," << v4.size() << endl;//5,5
	for (auto& d : v4)cout << d << endl;//全是0

	vector<int>v5(6,99);
	cout << v5.capacity() << "," << v5.size() << endl;//6,6
	for (auto& d : v5)cout << d << endl;//全是99
}

void pro_resie() {
	vector<int>v;

	v.resize(3);//改变capacity和size
	cout << v.capacity() << "," << v.size() << endl;//3,3
	for (auto& d : v)cout << d << endl;//全是0
}
void pro_resize2() {
	vector<int> v{1,2,3,4,5};
	cout << v.capacity() << "," << v.size() << endl;//5,5
	for (auto& d : v)cout << d << endl;

	v.resize(3);
	cout << v.capacity() << "," << v.size() << endl;//5,3
	for (auto& d : v)cout << d << endl;///1,2,3

	//resize第二个参数
	v.resize(2, 0);
	cout << v.capacity() << "," << v.size() << endl;//5,2
	for (auto& d : v)cout << d << endl;///1,2

	v.resize(4, 0);
	cout << v.capacity() << "," << v.size() << endl;//5,4
	for (auto& d : v)cout << d << endl;///1,2,0,0
	//第二个参数只对超出当前size部分的元素生效
}

void pro_beyond() {
	vector<int> v{ 1,2,3 };
	cout << v[3] << endl;
	//运行时报错
}
void pro_beyond2() {
	vector<int>v(5);
	v.clear();
	cout << v.capacity() << "," << v.size() << endl;//5,0
	for (auto& d : v)cout << d << endl;//无输出
	v[0] = 5;
	//运行时报错，在capacity范围内越界也不行
}

void pro_reserve() {
	vector<int>v;

	v.reserve(3);//仅改变capacity不会添加新元素
	cout << v.capacity() << "," << v.size() << endl;//3,0
	for (auto& d : v)cout << d << endl;//无输出
}

void pro_clear() {
	vector<int>v{1,2,3,4};
	v.clear();
	cout << v.capacity() << "," << v.size() << endl;//4,0
	for (auto& d : v)cout << d << endl;//无输出
}

void pro_assign() {
	vector<int> v(10);

	//assign可以初始化所有元素的值
	v.assign(v.size(), 99);
	cout << v.capacity() << "," << v.size() << endl;//10,10
	for (auto& d : v)cout << d << endl;//全99

	v.assign(2, 3);
	cout << v.capacity() << "," << v.size() << endl;//10,2
	for (auto& d : v)cout << d << endl;//全2
	//assign会改变size，size不超过capacity不会改capacity

	v.assign(15, 44);
	cout << v.capacity() << "," << v.size() << endl;//15,15
	for (auto& d : v)cout << d << endl;//全44
	//assign会改变capacity（必要时）
}

void test3() {
	vector<char> v1 = { 'h','e','l','l','o','W','o' };
	cout << "v1.capacity()=" << v1.capacity() <<
		", v1.size()=" << v1.size() << endl;//7,7

	auto i = v1.begin();
	v1.insert(i, 'k');//在i之前插入元素，迭代器会失效
	i = v1.begin();
	cout << *i << endl;
	for (auto e : v1)cout << e;
	cout << endl;
	v1.erase(++i);//删除i元素，迭代器会失效
	cout << *i << endl;
	for (auto e : v1)cout << e;
}


int main() {
	//pro1();
	pro_assign();
}