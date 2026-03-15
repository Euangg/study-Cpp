//queue和stack其实不叫容器(container)，而是叫适配器(adapter)
//他们是对容器的再封装

//queue，是一种操作受限的线性表，限制为：只允许再队首删除(出队)，队尾插入(入队)，先进先出
//在stl中，其底层容器未deque(双端队列)和list(双向链表)，其中deque为默认底层容器
//queue是一个典型的数据缓冲构造

#include<iostream>
#include<queue>
#include<string>
using namespace std;


void test1() {
	queue<string> q;

	//插入三个元素到队列
	q.push("These ");
	q.push("are ");
	q.push("more than ");

	//从队列读取出两个元素
	cout << q.front(); q.pop();
	cout << q.front(); q.pop();

	//再插入两个元素
	q.push("four ");
	q.push("words!");

	//出一个元素
	q.pop();

	//从队列读取出两个元素
	cout << q.front(); q.pop();
	cout << q.front() << endl;
	q.pop();

	//显示队列中元素的数量
	cout << "number of elements in the queue: " << q.size() << endl;
}

void test2() {
	queue<int> a;

	for (int i = 1; i <= 100; i++) {
		a.push(i);
		cout << a.back()<<","<< a.front() << endl;
	}

	//下标访问//不行
	//cout << a[5] << endl;、
	//a.at(5)
	
	//迭代器//md没有迭代器

	//设计上不让访问两端之间的元素
}

int main(){
	test2();
}