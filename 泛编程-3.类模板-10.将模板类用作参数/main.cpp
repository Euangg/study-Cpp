//C++的类模板主要目的是为了解决数据结构的问题


//线性表：链表、数组、栈、队列……
//不管是链表还是数组，为了支持任意类型数据，最好的方法是用类模板来实现
#include<iostream>
using namespace std;


template<class T,int len>
class LinkList {		//链表类模板
public:
	T* m_head;			//链表头节点
	int m_len = len;	//链表长
	void insert() { cout << "向链表中插入了一条记录" << endl; };
	void ddelete() { cout << "从链表中删除了一条记录" << endl; };
	void update() { cout << "链表中更新了一条记录" << endl; };
};


template<class T,int len>
class Array {			//数组类模板
public:
	T* m_data;			//数组指针
	int m_len = len;	//数组长度
	void insert() { cout << "向数组中插入了一条记录" << endl; };
	void ddelete() { cout << "从数组中删除了一条记录" << endl; };
	void update() { cout << "数组中更新了一条记录" << endl; };
};
//这些模板类可以存放各种类型的数据，习惯上被称为容器
//都是线性表：
//物理结构不一样，逻辑结构是一样的，所以它们操作数据的方法也是一样的
//模板类的目的就是代码重用，既然链表和数组的逻辑结构是一样的，那就可以把它们作成一个模板类

//C++支持模板的模板——把模板名当成一种特殊的数据类型，实例化对象的时候，可以用模板名作为参数，传给模板

//线性表模板类
template<template<class,int>class tabletype,class datatype,int len>
//template<class,int>class tabletype————容器的通用参数（指定该容器的模板参数为<class,int>）
//template<class,int>标识 参数tabletype不是一个普通的参数（通用数据类型），而是一个模板类，且模板类的模板参数为<class,int>
//即typename要填模板名，而不是int、string等普通的数据类型，
//且要求模板有两个参数（一个是不行的），且第一个参数是通用类型，第二个是int类型（严格）
//注：class可以用typename，只是类模板习惯用class
class LinearList {
public:
	tabletype<datatype, len>m_table;	//创建线性表对象
	//tabletype只是一个模板名，用其创建对象的时候，还需要指定具体的数据类型
	//通用操作：这些数据类型可以从广一级模板的模板参数传入——用LinearList的模板参数从外面传入

	void insert() { m_table.insert(); };
	void ddelete() { m_table.ddelete(); };
	void update() { m_table.update(); };
};


int main() {
	//创建线性表对象，容器类型为链表，链表的数据类型为int，表长为20
	LinearList<LinkList, int, 20>table1;
	table1.insert();
	table1.ddelete();
	table1.update();

	//创建线性表对象，容器类型为数组，数组的数据类型为string，表长为20
	LinearList<Array, string, 20>table2;
	table2.insert();
	table2.ddelete();
	table2.update();

	//线性表的第一个参数是容器的类型，容器都是类模板，所以这个参数填类模板名
	//容器可以不同，但是操作数据的方法（方式种类而非具体操作方式）是相同的
}


//注：
//1.函数模板不支持模板的模板参数
//2.这种方法主要用于数据结构中，其他的场景很少用到，不需要这么复杂的设计