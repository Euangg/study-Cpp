#include<list>
#include<iostream>
using namespace std;

//插入和删除
//void push_back(const T& value);//在容器尾部追加一个元素
//void push_front(const T& value);//在容器头部插入一个元素
//void emplace_front(...);//在容器头部插入一个元素，...用于构造元素
// 
//void remove(const T& value);//


//remove删除对迭代的影响
void test01() {
	list<int> lst{ 1,2,3,4,5,6,7,8 };
	for (auto& i : lst) {
		cout << i << ",";
		if (i == 6)lst.remove(i);//会导致迭代失效，程序异常中断（先移除，后迭代）
	}

	cout << endl<<"循环后输出" << endl;
	
};
//remove删除对size的影响//从容器中删除值为value的元素，会改变容器的size
void test02() {
	list<int> lst{ 2,1,2,3,4,5,2,2,6,7,8 ,2 };
	cout << lst.size() << endl;
	for (auto& i : lst) cout << i << ",";
	cout << endl;
	lst.remove(2);
	cout << lst.size() << endl;
	for (auto& i : lst) cout << i << ",";
	cout << endl;
}

//erase删除//会改变size
void test03() {
	list<int> lst{ 1,2,3,4,5,6,7,8 };
	cout << lst.size() << endl;
	list<int>::iterator it = lst.begin();
	for (; it != lst.end();) {
		cout << *it << ",";
		if (*it == 8) {
			//lst.erase(it);//迭代器失效
			it=lst.erase(it);//erase后会返回下一个迭代器
			continue;
		}
		++it;
	}
	cout << endl<<lst.size() << endl;
}
//erase迭代中删除语法
void test04() {
	list<int> lst{ 1,2,3,4,5,6,7,8 };
	cout << lst.size() << endl;
	auto it = lst.begin();
	for (; it != lst.end(); ++it) {
		cout << *it << ",";
		if (*it == 1) --(it = lst.erase(it));//如果是第一个元素，异常
	}
	cout << endl << lst.size() << endl;
	it = lst.begin();
	for (; it != lst.end(); ++it) {
		cout << *it << ",";
	}
}

void test05() {
	list<int> lst{ 1,2,3,4,5,6,7,8 };
	int addT = 3;
	cout << lst.size() << endl;
	for (auto it = lst.begin(); it != lst.end();) {
		cout << *it << ",";
		if (*it == 3 && addT) {
			lst.push_back(3);//不会使迭代器失效
			addT--;
		}
		++it;
	}
	cout << endl << lst.size() << endl;
}


int main() {
	//test01();
	test02();
	//test03();
	//test04();
	//test05();

	return 0;
}