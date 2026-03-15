#include<set>
#include<iostream>
using namespace std;

//基本操作
void test1() {
	set<int> set;//默认创建大小为0
	cout << set.size() << "," << set.empty() << endl;
	for (auto& e : set)cout << e << endl;

	set.insert(1);//插入
	set.insert(1);//重复插入不会改变
	cout << set.size() << "," << set.empty() << endl;
	for (auto& e : set)cout << e << endl;

	set = { 8,9 };//可重新初始化
	for (auto& e : set)cout << e << endl;

	set = { 6,6,6,6 };//重初始化相同的值，也只会有1个
	for (auto& e : set)cout << e << endl;
}

//查找
void test2() {
	set<int> set{ 1,2,3 };
	auto it = set.find(30);
	if (it == set.end())cout << "无" << endl;
	else cout << *it << endl;
}

//不能修改值，只能删除后添加新的

int main() {
	//test1();
	test2();
}