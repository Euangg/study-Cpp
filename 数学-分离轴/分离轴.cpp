#include<Windows.h>
#include<string>
#include<d2d1.h>
#pragma comment(lib,"d2d1.lib")
#include<dwrite.h>
#pragma comment(lib,"dwrite.lib")
#include<wincodec.h>
#pragma comment(lib,"windowscodecs.lib")
#define _USE_MATH_DEFINES
#include<math.h>

using std::wstring;
using RECTF = D2D1_RECT_F;
using COLORF = D2D1_COLOR_F;

struct sRoRect {
	RECT rt_{0,0,0,0};
	double ang_{0};

	float CX() { return (rt_.left + rt_.right) / 2.; }
	float CY() { return (rt_.top + rt_.bottom) / 2.; }
	void ADDCX(int d) { rt_.left += d; rt_.right += d; }
	void ADDCY(int d) { rt_.top += d; rt_.bottom += d; }
	int W() { return rt_.right - rt_.left; }
	int H() { return rt_.bottom - rt_.top; }

	
	POINTF LT() { POINT o{ -W() / 2.,-H()/2. }; double radian = ang_ * M_PI / 180;
	//return{ float(o.x * cos(radian) - o.y * sin(radian) + CX()),float(o.x * sin(radian) + o.y * cos(radian) + CY()) };//传统坐标系、逆
	//return{ float(o.x * cos(radian) + o.y * sin(radian) + CX()),float(-o.x * sin(radian) + o.y * cos(radian) + CY()) };//屏幕坐标系、逆
	return{ float(o.x * cos(radian) - o.y * sin(radian) + CX()),float(o.x * sin(radian) + o.y * cos(radian) + CY()) };//屏幕坐标系、顺
	};
	POINTF RT() { POINT o{ W() / 2.,-H() / 2. }; double radian = ang_ * M_PI / 180;
	return{ float(o.x * cos(radian) - o.y * sin(radian) + CX()),float(o.x * sin(radian) + o.y * cos(radian) + CY()) };
	}
	POINTF LB() { POINT o{ -W() / 2.,H() / 2. }; double radian = ang_ * M_PI / 180;
	return{ float(o.x * cos(radian) - o.y * sin(radian) + CX()),float(o.x * sin(radian) + o.y * cos(radian) + CY()) };
	}
	POINTF RB() {POINT o{ W() / 2.,H() / 2. };  double radian = ang_ * M_PI / 180;
	return{ float(o.x * cos(radian) - o.y * sin(radian) + CX()),float(o.x * sin(radian) + o.y * cos(radian) + CY()) };
	}
};							 

void Update();
void Render();

HWND hwnd_;
HDC dc_;
POINT mousePos_;

ID2D1Factory* _D2DFactory_ = nullptr;//D2D工厂
IDWriteFactory* _DWriteFactory_ = nullptr;//文字工厂
ID2D1HwndRenderTarget* _hwndRenderTarget_ = nullptr;//渲染目标（指定窗口DC和区域）

ID2D1SolidColorBrush* _scBrush_ = nullptr;//颜色画刷
ID2D1BitmapBrush* _bitmapBrush_bitmapRenderTarget_ = nullptr;

ID2D1StrokeStyle* _strokeStyle_ = nullptr;

ID2D1Bitmap* _bitmap_ = nullptr;

D2D1_COLOR_F cCrimson = D2D1::ColorF(D2D1::ColorF::Crimson);
D2D1_COLOR_F cBlack = D2D1::ColorF(D2D1::ColorF::Black);
D2D1_COLOR_F cWhite = D2D1::ColorF(D2D1::ColorF::White);
D2D1_COLOR_F cRed = D2D1::ColorF(D2D1::ColorF::Red);
D2D1_COLOR_F cOrange = D2D1::ColorF(D2D1::ColorF::Orange);
D2D1_COLOR_F cYellow = D2D1::ColorF(D2D1::ColorF::Yellow);
D2D1_COLOR_F cGreen = D2D1::ColorF(D2D1::ColorF::Green);
D2D1_COLOR_F cCyan = D2D1::ColorF(D2D1::ColorF::Cyan);
D2D1_COLOR_F cBlue = D2D1::ColorF(D2D1::ColorF::Blue);
D2D1_COLOR_F cPurple = D2D1::ColorF(D2D1::ColorF::Purple);
D2D1_COLOR_F cChartreuse = D2D1::ColorF(D2D1::ColorF::Chartreuse);


