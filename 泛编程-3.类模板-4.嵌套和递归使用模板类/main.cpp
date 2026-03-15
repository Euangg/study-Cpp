//容器的嵌套：
//容器中有容器
//数组元素可以是栈
//栈中元素可以是数组

//递归是嵌套的特殊情况


#include<iostream>
using namespace std;

template<class DataType>
class Stack {
private:
	DataType* items;
	int stacksize;
	int top;
public:
	Stack(int size=3) :stacksize(size), top(0) {
		items = new DataType[stacksize];
	}
	~Stack() {
		delete[] items;
		items = nullptr;
	}
	Stack& operator=(const Stack& v) {//重载赋值函数，实现深拷贝
		delete[] items;//释放原内存（防止原内存有东西，不释放造成内存泄露）
		stacksize = v.stacksize;//栈实际的大小
		items = new DataType[stacksize];//新分配内存
		for (int ii = 0; ii < stacksize; ii++) {
			items[ii] = v.items[ii];//复制数组中的元素
		}
		top = v.top;//栈顶指针
		return *this;
	}
	bool isempty() const {
		return top == 0;
	}
	bool isfull()const {
		return top == stacksize;
	}
	bool push(const DataType& item) {
		if (top < stacksize) { items[top++] = item; return true; }
		return false;
	}
	bool pop(DataType& item) {
		if (top > 0) { item = items[--top]; return true; }
		return false;
	}

};

//template<class T,int len=10>
//class Array {
//private:
//	T items[len];
//public:
//	Array() {};//默认构造函数
//	~Array() {};//析构函数
//	T& operator[](int ii) { return items[ii]; };//重载[]，可修改元素
//	const T& operator[](int ii)const { return items[ii]; };//重载[]，不可修改元素
//};


template<class T>
class Vector{
private:
	int len;
	T* items;
public:
	Vector(int size = 2) :len(size) {
		items = new T[len];
	}
	~Vector() {
		delete[] items;
		items = nullptr;
	}
	Vector& operator=(const Vector& v) {//重载赋值运算符，实现深拷贝
		delete[] items;//释放原内存(没分配也是安全的，保证内存不泄漏)
		len = v.len;
		items = new T[len];//重新分配内存空间
		for (int ii = 0; ii < len; ii++) {
			items[ii] = v.items[ii];
		}
		return *this;
	}
	void resize(int size) {
		if (size <= len)return;
		T* tmp = new T[size];
		for (int ii = 0; ii < len; ii++) {
			tmp[ii] = items[ii];//如果Vector装载的是Stack模板类，会用到Stack类的赋值函数（如果重载赋值函数就是浅拷贝！！）
		}
		delete[] items;
		items = tmp;
		len = size;
	}
	int size()const { return len; };
	T& operator[](int ii) {
		if (ii >= len)resize(ii + 1);
		return items[ii];
	}
	const T& operator[](int ii)const { return items[ii]; }

};

int main() {
	//1创建Vector容器，容器中的元素用Stack<string>
	Vector<Stack<string>>vs;//C++11标准之前，后面的两个>>之间要加空格
	//类似于：
	//Stack<string> vs1[2];
	//string vs2[2][3];

	//2手动往容器中插入数据
	vs[0].push("hello"); vs[0].push("world"); vs[0].push("!!!");		//vs容器中的第0个栈
	vs[1].push("this"); vs[1].push("is"); vs[1].push("xyy");			//vs容器中的第1个栈
	vs[2].push("展"); vs[2].push("扩");									//vs容器中的第2个栈（自动扩展出来的，装载Stack，要去Stack中重载赋值函数，不然会出现浅拷贝错误）

	//3用嵌套的循环，把容器中的数据显示出来
	for (int ii = 0; ii < vs.size(); ii++) {//遍历Vector容器
		while (vs[ii].isempty() == false)//遍历元素Stack容器
		{
			string item;
			vs[ii].pop(item);
			cout << item << "\t";
		}
		cout << endl;
	}

	//-------------------------------------------------------------------------//
	cout << endl << endl;
	//1创建Stack容器，容器中的元素用Vector<string>
	Stack<Vector<string>>sv;

	//2插入数据
	Vector<string>tmp;//创建临时的Vector容器，把数据放入临时容器中，然后再入栈
	tmp[0] = "tmp00"; tmp[1] = "tmp01"; //第一个入栈的Vector(预设元素个数)
	sv.push(tmp);
	tmp[0] = "tmp10"; //第二个入栈的Vector（少填一个元素）
	sv.push(tmp);
	tmp[0] = "tmp30"; tmp[1] = "tmp31"; tmp[2] = "tmp31";//第三个入栈的Vector(扩展一个元素)
	sv.push(tmp);

	//3用嵌套循环，把容器中的数据显示出来
	while (sv.isempty()==false)
	{
		sv.pop(tmp);//出栈一个元素，放在临时容器中
		for (int ii = 0; ii < tmp.size(); ii++) {
			cout << tmp[ii] << "\t";
		}
		cout << "..." << endl;
	}


	//------------------------------------------------------------------------//
	cout << endl << endl;
	//1创建Vector容器，容器中的元素用Vector<string>类
	Vector<Vector<string>>vv;//递归使用模板类——自己模板类型嵌套自己模板类型
	//2插入数据
	vv[0][0] = "vv00"; vv[0][1] = "vv01";
	vv[1][0] = "vv10"; vv[1][1] = "vv11";
	vv[2][0] = "vv20"; vv[2][1] = "vv21";
	//3用嵌套循环，把vv容器中的数据显示出来
	for (int ii = 0; ii < vv.size(); ii++) {
		for (int jj = 0; jj < vv[ii].size(); jj++) {
			cout << vv[ii][jj] << "\t";
		}
		cout << endl;
	}

}

//在实际开发中，嵌套使用模板类是家常便饭