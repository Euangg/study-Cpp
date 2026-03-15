//异步选择模型，应用程序可在一个套接字上，接收以Windows消息为基础的网络事件通知，使网络事件发生变成系统消息
//使用该模型，在程序中必须调用CreateWindow创建窗口，再为窗口提供一个窗口例程函数(事件处理函数、回调函数)
//int WSAAsuncSelect(
//	[in]	SOCKET s,			//套接字
//	[in]	HWND hWnd,			//网络事件发生后，需要收到通知消息的那个窗口
//	[in]	unsigned int wMsg,	//发生网络事件时，想要接收的消息
//	[in]	long lEvent			//位掩码，对应网络事件组合
//)

//网络事件：
//wParam：发生网络事件的套接字（当窗口例程同时分配多个套接字，作用显现）
//lParam：低字指示已发生的网络事件，高字包含出现的错误代码

#include<string>
using namespace std;

#include<Windows.h>

int main() {

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = NULL;
	wc.hInstance=

	DWORD dwStyle;
	DWORD dwExStyle = 0;


	HWND myWindow = CreateWindowExW(dwExStyle, NULL, L"XWindow", NULL, 0, 0, 800, 800, NULL, NULL, NULL, NULL);
	//参数:
	//[in]			DWORD		dwExStyle,		窗口样式
	//[in,optional]	LPCWSTR		lpClassName,	窗口类名（系统类，或自己调用RegisterClass注册的类）
	//[in,optional] LPCWSTR		lpWindowName,	窗口名（自定义）
	//[in]           DWORD		dwStyle,		创建的窗口样式，位掩码
	//[in]           int		X,				
	//[in]           int		Y,
	//[in]           int		nWidth,
	//[in]           int		nHeight,
	//[in, optional] HWND		hWndParent,		
	//[in, optional] HMENU		hMenu,
	//[in, optional] HINSTANCE	hInstance,		要与窗口关联的实例模块句柄
	//[in, optional] LPVOID		lpParam
	if (myWindow == NULL) {
		wstring str = L"窗口句柄创建失败-" + to_wstring(GetLastError());
		MessageBox(myWindow, str.c_str(), L"tip", MB_OK);
		//87-参数错误
	}
	ShowWindow(myWindow, 0);

}
