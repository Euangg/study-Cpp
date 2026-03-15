//特性操作
//int max_size() const;//返回string对象的最大长度string::npos，此函数意义不大
//int capacity() const;//返回当前容量（可以存放的字符总数）
//int length() const;//返回容器中数据的大小（字符串语义，字符串长短）
//int size() const;//返回容器中数据的大小（容器语义，数据大小（byte））实际效果同上一个函数
//bool empty() const;//判断容器是否为空
//void clear();//清空容器
//void reserve(size_t size=0);//将容器的容量设置为至少size
//void resize(int len,char c=0);//把容器的实际大小置为len，如果len<实际大小，会截断多出的部分；如果len>实际大小，就用c填充

//字符操作
//int copy(char* s,int n,int pos=0)const;//从pos开始的n个字节拷贝到s中，返回实际拷贝的数目。

//交换操作
//void swap(string& str);//与str交换内容；如果数据量很小，交换的是动态数组中的内容，如果数据量较大，交换的是动态数组的地址

//查找操作

//替换操作

//插入操作

//删除操作

#include<iostream>
using namespace std;

int main() {
	string s1 = "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
	string s2 = "222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222";

	cout << "s1中的内容：" << s1 << endl;
	cout << "s1动态数组的地址：" << (void*)s1.data() << endl;
	cout << "s2中的内容：" << s2 << endl;
	cout << "s2动态数组的地址：" << (void*)s2.data() << endl;

	cout << endl;
	s1.swap(s2);
	cout << "s1中的内容：" << s1 << endl;
	cout << "s1动态数组的地址：" << (void*)s1.data() << endl;
	cout << "s2中的内容：" << s2 << endl;
	cout << "s2动态数组的地址：" << (void*)s2.data() << endl;

}