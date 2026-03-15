#include<Windows.h>

#define WNDCLASS_NAME	TEXT("Myd2dWndClass")
#define WINDOW_NAME		TEXT("XEdit")

#define CLIENT_WIDTH	800
#define CLIENT_HEIGHT	600

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
	return 0;
}

INT WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPTSTR lpCmdLine,int nCmdShow) {
	WNDCLASSEX wnd = { 0 };
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hInstance;
	wnd.lpszClassName = WNDCLASS_NAME;
	wnd.lpfnWndProc = WndProc;
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;

	RegisterClassExW(&wnd);


	RECT rect = { 0,0,CLIENT_WIDTH,CLIENT_HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, WNDCLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowhandle)return -1;

	ShowWindow(windowhandle, nCmdShow);
	UpdateWindow(windowhandle);

	//CreateWindow(WNDCLASS_NAME,L"edit",)
	CreateWindowEx(NULL, L"EDIT", L"", WS_CHILD | WS_VISIBLE, 10, 10, 100, 15, windowhandle, (HMENU)1001, hInstance, NULL);


	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else/////////////////////////////////////////////////////////////Ö÷³ÌÐòÑ­»·
		{
			
		
		}
	}

	return 0;
}

