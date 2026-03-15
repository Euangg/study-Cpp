#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

// 全局变量
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 使用GDI+加载PNG图像
        Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromFile(L"test.png");
        if (pBitmap)
        {
            // 获取图像的宽度和高度
            int width = pBitmap->GetWidth();
            int height = pBitmap->GetHeight();

            // 创建绘图对象
            Gdiplus::Graphics graphics(hdc);

            //graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
            //graphics.DrawImage(pBitmap, 0, 0, width*20, height*20);

           /* graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeDefault);
            graphics.DrawImage(pBitmap,150, 0, width * 20, height * 20);

            graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
            graphics.DrawImage(pBitmap, 300, 0, width * 20, height * 20);*/

            graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighSpeed);
            graphics.DrawImage(pBitmap, 450, 0, width * 20, height * 20);

            //graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeInvalid);
            //graphics.DrawImage(pBitmap, 600, 0, width * 20, height * 20);

           /* graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeNone);
            graphics.DrawImage(pBitmap, 750, 0, width * 20, height * 20);*/

            // 释放GDI+位图资源
            delete pBitmap;
        }

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        Gdiplus::GdiplusShutdown(gdiplusToken);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 初始化GDI+
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // 注册窗口类
    const wchar_t* className = L"MyWindowClass";
    WNDCLASS wndClass = {};
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = className;
    RegisterClass(&wndClass);

    // 创建窗口
    HWND hWnd = CreateWindow(className, L"Window Title", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    // 显示窗口
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}