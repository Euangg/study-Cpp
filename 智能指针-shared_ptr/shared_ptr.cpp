#include<memory>
#include<iostream>
#include<list>
#include<vector>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;
using std::list;

//赋值操作是否会reset？会
void test2() {
	auto sptr1 = std::make_shared<int>(21);
	auto sptr2 = std::make_shared<int>(8228);
	auto sptr3 = sptr1;
	cout << "sptr1:" << sptr1.use_count() << endl;//2
	cout << "sptr2:" << sptr2.use_count() << endl;//1
	sptr3 = sptr2;
	cout << "sptr1:" << sptr1.use_count() << endl;//1
	cout << "sptr2:" << sptr2.use_count() << endl;//2
}

//存入list
void test3() {
	auto ptr1= std::make_shared<int>(21);
	cout << sizeof(ptr1) << endl;//一个shared_ptr智能指针大小为8
	std::list<std::shared_ptr<int>>list;
	//list.push_back(ptr1);//引用计数+1
	list.push_back(std::move(ptr1));//移动语义，不会增加计数
	for (auto& p : list)cout  << p.use_count() << endl;
	list.clear();
	for (auto& p : list)cout << p.use_count() << endl;
}

//绑定原生指针检测？可以，但是危险
void test4() {
	auto ptr1 = std::make_shared<int>(21);
	auto* pptr = &ptr1;//不会增加引用计数
	cout << ptr1.use_count() << endl;
	cout << **pptr << endl;
	ptr1.reset();
	cout << ptr1.use_count() << endl;
	cout << **pptr << endl;//如果指针已没有东西，二级解会崩溃
}

//容器中的释放？
void test5() {
	std::vector<std::shared_ptr<int>>vect;
	vect.push_back(std::make_shared<int>(21));//原地构造，只算一次引用
	cout << vect[0].use_count() << endl;
	auto* pptr = &vect[0];
	cout << pptr << "," << pptr->use_count() << endl;
	//vect.clear();//会释放引用计数
	vect.pop_back();//会释放引用计数
	cout << pptr<<"," << pptr->use_count() << endl;
}

//移动语义高效传递
list<shared_ptr<int>> listInt;
shared_ptr<int> test6_1() {
	shared_ptr<int> p = make_shared<int>(6);
	listInt.push_back(p);
	return p;
}
shared_ptr<int> test6_2() {
	shared_ptr<int> p = make_shared<int>(6);
	listInt.push_back(p);
	return std::move(p);
}
void test6() {
	//shared_ptr<int> p2=test6_1();
	shared_ptr<int> p2=std::move(test6_2());
	p2.reset();
}

int main() {
	test2();
	//test3();
	//test4();
	//test5();
	//test6();
}