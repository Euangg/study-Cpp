#include<Windows.h>


LRESULT __stdcall MessageProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_QUIT:
	case WM_CLOSE:
	case WM_DESTROY:
		//SteamAPI_Shutdown();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, msg, wp, lp);
}

int __stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {
	WNDCLASSEX wnd;//准备WNDCLASSEX
	ZeroMemory(&wnd, sizeof(WNDCLASSEX));//清空WNDCLASS内存空间，准备填写
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hInstance;
	wnd.lpszClassName = L"XClass";//窗口类名
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.lpfnWndProc = MessageProc;//回调过程

	if (!RegisterClassExW(&wnd)) {
		MessageBox(NULL, L"register window class failed", L"err", MB_OK);
	}

	RECT rect = { 0,0,1600,900 };//准备生成窗口尺寸，预设定绘图区尺寸（单位像素）
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);//根据绘图区尺寸生成窗口尺寸

	HWND hwnd_ = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"XClass", L"窗口程序", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!hwnd_) {
		MessageBox(NULL, L"create window failed", L"err", MB_OK);
		return 0;
	};

	ShowWindow(hwnd_, SW_SHOW);//显示窗口
	UpdateWindow(hwnd_);//刷新窗口
	SetFocus(hwnd_);//聚焦窗口

	MSG msg = { 0 };//准备接收消息
	msg.message = WM_NULL;//清空消息内容
	while (msg.message != WM_QUIT) {
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {//从消息队列中获取消息（非阻塞式）
			TranslateMessage(&msg);//转换消息
			DispatchMessage(&msg);//分发消息到窗口过程（把消息传递给Windows，由Windows调用窗口过程，窗口过程处理消息）
		}
		else {/////////////////////////////////////////////////////////////主程序循环

		}
	}

	return 0;
}