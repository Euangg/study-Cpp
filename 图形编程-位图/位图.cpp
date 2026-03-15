#include"XWindow.h"

#define CLIENT_WIDTH	1280
#define CLIENT_HEIGHT	720

void 测试加载位图为DIB() {
	HBITMAP hBitmap = NULL;
	//hBitmap = (HBITMAP)LoadImageW(NULL, L"res/test1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//4x4
	//hBitmap = (HBITMAP)LoadImageW(NULL, L"res/test2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//4x8
	hBitmap = (HBITMAP)LoadImageW(NULL, L"res/test3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//5x6
	if (hBitmap == NULL) {
		MessageBoxW(NULL, L"加载失败", L"Tip", MB_OK);
		return;
	}

	BITMAP bitmap;
	GetObjectW(hBitmap, sizeof(BITMAP), &bitmap);

	//B  G  R
	//test1.bmp
	//ff ff ff   ff ff ff   ff ff ff   37 21 0b 
	//ff ff ff   ff ff ff   ff ff ff   ff ff ff 
	//ff ff ff   ff ff ff   ff ff ff   ff ff ff 
	//37 21 0b   ff ff ff   ff ff ff   ff ff ff

	//test3.bmp
	//ff ff ff   ff ff ff   ff ff ff   37 21 0b   4d e3 02   00 
	//ff ff ff   ff ff ff   ff ff ff   ff ff ff   4d e3 02   00 
	//ff ff ff   ff ff ff   ff ff ff   ff ff ff   4d e3 02   00 
	//37 21 0b   ff ff ff   ff ff ff   ff ff ff   4d e3 02   00 
	//4d e3 02   4d e3 02   4d e3 02   4d e3 02   37 21 0b   00
	//4d e3 02   4d e3 02   4d e3 02   4d e3 02   4d e3 02   00
	//数据中仍有内存对齐的补位数据
}

HDC wndDC = NULL;
HDC bufDC = NULL;
HDC lodDC = NULL;
namespace Test {
	HBITMAP hBitmap = NULL;
	HBITMAP hBitmap_create = NULL;

	void InitTest() {
		//加载DIB
		hBitmap = (HBITMAP)LoadImageW(NULL, L"res/test3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//5x6
		if (hBitmap == NULL) {
			MessageBoxW(NULL, L"加载失败", L"Tip", MB_OK);
			return;
		}
		BITMAP bitmap;
		GetObjectW(hBitmap, sizeof(BITMAP), &bitmap);
		*((char*)bitmap.bmBits + 0 )= 255;
		*((char*)bitmap.bmBits + 1 )= 0;
		*((char*)bitmap.bmBits + 2 )= 0;//将最左下一格改为(0,0,,255)

		//创建DIB
		BITMAPINFOHEADER bmih;
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = 4;
		bmih.biHeight = 4;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = 0;
		bmih.biXPelsPerMeter = 0;
		bmih.biYPelsPerMeter = 0;
		bmih.biClrUsed = 0;
		bmih.biClrImportant = 0;
		BYTE* pBits = nullptr;
		hBitmap_create = CreateDIBSection(NULL, (BITMAPINFO*)&bmih, 0, (void**)&pBits, NULL, 0);
		for (int i = 0; i < bmih.biWidth * bmih.biHeight * 3; i++) *(pBits + i) = 255;
	}
	void RenderTest() {
		//TextOut(wndDC, 5, 5, L"ASDASDSAD", 5);

		//SelectObject(lodDC, hBitmap);
		//StretchBlt(bufDC, 0, 0, 500, 600, lodDC, 0, 0, 5, 6, SRCCOPY);

		SelectObject(lodDC, hBitmap_create);
		StretchBlt(bufDC, 0, 0, 400, 400, lodDC, 0, 0, 4, 4, SRCCOPY);

		BitBlt(wndDC, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, bufDC, 0, 0, SRCCOPY);
	}
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	nXWindow::Init(hInstance, L"TestClass");
	nXWindow::GenerateWindow(L"Test", CLIENT_WIDTH, CLIENT_HEIGHT);

	wndDC = nXWindow::hdc_;
	bufDC = CreateCompatibleDC(wndDC);
	HBITMAP whiteBmp = CreateCompatibleBitmap(wndDC, CLIENT_WIDTH, CLIENT_HEIGHT);
	SelectObject(bufDC, whiteBmp);//此时g_hdc(缓冲区)的尺寸已经确定
	lodDC = CreateCompatibleDC(wndDC);//创建用于加载资源的dc

	nXWindow::fpInit_ = Test::InitTest;
	nXWindow::fpRender_ = Test::RenderTest;

	nXWindow::RunWindow();
	return 0;
}