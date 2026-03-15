//Linux着重进程开发（服务端）
//Windows着重线程开发（客户端）
//Windows线程是可以执行的代码实例。系统是以线程为单位调度程序
//一个程序中可以有多个线程，实现多任务处理

//线程挂起（休眠）
//DWORD SuspendThread(
//	HANDLE hThread								//要挂起的线程句柄
//)

//线程唤醒
//DWORD ResumeThread(
//	HANDLE hThread								//要唤醒的线程句柄
//)

//结束指定线程
//BOOL TerminateThread(
//	HANDLE hThread,								//要结束的线程句柄
//	DWORD dwExitCode							//退出码（没什么实际意义，随便填）
//)

//结束当前线程（结束调用该函数的线程）
//VOID ExitThread(
//	DWORD dwExitCode							//退出码（没什么实际意义，随便填）
//)

//获取当前线程的ID
//GetCurrentThreadId

//获取当前线程句柄
//GetCurrentThread()

//等候单个句柄有信号
//VOID WaitForSingleObject(
//	HANDLE handle,								//句柄的地址
//	DWORD dwMilliseconds						//最大等待时间（ms为单位），可填：INFINITE——一直等
//)
//可等候句柄：
//	线程句柄：线程执行过程中无信号，线程结束有信号（线程挂起不算结束）

//同时等候多个句柄有信号
//DWORD WaitForMultipleObjects(
//	DWORD nCount,								//句柄的数量
//	CONST HANDLE* lpHandle,						//句柄的BUFF地址(一般为句柄数组名)
//	BOOL bWaitAll,								//等候方式，TRUE-所有句柄都有信号，才结束等候；FALSE-只要有一个有信号，就结束等候
//  DWORD dwMilliseconds						//等待时间
//)




#include<Windows.h>
#include<stdio.h>
#include<iostream>
using namespace std;

DWORD CALLBACK TestProc(LPVOID pParam) {
	char* pchar_info = (char*)pParam;
	while (true) {
		printf("%s\n", pchar_info);
		Sleep(200);

		//内部强制终止
		//cout << "线程即将内部强制终止" << endl;
		//ExitThread(0);//到此为止，后面的内容不会再执行
		//cout << "线程已内部强制终止" << endl;//不会执行
	}
	return 0;
}

int main() {
	
	char pchar1[] = "********";
	HANDLE hThread1 = CreateThread(NULL, 0, TestProc, pchar1, 0, nullptr);


	Sleep(1000);
	cout << "Sleep(1000)结束" << endl;
	/*TerminateThread(hThread1, 0);
	cout << "外部强制终止线程1" << endl;*/
	/*SuspendThread(hThread1);
	cout << "外部挂起线程1" << endl; */
	WaitForSingleObject(hThread1, INFINITE);//等待线程1有信号（阻塞）//自然运行结束、外部强制终止、内部强制终止；挂起无效
	cout << "线程1信号" << endl;

	char pchar2[] = "-----------";
	HANDLE hThread2 = CreateThread(NULL, 0, TestProc, pchar2, CREATE_SUSPENDED, nullptr);

	getchar();
	//SuspendThread(hThread1);
	ResumeThread(hThread2);

	getchar();

	//线程执行过程中无信号，线程结束有信号

	return 0;
}