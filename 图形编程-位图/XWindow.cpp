#include "XWindow.h"

HINSTANCE nXWindow::hins_ = NULL;
PWSTR nXWindow::className_ = L"NULL";
UINT16 nXWindow::wPixs_ = 0;
UINT16 nXWindow::hPixs_ = 0;
HWND nXWindow::hwnd_ = NULL;
HDC nXWindow::hdc_ = NULL;
fpLoop nXWindow::fpInit_ = nXWindow::emptyLoop;
fpLoop nXWindow::fpLoop_ = nXWindow::emptyLoop;
fpLoop nXWindow::fpRender_ = nXWindow::emptyLoop;

void nXWindow::Init(HINSTANCE hins, PWSTR classname) {
	if (!hins)return;
	hins_ = hins;//绑定进程实例句柄

	WNDCLASSEX wnd;//准备WNDCLASSEX
	ZeroMemory(&wnd, sizeof(WNDCLASSEX));//清空WNDCLASS内存空间，准备填写
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hins;
	wnd.lpszClassName = classname;//窗口类名
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.lpfnWndProc = MessageProc;//回调过程

	if (!RegisterClassExW(&wnd)) {
		MessageBox(NULL, L"register window class failed", L"err", MB_OK);
	}
	className_ = classname;
}
void nXWindow::GenerateWindow(LPCWSTR wndname, UINT16 wpixs, UINT16 hpixs) {
	RECT rect = { 0,0,wpixs,hpixs };//准备生成窗口尺寸，预设定绘图区尺寸（单位像素）
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);//根据绘图区尺寸生成窗口尺寸

	hwnd_ = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, className_, wndname, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hins_, 0);

	if (!hwnd_) {
		MessageBox(NULL, L"create window failed", L"err", MB_OK);
	};

	wPixs_ = wpixs;
	hPixs_ = hpixs;
	hdc_ = ::GetDC(hwnd_);

	ShowWindow(hwnd_, SW_SHOW);//显示窗口
	UpdateWindow(hwnd_);//刷新窗口
}

LRESULT CALLBACK nXWindow::MessageProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	//if (s_fpMsgProc)s_fpMsgProc(msg, wp, lp);
	return DefWindowProc(hwnd, msg, wp, lp);
}

void nXWindow::RunWindow() {
	fpInit_();

	MSG msg = { 0 };//准备接收消息
	msg.message = WM_NULL;//清空消息内容
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {//从消息队列中获取消息（非阻塞式）
			TranslateMessage(&msg);//转换消息
			DispatchMessage(&msg);//分发消息到窗口过程（把消息传递给Windows，由Windows调用窗口过程，窗口过程处理消息）
		}
		else {/////////////////////////////////////////////////////////////主程序循环
			//=========update逻辑刷新=========
			fpLoop_();
			////=========Render图像渲染=========
			fpRender_();
		}
	}
}


void nXWindow::emptyLoop() {};