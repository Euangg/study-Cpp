//预编译头文件实际上是让你抓取一堆头文件，并将它们转化成编译器可以使用的格式
//在visual studio中一般叫stdafx.h或pch.h

#include"pch.h"

int main() {
	std::cout << "Hello World" << std::endl;
	std::cout << "Hello World" << std::endl;
	std::cout << "Hello World" << std::endl;
}


//visual studio显示生成时间：
//菜单栏：工具->选项->项目和解决方案->VC++项目设置->生成计时