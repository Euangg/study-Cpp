#include<iostream>
using namespace std;

template<typename T>
void show(T name) {
	cout << "亲爱的" << name << "，你好！" << endl;
}

void print() {
	cout << "递归终止" << endl;
}

template<typename T,typename ...Args>
void print(T arg, Args... args) {
	cout << "参数:" << arg << endl;
	//cout << "还有" << sizeof...(args) << "个参数未展开" << endl;
	show(arg);
	print(args...);
}

template<typename...Args>
void func(const string& str, Args...args) {
	cout << str << endl;
	print(args...);
	cout << "完成" << endl;
}

int main() {
	//print("asdasd", 23, "hello");
	func("omg！", "ak67", "ask", "jaskod");
}


//复习统一初始化列表