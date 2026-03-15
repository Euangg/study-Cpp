#include<iostream>
#include<vector>
#include<list>
using namespace std;

//单向链表节点
struct Node {
	int item;
	Node* next;
};

int* find_(int* arr, int n, const int& val) {
	for (int i = 0; i < n; i++)
		if (arr[i] == val)return &arr[i];
	return nullptr;
}

int* find_(int* begin, int* end, const int& val) {
	for (int* iter = begin; iter != end; iter++)
		if (*iter == val)return iter;
	return nullptr;
}
//第二个参数为数组的尾后地址（不是尾地址！）

Node* find_(Node* head, const Node& val) {
	for (Node* iter = head; iter != nullptr; iter = iter->next)
		if (iter->item == val.item)return iter;
	return nullptr;
}


template<typename T1,typename T2>
T1 find_(T1 begin, T1 end, const T2& val) {
	for (T1 iter = begin; iter != end; iter++)
		if (*iter == val)return iter;
	return end;
}

//STL把各种数据结构封装成了容器，每个容器都有一个迭代器
//迭代器提供了访问容器元素的通用方法
//如果使用迭代器，不同的容器，访问元素的方法是相同的
//迭代器支持的基本操作有：赋值（=）、解引用（*）、比较（==和!=）、遍历（++）
//一般情况下，迭代器是指针和移动指针的方法，在某些容器中迭代器是指针，在某些容器中迭代器是类（封装了指针和移动指针的方法）

void test1() {
	//在vector容器中查找元素
	vector<int> v = { 1,2,3,4,5,6 };
	vector<int>::iterator it1 = find_(v.begin(), v.end(), 3);
	if (it1 != v.end())cout << "查找成功" << endl;
	else cout << "查找失败" << endl;

	//在list容器中查找元素
	list<int> l = { 1,2,3,4,5,6,7 };
	list<int>::iterator it2 = find_(l.begin(), l.end(), 3);
	if (it2 != l.end())cout << "查找成功" << endl;
	else cout << "查找失败" << endl;

//迭代器有五种分类：
//1）正向迭代器：
//		容器名<元素类型>::iterator 迭代器名——正向迭代器
//		容器名<元素类型>::const_iterator 迭代器名——常正向迭代器（不可修改元素）
//		只能使用++运算符来遍历容器，每次沿容器逻辑结构向右移动一个元素。例如，单向链表由于其逻辑结构，只能支持正向迭代器
//		如果容器提供正向迭代器，会提供6个成员函数：
//			iterator begin();
//			iterator end();
//			const_iterator begin();
//			const_iterator end();
//			const_iterator cbegin();//配合auto使用（可以简化类型声明）
//			const_iterator cend();//配合auto使用
	vector<int> v2 = { 1,2,3,4,5 };
	vector<int>::iterator it3 = v2.begin();
	*it3 = 8;
	it3++;//迭代器后移
	*it3 = 7;
	for (auto it4 = v2.cbegin(); it4 != v2.end(); it4++)
		cout << *it4 << " ";
	cout << endl;


//2）反向迭代器（双向迭代器）：
//		容器名<元素类型>::reverse_iterator 迭代器名——反向迭代器
// 		容器名<元素类型>::const_reverse_iterator 迭代器名——常反向迭代器
//		具备正向（从右到左）和反向（从左到右）遍历的容器。例如，双向链表
//		如果容器支持反向迭代器，会提供4个成员函数：
//		reverse_iterator rbegin();
// 		reverse_iterator rend();
//		const_reverse_iterator crbegin();
//		const_reverse_iterator crend();
//		注：rbegin与rend对应正向迭代器的end与begin	，++操作往左，--操作往右

//3）随机访问迭代器：
//		具备双向迭代器的功能，还支持：
//			1.用于比较两个迭代器位置关系的运算符（<、<=、>、>=），得到新的位置
//			2.迭代器和一个整数值的加减运算(+、+=、-、-=)
//			3.下标运算符（iter[n]）
//		注：数组的指针是原生的随机访问迭代器
//		只有物理存储结构是数组的容器才有这种迭代器，例如string、vector、deque

//4）输入和输出迭代器
//		它们不是把容器当作操作对象，而是把输入/输出流作为操作对象


	//关于vector容器的构造函数
	vector<int> v3 = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v4(v3.cbegin() + 2, v3.cend() - 3);

	for (auto it = v4.crbegin(); it != v4.crend(); it++)//正向迭代器的++与反向迭代器的移动方向相反
		cout << *it << " ";

	auto it5 = v4.insert(v4.begin() + 2, 22);
	cout << "新插入的元素是" << *it5 << endl;

	for (auto it = v4.cbegin(); it != v4.cend(); it++)
		cout << *it << " ";
	cout << endl;

	//迭代器失效
	//resize()、reserve()、assign()、pushback()、pop_back()、insert()、erase()等函数
	//会引起vector容器的动态数组发生变化，可能导致vector迭代器失效
	vector<int> v5 = { 1,2,3,4,5 };
	//for (auto it = v5.cbegin(); it != v5.cend(); it++) {
	//	cout << *it << " ";
	//	v5.erase(it);//会导致迭代器失效而出现问题
	//}

	for (auto it = v5.cbegin(); it != v5.cend(); ) {
		cout << *it << " ";
		it=v5.erase(it);//erase会返回该迭代器的下一个迭代器
	}
	cout << endl << "v5.size()=" << v5.size() << endl;
}

//迭代器越界
void test2() {
	vector<int>v1 = { 1,2,3 };

	auto i = v1.end();

	//cout << "*i=" << *i << endl;//运行报错，不能解析超过范围的迭代器

	i++;//运行报错，不能超范围迭代
}

int main() {
	test2();
};