void Init() {
	//初始化D2D工厂
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_D2DFactory_);
	if (res != S_OK) {
		MessageBox(NULL, L"D2D1CreateFactory失败！", L"Err", 0);
		return;
	}
	//初始化文字工厂
	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&_DWriteFactory_));
	if (res != S_OK) {
		MessageBox(NULL, L"DWriteCreateFactory失败！", L"Err", 0);
		return;
	}

	//初始化渲染目标
	res = _D2DFactory_->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd_, D2D1::SizeU(1600, 900)),//不管给多大都会画满
		&_hwndRenderTarget_);
	if (res != S_OK) {
		MessageBox(NULL, L"CreateHwndRenderTarget失败！", L"Err", 0);
		return;
	}

	//初始化画刷
	res = _hwndRenderTarget_->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 1), &_scBrush_);
	if (res != S_OK) {
		MessageBox(NULL, L"CreateSolidColorBrush失败！", L"Err", 0);
		return;
	}

	D2D1_STROKE_STYLE_PROPERTIES strokeStylePro = D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE::D2D1_CAP_STYLE_ROUND,
		D2D1_CAP_STYLE::D2D1_CAP_STYLE_ROUND,
		D2D1_CAP_STYLE::D2D1_CAP_STYLE_ROUND,
		D2D1_LINE_JOIN::D2D1_LINE_JOIN_BEVEL,
		10.0f,
		D2D1_DASH_STYLE::D2D1_DASH_STYLE_CUSTOM,
		0.0f
	);
	float dashes[] = { 100.0f, 200.0f, 50.0f, 3.0f, 2.0f, 2.0f };
	_D2DFactory_->CreateStrokeStyle(strokeStylePro, dashes, 6, &_strokeStyle_);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//创建窗口部分
	{
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
		wnd.lpfnWndProc = [](HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)->LRESULT __stdcall{
			switch (msg) {
			case WM_MOUSEMOVE: {
				//RECT windRect{ 0 };
				POINTS mouse= MAKEPOINTS(lp);
				mousePos_.x = mouse.x;
				mousePos_.y = mouse.y;
				break;
			}
			case WM_QUIT:
			case WM_CLOSE:
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			}
			return DefWindowProcW(hwnd, msg, wp, lp);
		};//回调过程

		if (!RegisterClassExW(&wnd)) {
			MessageBox(NULL, L"register window class failed", L"err", MB_OK);
		}

		RECT rect = { 0,0,1600,900 };//准备生成窗口尺寸，预设定绘图区尺寸（单位像素）
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);//根据绘图区尺寸生成窗口尺寸

		hwnd_ = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"XClass", L"窗口程序", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
		dc_ = GetDC(hwnd_);

		if (!hwnd_) {
			MessageBox(NULL, L"create window failed", L"err", MB_OK);
			return 0;
		};

		ShowWindow(hwnd_, SW_SHOW);//显示窗口
		UpdateWindow(hwnd_);//刷新窗口
		SetFocus(hwnd_);//聚焦窗口
	};
	Init();
	MSG msg = { 0 };//准备接收消息
	msg.message = WM_NULL;//清空消息内容
	while (msg.message != WM_QUIT) {
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {//从消息队列中获取消息（非阻塞式）
			TranslateMessage(&msg);//转换消息
			DispatchMessage(&msg);//分发消息到窗口过程（把消息传递给Windows，由Windows调用窗口过程，窗口过程处理消息）
		}
		else {/////////////////////////////////////////////////////////////主程序循环
			Update();
			Render();
		}
	}
	return 0;
}
void ShowText(ID2D1RenderTarget* prt, const wstring& str, RECTF& rect, const COLORF& color, double size, 
	DWRITE_TEXT_ALIGNMENT talignment= DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT palignment= DWRITE_PARAGRAPH_ALIGNMENT_NEAR) {
	IDWriteTextFormat* _textFormat_;
	_DWriteFactory_->CreateTextFormat(L"Cambria", NULL, DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		size, L"", &_textFormat_);
	_textFormat_->SetTextAlignment(talignment);//设置文字对齐
	_textFormat_->SetParagraphAlignment(palignment);//设置段落对齐
	_textFormat_->SetWordWrapping(DWRITE_WORD_WRAPPING::DWRITE_WORD_WRAPPING_NO_WRAP);//设置为单行文字
	_scBrush_->SetColor(color);
	prt->DrawTextW(str.c_str(), str.length(), _textFormat_, rect, _scBrush_);
	_textFormat_->Release();
}

