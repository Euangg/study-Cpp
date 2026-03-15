





// 操作像素数据
BYTE* pPixels = reinterpret_cast<BYTE*>(mappedRect.bits);
UINT32 stride = mappedRect.pitch;

for (UINT32 y = 0; y < size.height; y++)
{
    for (UINT32 x = 0; x < size.width; x++)
    {
        // 访问像素数据
        BYTE* pPixel = pPixels + y * stride + x * sizeof(UINT32);

        // 读取或写入像素值
        BYTE blue = pPixel[0];
        BYTE green = pPixel[1];
        BYTE red = pPixel[2];
        BYTE alpha = pPixel[3];

        // 对像素值进行处理
        // ...

        // 示例：将像素值设为红色
        pPixel[0] = 255;   // 蓝色通道
        pPixel[1] = 0;     // 绿色通道
        pPixel[2] = 0;     // 红色通道
        pPixel[3] = 255;   // Alpha通道
    }
}

// 结束对像素数据的操作
pTempBitmap->Unmap();

// 释放对象
pTempBitmap->Release();
pBitmap->Release();
pFormatConverter->Release();
pFrame->Release();
pDecoder->Release();
pWICFactory->Release();
pRenderTarget->Release();
pD2DFactory->Release();




#include"XWindow.h"
#include<d2d1.h>
#include<wincodec.h>

#define CLIENT_WIDTH	1280
#define CLIENT_HEIGHT	720

HWND hwnd = NULL;
HDC wndDC = NULL;
HDC bufDC = NULL;
HDC lodDC = NULL;
namespace Test {
	HBITMAP hBitmap = NULL;
	HBITMAP hBitmap_create = NULL;

	void InitTest() {


		// 创建Direct2D设备和渲染目标
		ID2D1Factory* pD2DFactory = nullptr;
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

		ID2D1HwndRenderTarget* pRenderTarget = nullptr;
		D2D1_SIZE_U size = { CLIENT_WIDTH,CLIENT_HEIGHT };
		pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd,size), &pRenderTarget);

		// 加载图像文件并创建ID2D1Bitmap对象
		//创建WIC工厂
		IWICImagingFactory* pWICFactory = nullptr;
		CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
		//创建解码器
		IWICBitmapDecoder* pDecoder = nullptr;
		pWICFactory->CreateDecoderFromFilename(L"test.bmp", nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
		//获取图像帧
		IWICBitmapFrameDecode* pFrame = nullptr;
		pDecoder->GetFrame(0, &pFrame);

		IWICFormatConverter* pFormatConverter = nullptr;
		pWICFactory->CreateFormatConverter(&pFormatConverter);

		pFormatConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);



		ID2D1Bitmap* pBitmap = nullptr;
		pRenderTarget->CreateBitmapFromWicBitmap(pFormatConverter, nullptr, &pBitmap);
		pBitmap->Se



		// 获取像素格式和大小信息
		D2D1_PIXEL_FORMAT pixelFormat = pBitmap->GetPixelFormat();
		D2D1_SIZE_U size = pBitmap->GetPixelSize();

		// 创建临时的ID2D1Bitmap对象，并将原始的ID2D1Bitmap对象复制到临时对象中
		ID2D1Bitmap* pTempBitmap = nullptr;
		pRenderTarget->CreateBitmap(size, nullptr, 0, D2D1::BitmapProperties(pixelFormat), &pTempBitmap);
		pTempBitmap->CopyFromBitmap(nullptr, pBitmap, nullptr);

		// 获取对像素数据的指针
		D2D1_MAPPED_RECT mappedRect;
		pTempBitmap->Map(D2D1_MAP_OPTIONS_READ, &mappedRect);

		DXGI_MAPPED_RECT mappedRect;
		



		
	}
	void RenderTest() {
		
	}
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	nXWindow::Init(hInstance, L"TestClass");
	nXWindow::GenerateWindow(L"Test", CLIENT_WIDTH, CLIENT_HEIGHT);

	hwnd = nXWindow::hwnd_;
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