#include<Windows.h>
#include<iostream>
using namespace std;
LRESULT __stdcall MessageProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CLOSE://默认窗口过程收到后会自动调用DestroyWindow
		DestroyWindow(hwnd);
		cout << "WM_CLOSE" << endl;
		break;
	case WM_DESTROY://当DestroyWindow被调用后，窗口被销毁时发出。没有默认处理，必须自己在此PostQuitMessage
		PostQuitMessage(0);
		cout << "WM_DESTROY" << endl;
		break;
	case WM_QUIT://这不是一个窗口消息，永远不会被执行
		cout << "WM_QUIT" << endl;
		break;
	}
	return DefWindowProcW(hwnd, msg, wp, lp);
}

int main() {
	WNDCLASSW wndCls{};
	wndCls.lpszClassName = L"XClass";//窗口类名
	wndCls.lpfnWndProc = MessageProc;//回调过程

	if (!RegisterClassW(&wndCls)) MessageBox(NULL, L"register window class failed", L"err", MB_OK);

	RECT rect = { 0,0,1600,900 };//准备生成窗口尺寸，预设定绘图区尺寸（单位像素）
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);//根据绘图区尺寸生成窗口尺寸

	HWND hwnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, L"XClass", L"窗口程序", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, NULL, 0);

	if (!hwnd) {
		MessageBox(NULL, L"create window failed", L"err", MB_OK);
		return 0;
	};

	ShowWindow(hwnd, SW_SHOW);//显示窗口
	UpdateWindow(hwnd);//刷新窗口
	SetFocus(hwnd);//聚焦窗口

	MSG msg = { 0 };//准备接收消息
	msg.message = WM_NULL;//清空消息内容
	while (1) {
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {//从消息队列中获取消息（非阻塞式）
			TranslateMessage(&msg);//转换消息
			DispatchMessage(&msg);//分发消息到窗口过程（把消息传递给Windows，由Windows调用窗口过程，窗口过程处理消息）
			if (msg.message == WM_QUIT)break;
		}
		else {/////////////////////////////////////////////////////////////主程序循环

		}
	}

	return 0;
}