sRoRect roRt1{ {10,10,100,50},{0} };
sRoRect roRt2{ {10,10,120,70},{0} };
bool hitted;
void Update() {
	if (GetAsyncKeyState('Q'))roRt1.ang_ -= 0.5;
	if (GetAsyncKeyState('E'))roRt1.ang_ += 0.5;
	if (GetAsyncKeyState('W'))roRt1.ADDCY(-1);
	if (GetAsyncKeyState('S'))roRt1.ADDCY(1);
	if (GetAsyncKeyState('A'))roRt1.ADDCX(-1);
	if (GetAsyncKeyState('D'))roRt1.ADDCX(1);

	if (GetAsyncKeyState('U'))roRt2.ang_ -= 0.5;
	if (GetAsyncKeyState('O'))roRt2.ang_ += 0.5;
	if (GetAsyncKeyState('I'))roRt2.ADDCY(-1);
	if (GetAsyncKeyState('K'))roRt2.ADDCY(1);
	if (GetAsyncKeyState('J'))roRt2.ADDCX(-1);
	if (GetAsyncKeyState('L'))roRt2.ADDCX(1);
};


void Render() {
	_hwndRenderTarget_->BeginDraw();
	_hwndRenderTarget_->Clear(cBlack);

	D2D1_POINT_2F base{ 800,300 };
	{
		hitted = true;
		POINTF p11 = roRt1.LT();
		POINTF p12 = roRt1.RT();
		POINTF p13 = roRt1.RB();
		POINTF p14 = roRt1.LB();

		POINTF p21 = roRt2.LT();
		POINTF p22 = roRt2.RT();
		POINTF p23 = roRt2.RB();
		POINTF p24 = roRt2.LB();

		POINTF n[4] = {
			{ p12.x - p11.x,p12.y - p11.y },
			{ p13.x - p12.x,p13.y - p12.y },
			{ p22.x - p21.x,p22.y - p21.y },
			{ p23.x - p22.x,p23.y - p22.y },
		};

		COLORF cVn[4] = { cRed,cOrange,cYellow,cGreen };
		for (int o = 0; o < 4; o++) {
			POINTF& vn = n[o];

			_scBrush_->SetColor(cVn[o]);
			_hwndRenderTarget_->DrawLine({ 0,0 }, { vn.x,vn.y }, _scBrush_);

			double sn = sqrt(vn.x * vn.x + vn.y * vn.y);
			D2D1_ELLIPSE e = D2D1::Ellipse({ 0,0 }, sn, sn);
			_hwndRenderTarget_->DrawEllipse(e, _scBrush_);

			double shadow1[4] = {
				(p11.x * vn.x + p11.y * vn.y) / sn,
				(p12.x * vn.x + p12.y * vn.y) / sn,
				(p13.x * vn.x + p13.y * vn.y) / sn,
				(p14.x * vn.x + p14.y * vn.y) / sn,
			};
			double shadow2[4] = {
				(p21.x * vn.x + p21.y * vn.y) / sn,
				(p22.x * vn.x + p22.y * vn.y) / sn,
				(p23.x * vn.x + p23.y * vn.y) / sn,
				(p24.x * vn.x + p24.y * vn.y) / sn,
			};

			_hwndRenderTarget_->DrawLine(base, { base.x + 1000,base.y }, _scBrush_);
			D2D1_ELLIPSE eshadow[8] = {
				{ {base.x + shadow1[0],base.y},3,3 },
				{ {base.x + shadow1[1],base.y},3,3 },
				{ {base.x + shadow1[2],base.y},3,3 },
				{ {base.x + shadow1[3],base.y},3,3 },
				{ {base.x + shadow2[0],base.y},3,3 },
				{ {base.x + shadow2[1],base.y},3,3 },
				{ {base.x + shadow2[2],base.y},3,3 },
				{ {base.x + shadow2[3],base.y},3,3 },
			};
			COLORF cshadow[8] = { cRed,cOrange,cYellow,cGreen,cCyan,cBlue,cPurple,cWhite };
			for (int os = 0; os < 8; os++) {
				_scBrush_->SetColor(cshadow[os]);
				_hwndRenderTarget_->DrawEllipse(eshadow[os], _scBrush_);
			}
			base.y += 30;


			double max1 = shadow1[0], min1 = shadow1[0], max2 = shadow2[0], min2 = shadow2[0];
			for (int i = 1; i < 4; i++) {
				max1 < shadow1[i] ? max1 = shadow1[i] : 0;
				min1 > shadow1[i] ? min1 = shadow1[i] : 0;

				max2 < shadow2[i] ? max2 = shadow2[i] : 0;
				min2 > shadow2[i] ? min2 = shadow2[i] : 0;
			}
			min1 >= max2 ? hitted = false : 0;
			min2 >= max1 ? hitted = false : 0;
		}
	}


	COLORF cRoRt = cChartreuse;
	if (hitted)cRoRt = cRed;

	D2D1_RECT_F rt = { roRt1.rt_.left,roRt1.rt_.top,roRt1.rt_.right,roRt1.rt_.bottom };
	_scBrush_->SetColor(cBlue);
	_hwndRenderTarget_->DrawRectangle(rt, _scBrush_, 2);

	_hwndRenderTarget_->SetTransform(D2D1::Matrix3x2F::Rotation(roRt1.ang_, { roRt1.CX(),roRt1.CY() }));
	_scBrush_->SetColor(cRoRt);
	_hwndRenderTarget_->DrawRectangle(rt, _scBrush_, 2);
	_scBrush_->SetColor(cRed);
	D2D1_ELLIPSE e = D2D1::Ellipse({ roRt1.CX(),roRt1.CY() }, 5, 5);
	_hwndRenderTarget_->FillEllipse(e, _scBrush_);
	_hwndRenderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());

	

	D2D1_ELLIPSE e11 = D2D1::Ellipse({ roRt1.LT().x,roRt1.LT().y }, 3, 3);
	_scBrush_->SetColor(cOrange);
	_hwndRenderTarget_->FillEllipse(e11, _scBrush_);
	D2D1_ELLIPSE e12 = D2D1::Ellipse({ roRt1.RT().x,roRt1.RT().y }, 3, 3);
	_scBrush_->SetColor(cYellow);
	_hwndRenderTarget_->FillEllipse(e12, _scBrush_);
	D2D1_ELLIPSE e13 = D2D1::Ellipse({ roRt1.LB().x,roRt1.LB().y }, 3, 3);
	_scBrush_->SetColor(cGreen);
	_hwndRenderTarget_->FillEllipse(e13, _scBrush_);
	D2D1_ELLIPSE e14 = D2D1::Ellipse({ roRt1.RB().x,roRt1.RB().y }, 3, 3);
	_scBrush_->SetColor(cCyan);
	_hwndRenderTarget_->FillEllipse(e14, _scBrush_);


	D2D1_RECT_F rt2 = { roRt2.rt_.left,roRt2.rt_.top,roRt2.rt_.right,roRt2.rt_.bottom };
	_scBrush_->SetColor(cBlue);
	_hwndRenderTarget_->DrawRectangle(rt2, _scBrush_, 2);

	_hwndRenderTarget_->SetTransform(D2D1::Matrix3x2F::Rotation(roRt2.ang_, { roRt2.CX(),roRt2.CY() }));
	_scBrush_->SetColor(cRoRt);
	_hwndRenderTarget_->DrawRectangle(rt2, _scBrush_, 2);
	_scBrush_->SetColor(cRed);
	D2D1_ELLIPSE e2 = D2D1::Ellipse({ roRt2.CX(),roRt2.CY() }, 5, 5);
	_hwndRenderTarget_->FillEllipse(e2, _scBrush_);
	_hwndRenderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());

	D2D1_ELLIPSE e21 = D2D1::Ellipse({ roRt2.LT().x,roRt2.LT().y }, 3, 3);
	_scBrush_->SetColor(cOrange);
	_hwndRenderTarget_->FillEllipse(e21, _scBrush_);
	D2D1_ELLIPSE e22 = D2D1::Ellipse({ roRt2.RT().x,roRt2.RT().y }, 3, 3);
	_scBrush_->SetColor(cYellow);
	_hwndRenderTarget_->FillEllipse(e22, _scBrush_);
	D2D1_ELLIPSE e23 = D2D1::Ellipse({ roRt2.LB().x,roRt2.LB().y }, 3, 3);
	_scBrush_->SetColor(cGreen);
	_hwndRenderTarget_->FillEllipse(e23, _scBrush_);
	D2D1_ELLIPSE e24 = D2D1::Ellipse({ roRt2.RB().x,roRt2.RB().y }, 3, 3);
	_scBrush_->SetColor(cCyan);
	_hwndRenderTarget_->FillEllipse(e24, _scBrush_);


	wstring strMouse = L"mouse:" + std::to_wstring(mousePos_.x) + L"," + std::to_wstring(mousePos_.y) + L"\n" +
		std::to_wstring(roRt1.LT().x) + L"," + std::to_wstring(roRt1.LT().y) + L"\n" +
		std::to_wstring(roRt1.RT().x) + L"," + std::to_wstring(roRt1.RT().y) + L"\n" +
		std::to_wstring(roRt1.LB().x) + L"," + std::to_wstring(roRt1.LB().y) + L"\n" +
		std::to_wstring(roRt1.RB().x) + L"," + std::to_wstring(roRt1.RB().y);
	RECTF rtText = { 0,500,500,1000 };
	ShowText(_hwndRenderTarget_, strMouse, rtText, cWhite, 15);


	_hwndRenderTarget_->EndDraw();
}