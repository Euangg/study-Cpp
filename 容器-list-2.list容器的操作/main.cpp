//特性操作
//size_t size() const;//返回容器的实际大小（已使用的空间）
//bool empty() const;//判断容器是否为空
//void clear();//清空容器
//void resize(size_t size);//把容器的实际大小置为size

//元素操作
//T& front();
//const T& front();
//T& back();
//const T& back();

//赋值操作


//交换操作


//比较操作



#include<list>
#include<iostream>
using namespace std;

class myClass {
	int m_1;
	int m_2;
public:
	myClass(int m1, int m2) {
		m_1 = m1;
		m_2 = m2;
	}
	void show() {
		cout << "m_1=" << m_1 << ", m_2=" << m_2 << endl;
	} 
	
	bool operator ==(const myClass& c1) const {
		return this->m_1 == c1.m_1 && this->m_2 == c1.m_2;
	}//如果在容器方法中有检测（例如list::remove），两个const必不可少
	/*bool operator ==(myClass& c1) {
		return this->m_1 == c1.m_1 && this->m_2 == c1.m_2;
	}*/

};
void test1() {
	list<int> l1 = { 1,2,3,4,5,6,6,6,7,8,9,10 };

	for (auto val : l1) {
		cout << val << " ";
	}
	cout << endl;

	l1.remove(6);
	for (auto val : l1) {
		cout << val << " ";
	}
	cout << endl;

	myClass c1(2, 3);
	myClass c2(1, 4);
	myClass c3(2, 4);
	myClass c4(7, 3);
	myClass c5(2, 3);

	myClass c6(66, 66);

	if (c1 == c5) {
		cout << "c1==c5" << endl;
	}
	else {
		cout << "c1!=c5" << endl;
	}

	list<myClass>l2 = { c1,c6 };
	/*l2.push_back(c1);
	l2.push_back(c6);*/
	for (auto val : l2) {
		cout << "::";
		val.show();
	}
	cout << endl;



	cout << "remove c2(1,4)..." << endl;
	//remove(l2.begin(),l2.end(),c5);//std::remove只是通过迭代器的指针向前移动来删除，将没有删除的元素放在链表的前面，并返回一个新的指向尾后的迭代器（这个新的尾后迭代器要自己保留并使用，不会刷新到容器新的迭代器中）
	l2.remove(c2);//链表的list::remove会改变容器的size
	//l2.erase()
	for (auto val : l2) {
		cout << "::";
		val.show();
	}
	cout << endl;

	cout << "remove c3(2, 4)..." << endl;
	l2.remove(c3);
	for (auto val : l2) {
		val.show();
	}
	cout << endl;

	cout << "remove c4(7, 3)..." << endl;
	l2.remove(c4);
	for (auto val : l2) {
		val.show();
	}
	cout << endl;

	cout << "remove c5(2, 3)..." << endl;
	l2.remove(c5);
	for (auto val : l2) {
		val.show();
	}
}

void test2() {
	list<int>lst{};
	auto it = lst.begin();//空list，begin直接取到end()
	if (it != lst.end()) { cout << "it!=lst.end()" << endl; }
	else cout << "it=lst.end()" << endl;
}

int main() {
	test2();
}