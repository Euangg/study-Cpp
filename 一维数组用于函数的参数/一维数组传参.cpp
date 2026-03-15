#include<iostream>
using namespace std;

//传一维数组标准写法
void func(char* arr, int len) {};
//void func(char arr[], int len) {};//与上面的一起算重定义


void func2(int* arr) {};
//void func2(int arr[5]) {};//与上面的一起重定义

void func3(int arr[]) {
	//for (auto& e : arr) {}//报错arr没有begin()函数，实际上还是当指针
};

//关于这两种不同写法 int* arr和int arr[]  在函数头中  是算一种表达的意义：
//数组写法（int arr[]）可以作为一种约定 提醒程序员，arr不仅指向int，还指向数组，还指向数组的第一个元素，还可以填数组的大小

//在其他上下文中，二者意义可能不同，例如，在代码段中不能使用int a[]来声明指针


void func3(int arr[6]) {
	cout << sizeof(arr) << endl;//只会算指针大小
};

int main() {
	int arr[] = { 1,2,34,5,6,7 };
	cout << sizeof(arr) << endl;//24
	func3(arr);					//4
}
