//API创建线程
//HANDLE CreateThread(//创建在调用进程的虚拟地址空间内执行的线程。若要创建在另一个进程的虚拟地址空间中运行的线程，使用 CreateRemoteThread 函数。
//	LPSECURITY_ATTRIBUTES lpThreadAttributes,	//安全属性（Windows操作系统已不用这个参数，填NULL即可）
//	SIZE_T dwStackSize,							//线程堆栈的初始大小（以字节为单位），如果此参数为零，则新线程使用可执行文件的默认大小。 
//	LPTHREAD_START_ROUTINE lpStartAddress,		//线程任务的函数地址
//	LPVOID lpParameter,							//传递给线程任务函数的参数
//	DWORD dwCreationFlags,						//线程的创建方式（立即执行方式or挂起方式）0创建后，线程会立即运行。
//	LPDWORD lpThreadId							//创建成功返回的线程ID
//)//创建

//类型LPTHREAD_START_ROUTINE：
//typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);
//一个函数指针，要求一个LPVOID参数，返回值为DWORD，调用约定为WINAPI（要求参数固定）

//线程处理函数（程序员自定义）
//DWORD WINAPI 函数名(LPVOID lpParameter)		//创建线程时，传递给线程的参数

#include<iostream>
using namespace std;
#include<Windows.h>

DWORD CALLBACK ThreadTask(LPVOID para) {
	for (int i = 0; i < 100; i++)cout << i << endl;
	cout << "任务完成" << endl;
	return 0;
}
int main() {
	CreateThread(NULL, 0, ThreadTask, nullptr, 0, nullptr);
//	参数：1.废弃，填NULL即可
//		2.线程栈大小，小于1024会被默认置为1024
//		3.线程处理函数(自己定义)
//		4.传递给线程处理函数的参数
//		5.线程的创建方式，可填：0——立即执行、CREATE_SUSPENDED(4)——挂起
//		6.接收线程ID的变量
//	返回：线程句柄

	Sleep(30);//主线程一结束副线程就会被干掉，哪怕只执行了一半
}

