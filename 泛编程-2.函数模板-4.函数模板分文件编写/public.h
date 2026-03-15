#pragma once
#include<iostream>
using namespace std;

void Swap(int a, int b);//普通函数声明

//函数模板声明&定义（必须都在头文件中）
template<typename T>
void Swap(T a, T b) {
	cout << "调用通用类型函数模板" << endl;
}

//函数模板的具体化声明
template<>
void Swap(int a, int b);


//模板不能分文件，但模板特例化可以分文件