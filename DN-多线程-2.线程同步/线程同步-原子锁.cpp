//临界资源：变量、内存、文件、窗口
//多个线程操作同一资源，这个资源被称作临界资源，需要加锁


//同步技术（加锁机制）
//1）原子锁
//2）互斥
//3）

//4）


//原子锁
//	针对问题：多个线程对同一个数据进行原子操作（运算符操作），会产生结果丢失
//	实现：原子锁函数（API）
//		API原理：直接对数据所在的内存操作，并且在任何一个瞬间，只能有一个线程访问该内存
//				锁的是变量所在的内存
//	局限性：1.需要记大量API（每种运算符对应一种API）
//			2.只能针对运算操作
#include<Windows.h>
#include<iostream>
using namespace std;

long g_value = 0;

DWORD CALLBACK TestProc1(LPVOID pparam) {
	for (int i = 0; i < 100000; i++) {
		//g_value++;
		InterlockedIncrement(&g_value);//++运算原子锁函数
		//操作时会先锁住变量所在内存，如果锁不住就会阻塞，等其他线程操作完解锁后再由其锁住内存并进行操作
	}

	return 0;
}

DWORD CALLBACK TestProc2(LPVOID pparam) {
	for (int i = 0; i < 100000; i++) {
		//g_value++;
		InterlockedIncrement(&g_value);//++运算原子锁函数
	}
	return 0;
}

int main() {
	DWORD nID = 0;
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, TestProc1, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, TestProc2, NULL, 0, &nID);

	//保证子线程执行完
	WaitForMultipleObjects(2, hThread, true, INFINITE);
	cout << "wait over" << endl;
	cout << "g_value=" << g_value << endl;//不加锁的情况下，结果不是200000
	//计算机++运算过程：（汇编）
	//mov         eax, dword ptr[g_value(071C138h)]		//取g_value的地址(071C138h)，读取地址内存，读dword大小，值存入eax寄存器
	//add         eax, 1								//eax寄存器的数据+1
	//mov         dword ptr[g_value(071C138h)], eax		//eax寄存器的数据存到g_value的地址(071C138h)
	//1.将变量的值拷贝到寄存器
	//2.将寄存器的值+1
	//3.寄存器的值传递给变量

	//原子锁InterlockedIncrement运算：（汇编）
	//lock inc    dword ptr[g_value(0BEC138h)]

	//如果CPU时间片到现场不保护，变量的值在别的线程被修改，回到此线程，寄存器+1的值赋给变量，导致其他线程对变量完成的操作无效

	return 0;
}


