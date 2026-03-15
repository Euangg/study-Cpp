//模板类最常用的就是作为容器类
//C++标准库：栈、数组、链表、二叉树和哈希表等，都是用模板类实现的

#include<iostream>
using namespace std;


template<class DataType>
class Stack {//栈类
private:
	DataType* items;//栈数组
	int stacksize;//栈实际大小
	int top;//栈顶指针(指向待装填的空位)
public:
	//构造函数：1.分配栈数组内存；2.把栈顶指针初始化为0
	Stack(int size) :stacksize(size), top(0) {
		items = new DataType[stacksize];
	}

	~Stack() {
		delete[] items;
		items = nullptr;
	}

	//判断栈是否为空
	bool isempty()const {
		/*if (top == 0)return true;
		return false;*/

		return top == 0;
	}

	//判断栈是否已满
	bool isfull()const {
		return top == stacksize;
	}
	//元素入栈
	bool push(const DataType& item) {
		if (top < stacksize) {
			items[top++] = item;
			return true;
		}
		return false;
	}
	//元素出栈
	bool pop(DataType& item) {
		if (top > 0) {
			item = items[--top];
			return true;
		}
		return false;
	}

};


int main() {

	Stack<string> ss(5);

	//int
	//元素入栈
	/*ss.push(18);
	ss.push(238);
	ss.push(184);
	ss.push(128);
	ss.push(1118);
	ss.push(1890);*/
	//元素出栈
	/*int item;
	while (!ss.isempty())
	{
		ss.pop(item);
		cout << item << "\t";
	}
	cout << endl;*/

	//string
	//元素入栈
	ss.push("xxx");
	ss.push("sssu");
	ss.push("shiningsung");
	ss.push("xyy");
	ss.push("suu");
	ss.push("999");
	//元素出栈
	string item;
	while (!ss.isempty())
	{
		ss.pop(item);
		cout << item << "\t";
	}
	cout << endl;

}


//创建模板类的方法：
//先写一个普通类，用具体的数据类型
//调试普通类
//确定普通类的功能没有问题之后，再把普通类改为模板类


//不要一上来就写模板类，模板类调试起来不那么方便