#include<Windows.h>

int main() {
	WNDCLASSW wndCls{ {}, [](HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)->LRESULT {return DefWindowProc(hwnd, msg, wp, lp); } };
	wndCls.lpszClassName = L"MyWindow";
	RegisterClassW(&wndCls);

	HWND hwnd = CreateWindowExW(0, L"MyWindow", L"", WS_OVERLAPPEDWINDOW, 0, 0, 1000 + 16, 600 + 39, 0, 0, 0, 0);
	ShowWindow(hwnd, SW_SHOW);

	while (true){
		MSG msg{};
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
	}
}