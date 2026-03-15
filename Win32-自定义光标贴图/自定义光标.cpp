#include<Windows.h>

//HCURSOR cursor = LoadCursorFromFileW(L"ccc.cur");
HCURSOR cursor = LoadCursorFromFileW(L"555.cur");

LRESULT __stdcall MessageProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_QUIT:
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SETCURSOR:
		SetCursor(cursor);//不顶用
		break;
	}
	return DefWindowProcW(hwnd, msg, wp, lp);
}

int main() {
	WNDCLASSEX wnd;
	ZeroMemory(&wnd, sizeof(WNDCLASSEX));
	wnd.cbSize = sizeof(WNDCLASSEX);
	//wnd.hCursor = LoadCursor(NULL, IDC_ARROW);//加载默认光标
	wnd.hCursor = cursor;//最好还是在填写窗口类时设置
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = NULL;
	wnd.lpszClassName = L"XClass";
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.lpfnWndProc = MessageProc;

	if (!RegisterClassExW(&wnd)) MessageBox(NULL, L"register window class failed", L"err", MB_OK);

	RECT rect = { 0,0,1600,900 };//准备生成窗口尺寸，预设定绘图区尺寸（单位像素）
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);//根据绘图区尺寸生成窗口尺寸

	HWND hwnd_ = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"XClass", L"窗口程序", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, NULL, 0);

	if (!hwnd_) {
		MessageBox(NULL, L"create window failed", L"err", MB_OK);
		return 0;
	};


	ShowWindow(hwnd_, SW_SHOW);
	UpdateWindow(hwnd_);
	SetFocus(hwnd_);

	MSG msg = { 0 };
	msg.message = WM_NULL;
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