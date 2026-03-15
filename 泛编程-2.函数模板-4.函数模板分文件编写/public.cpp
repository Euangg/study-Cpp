#include"public.h"

//普通函数定义
void Swap(int a, int b) {
	cout << "调用普通函数" << endl;
}

//函数模板具体化定义
template<>
void Swap(int a, int b) {
	cout << "调用具体化函数模板" << endl;
}
