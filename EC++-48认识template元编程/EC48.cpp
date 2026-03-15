//所谓的Template meta programming（TMP，模板元编程）是以C++写成、
//执行于C++编译器内的程序。一旦TMP程序结束运行，其输出，
//也就是从templates具现出来的若干C++源码，便会一如往常地被编译

template<typename IterT,typename DistT>
void advance(IterT& iter, DistT& d) {
	if (iter is a random access iterator) {
		iter += d;//针对random access迭代器使用迭代器算术运算
	}
	else {
		if (d >= 0) { while (d--)++iter; }//针对其他迭代器类型反复调用++或--
		else { while (d++)--iter; }
	}
}

#include<iterator>
template<typename IterT, typename DistT>
void advance2(IterT& iter, DistT& d) {
	if (typeid(typename std::iterator_traits<IterT>::iterator_category)==
		typeid(std::random_access_iterator_tag)) {
		iter += d;//针对random access迭代器使用迭代器算术运算
	}
	else {
		if (d >= 0) { while (d--)++iter; }//针对其他迭代器类型反复调用++或--
		else { while (d++)--iter; }
	}
}


//TMP起手程序：在编译期计算阶乘
//递归模板具现化实现循环
#include<iostream>
template<unsigned n>
struct Factorial{
	enum{value=n*Factorial<n-1>::value};
};
template<>
struct Factorial<0>{	//特殊情况：Factorial<0>的值是1
	enum { value = 1 };
};
int main() {
	std::cout << Factorial<5>::value << std::endl;
	std::cout << Factorial<10>::value << std::endl;
	std::cout << Factorial<14>::value << std::endl;
}