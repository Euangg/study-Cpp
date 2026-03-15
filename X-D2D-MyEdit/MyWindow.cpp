#include<Windows.h>
#include"MyWindow.h"
#include<vector>
#pragma comment(lib,"winmm.lib")

//方便释放COM资源
template<typename InterfaceType>
inline void SafeRelease(InterfaceType** currentObject) {
	if (*currentObject != nullptr) {
		(*currentObject)->Release();
		*currentObject = nullptr;
	}
}


IDWriteTextLayout* MyWindow::createTextLayout(const std::wstring& text) {
	IDWriteTextLayout* textLayout = nullptr;
	IDWriteTextFormat* textFormat = nullptr;

	dwriteFactory->CreateTextFormat(L"", 0,
		DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		16.0f, L"", &textFormat);
	dwriteFactory->CreateTextLayout(text.c_str(),
		static_cast<UINT32>(text.length()),
		textFormat, width, height, &textLayout);
	SafeRelease<IDWriteTextFormat>(&textFormat);
	return textLayout;
}

void MyWindow::run() {
	//显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg = { 0 };

	isRunning = true;

	while (isRunning) {
		if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else {
			//hWndRenderTarget能自己控制频率
			target->BeginDraw();
			target->Clear(D2D1::ColorF(D2D1::ColorF::White));
			onPaint();
			target->EndDraw();
		}
	}
}

void MyWindow::createD2DResource() {
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory)))
		throw std::exception("create d2dFactory failed");
	if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&dwriteFactory)))
		throw std::exception("create dwrite factory failed");
	if (FAILED(d2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU((UINT32)0, (UINT32)0)), &target)))
		throw std::exception("create hwndTarget failed");

	//设置target的抗锯齿效果
	target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
	target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	//创建画刷
	if (FAILED(target->CreateSolidColorBrush(D2D1::ColorF(0xffffff, 1.0f), &brush)))
		throw std::exception("create brush failed");


}

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

void MyWindow::createWindow(const std::wstring& windowTitle, int left, int top, int width, int height) {
	if (!CreateWindowW(L"myWindow", windowTitle.c_str(), WS_OVERLAPPEDWINDOW,
		left, top, width, height,
		0, 0, HINST_THISCOMPONENT, this)) {
		throw std::exception("create window failed");
	}

	createD2DResource();
}

LRESULT MyWindow::messageProc(UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
	case WM_KEYDOWN:
		onKey(static_cast<UINT>(wp));
		return 0;
	case WM_CHAR:
		onChar(static_cast<UINT>(wp));
		return 0;
	case WM_MOUSEWHEEL:
		onScroll(HIWORD(wp));
		return 0;
	case WM_LBUTTONDOWN:
		SetFocus(hWnd);
		SetCapture(hWnd);
		onMouseEvent(msg, wp, lp);
		return 0;
	case WM_LBUTTONUP:
		onMouseEvent(msg, wp, lp);
		ReleaseCapture();
		return 0;
	case WM_MOUSEMOVE:
		onMouseEvent(msg, wp, lp);
		return 0;
	case WM_PAINT:
		target->BeginDraw();
		target->Clear(D2D1::ColorF(D2D1::ColorF::White));
		onPaint();
		target->EndDraw();
		ValidateRect(hWnd, 0);
		return 0;
	case WM_ERASEBKGND:
		return 0;
	case WM_SIZE: {
		RECT rect;
		GetClientRect(hWnd, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
		if (target) {
			target->Resize(D2D1::SizeU(width, height));
		}
		onResize(width, height);
		return 0;
	}
	case WM_DESTROY:
		isRunning = false;
		return 0;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}


void MyWindow::registerWindow() {
	WNDCLASS wc = { 0 };
	wc.hInstance = HINST_THISCOMPONENT;
	wc.lpszClassName = L"myWindow";
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hIcon = LoadIconA(0, MAKEINTRESOURCEA(IDI_APPLICATION));
	wc.hCursor = LoadCursorA(0, MAKEINTRESOURCEA(IDC_IBEAM));
	wc.cbWndExtra = sizeof(void*);
	wc.lpfnWndProc = [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT {
		MyWindow* window = static_cast<MyWindow*>(reinterpret_cast<void*>(GetWindowLongPtr(hwnd, 0)));
		if (window) {
			return window->messageProc(message, wParam, lParam);
		}
		else {
			if (message == WM_CREATE) {
				LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
				window = static_cast<MyWindow*>(cs->lpCreateParams);

				SetWindowLongPtr(hwnd, 0, reinterpret_cast<LONG_PTR>(window));
				window->hWnd = hwnd;
				return window->messageProc(message, wParam, lParam);
			}
			else return DefWindowProc(hwnd, message, wParam, lParam);
		}
	};

	if (!RegisterClassW(&wc)) {
		throw std::exception("register window failed");
	}
}

void MyWindow::init() {
	registerWindow();
}

MyWindow::~MyWindow()
{
	SafeRelease(&brush);
	SafeRelease(&target);
	SafeRelease(&dwriteFactory);
	SafeRelease(&d2dFactory);
	UnregisterClassW(L"myWindow", HINST_THISCOMPONENT);
}

MyWindow::MyWindow()
{
	hWnd = 0;
	width = 0;
	height = 0;

	isRunning = false;

	d2dFactory = nullptr;
	dwriteFactory = nullptr;
	target = nullptr;
	brush = nullptr;
}
























namespace {
	inline bool IsHighSurrogate(UINT32 ch) throw()
	{
		// 0xD800 <= ch <= 0xDBFF
		return (ch & 0xFC00) == 0xD800;
	}

	inline bool IsLowSurrogate(UINT32 ch) throw()
	{
		// 0xDC00 <= ch <= 0xDFFF
		return (ch & 0xFC00) == 0xDC00;
	}
}
void Editor::setSelectionFromPoint(float x, float y, bool moveAnchor)
{
	BOOL isTrailingHit;
	BOOL isInside;
	DWRITE_HIT_TEST_METRICS caretMetrics;


	textLayout->HitTestPoint(
		x, y,
		&isTrailingHit,
		&isInside,
		&caretMetrics
	);

	if (isTrailingHit) {
		caretPosition = caretMetrics.textPosition + caretMetrics.length;
	}
	else {
		caretPosition = caretMetrics.textPosition;
	}

	if (moveAnchor)
		caretAnchor = caretPosition;

	return;
}

void Editor::pasteFromClipboard() {

	deleteSelection();

	UINT32 characterCount = 0;

	if (OpenClipboard(0)) {
		HGLOBAL hClipboardData = GetClipboardData(CF_UNICODETEXT);

		if (hClipboardData != NULL)
		{
			// Get text and size of text.
			size_t byteSize = GlobalSize(hClipboardData);
			void* memory = GlobalLock(hClipboardData); // [byteSize] in bytes
			const wchar_t* ctext = reinterpret_cast<const wchar_t*>(memory);
			characterCount = static_cast<UINT32>(wcsnlen(ctext, byteSize / sizeof(wchar_t)));

			if (memory != NULL)
			{
				// Insert the text at the current position.
				text.insert(
					caretPosition,
					ctext,
					characterCount
				);

				GlobalUnlock(hClipboardData);

			}
		}
		CloseClipboard();
	}

	caretPosition += characterCount;
	caretAnchor = caretPosition;

	needUpdate = true;
}
void Editor::copyToClipboard()
{
	DWRITE_TEXT_RANGE selectionRange = getSelectionRange();
	if (selectionRange.length <= 0)
		return;

	if (OpenClipboard(0)) {
		if (EmptyClipboard()) {

			size_t byteSize = sizeof(wchar_t) * (selectionRange.length + 1);
			HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE | GMEM_ZEROINIT, byteSize);

			if (hClipboardData != NULL) {
				void* memory = GlobalLock(hClipboardData);

				if (memory != NULL) {
					const wchar_t* ctext = text.c_str();
					memcpy(memory, &ctext[selectionRange.startPosition], byteSize);
					GlobalUnlock(hClipboardData);

					if (SetClipboardData(CF_UNICODETEXT, hClipboardData) != NULL) {
						hClipboardData = NULL;
					}
				}
				GlobalFree(hClipboardData);
			}
		}
		CloseClipboard();
	}
}
bool Editor::isUnicodeUnit(wchar_t char1, wchar_t char2)
{
	return (IsLowSurrogate(char1) && IsHighSurrogate(char2))
		|| (char1 == '\n' && char2 == '\r');
}
void Editor::select(SelectMode mode, bool moveAnchor)
{
	//以下代码使用了dwrite的api

	switch (mode)
	{
	case SelectMode::up:
	case SelectMode::down:
	{
		std::vector<DWRITE_LINE_METRICS> lineMetrics;
		DWRITE_TEXT_METRICS textMetrics;
		textLayout->GetMetrics(&textMetrics);

		lineMetrics.resize(textMetrics.lineCount);
		textLayout->GetLineMetrics(&lineMetrics.front(), textMetrics.lineCount, &textMetrics.lineCount);


		UINT32 line = 0;
		UINT32 linePosition = 0;
		UINT32 nextLinePosition = 0;
		UINT32 lineCount = static_cast<UINT32>(lineMetrics.size());
		for (; line < lineCount; ++line)
		{
			linePosition = nextLinePosition;
			nextLinePosition = linePosition + lineMetrics[line].length;
			if (nextLinePosition > caretPosition) {
				break;
			}
		}

		if (line > lineCount - 1) {
			line = lineCount - 1;
		}

		if (mode == SelectMode::up)
		{
			if (line <= 0)
				break;
			line--;
			linePosition -= lineMetrics[line].length;
		}
		else
		{
			linePosition += lineMetrics[line].length;
			line++;
			if (line >= lineMetrics.size())
				break;
		}

		DWRITE_HIT_TEST_METRICS hitTestMetrics;
		float caretX, caretY, dummyX;

		textLayout->HitTestTextPosition(
			caretPosition,
			false,
			&caretX,
			&caretY,
			&hitTestMetrics
		);

		textLayout->HitTestTextPosition(
			linePosition,
			false,
			&dummyX,
			&caretY,
			&hitTestMetrics
		);

		BOOL isInside, isTrailingHit;
		textLayout->HitTestPoint(
			caretX,
			caretY,
			&isTrailingHit,
			&isInside,
			&hitTestMetrics
		);

		caretPosition = hitTestMetrics.textPosition;

		if (isTrailingHit) {
			caretPosition += hitTestMetrics.length;
		}
		break;
	}
	case SelectMode::head:
		caretPosition = 0;
		break;
	case SelectMode::tile:
		caretPosition = text.length();
		break;
	case SelectMode::lastChar:
		if (caretPosition > 0) {
			UINT32 moveCount = 1;

			if (caretPosition >= 2
				&& caretPosition <= text.length())
			{
				if (isUnicodeUnit(text[caretPosition - 1], text[caretPosition - 2]))
				{
					moveCount = 2;
				}
			}
			if (caretPosition < (UINT32)moveCount)
				caretPosition = 0;
			else caretPosition -= moveCount;
		}
		break;
	case SelectMode::nextChar:
		if (caretPosition < text.length()) {
			UINT32 moveCount = 1;
			if (caretPosition >= 0
				&& caretPosition <= text.length() - 2)
			{
				wchar_t charBackOne = text[caretPosition];
				wchar_t charBackTwo = text[caretPosition + 1];
				if (isUnicodeUnit(text[caretPosition], text[caretPosition + 1]))
				{
					moveCount = 2;
				}
			}
			if (caretPosition > text.length())
				caretPosition = text.length();
			else caretPosition += moveCount;
		}
		break;
	case SelectMode::lastWord:
	case SelectMode::nextWord: {
		std::vector<DWRITE_CLUSTER_METRICS> clusterMetrics;
		UINT32 clusterCount;
		textLayout->GetClusterMetrics(NULL, 0, &clusterCount);
		if (clusterCount == 0)
			break;

		clusterMetrics.resize(clusterCount);
		textLayout->GetClusterMetrics(&clusterMetrics.front(), clusterCount, &clusterCount);

		UINT32 clusterPosition = 0;
		UINT32 oldCaretPosition = caretPosition;

		if (mode == SelectMode::lastWord) {

			caretPosition = 0;
			for (UINT32 cluster = 0; cluster < clusterCount; ++cluster) {

				clusterPosition += clusterMetrics[cluster].length;
				if (clusterMetrics[cluster].canWrapLineAfter) {
					if (clusterPosition >= oldCaretPosition)
						break;

					caretPosition = clusterPosition;
				}

			}

		}
		else {
			for (UINT32 cluster = 0; cluster < clusterCount; ++cluster) {
				UINT32 clusterLength = clusterMetrics[cluster].length;

				if (clusterPosition + clusterMetrics[cluster].length > oldCaretPosition && clusterMetrics[cluster].canWrapLineAfter) {
					caretPosition = clusterPosition + clusterMetrics[cluster].length;
					break;

				}
				clusterPosition += clusterLength;
				caretPosition = clusterPosition;
			}
		}
		break;
	}
	case SelectMode::absoluteLeading: {
		DWRITE_HIT_TEST_METRICS hitTestMetrics;
		float caretX, caretY;

		textLayout->HitTestTextPosition(
			caretPosition,
			false,
			&caretX,
			&caretY,
			&hitTestMetrics
		);

		caretPosition = hitTestMetrics.textPosition;

		break;
	}
	case SelectMode::absoluteTrailing: {
		DWRITE_HIT_TEST_METRICS hitTestMetrics;
		float caretX, caretY;

		textLayout->HitTestTextPosition(
			caretPosition,
			true,
			&caretX,
			&caretY,
			&hitTestMetrics
		);

		caretPosition = hitTestMetrics.textPosition + hitTestMetrics.length;
		break;
	}
	case SelectMode::all:
		caretAnchor = 0;
		caretPosition = text.length();
		return;
	default:
		break;
	}

	if (moveAnchor)
		caretAnchor = caretPosition;

}

void Editor::deleteSelection()
{
	DWRITE_TEXT_RANGE range = getSelectionRange();

	if (range.length <= 0)
		return;

	text.erase(range.startPosition, range.length);

	caretPosition = range.startPosition;
	caretAnchor = caretPosition;

	needUpdate = true;
}
void Editor::drawText()
{
	//文本为黑色
	brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

	target->DrawTextLayout(D2D1::Point2F(0, -scrollY), textLayout, brush);
}

void Editor::drawCaret()
{
	DWRITE_HIT_TEST_METRICS caretMetrics;
	float caretX, caretY;
	textLayout->HitTestTextPosition(caretPosition, false, &caretX, &caretY, &caretMetrics);

	//若不处于滚动状态，则对光标位置进行判断修改，使其处于显示区域
	if (!isOnScroll) {
		if (caretY - scrollY + caretMetrics.height > height) {//光标超出窗口底部
			scrollY = caretY - height + caretMetrics.height;
		}
		else if (caretY - scrollY < 0) {//光标在窗口上方
			scrollY = caretY;
		}
	}

	//使用sin函数决定是否绘制caret
	if (sin((timeGetTime() / 1000.f - lastInputTime) * 6.28f) > -0.1) {

		//caret颜色为黑色
		brush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

		target->DrawLine(D2D1::Point2F(caretX, caretY - scrollY)
			, D2D1::Point2F(caretX, caretY + caretMetrics.height - scrollY), brush);

	}
}
DWRITE_TEXT_RANGE Editor::getSelectionRange() {
	UINT32 caretBegin = caretAnchor;
	UINT32 caretEnd = caretPosition;
	if (caretBegin > caretEnd)
		std::swap(caretBegin, caretEnd);
	UINT32 textLength = (UINT32)(text.length());

	if (caretBegin > textLength)
		caretBegin = textLength;

	if (caretEnd > textLength)
		caretEnd = textLength;

	return { caretBegin,caretEnd - caretBegin };
}

void Editor::fillSelectedRange() {
	UINT32 actualHitTestCount = 0;
	auto selectedRange = getSelectionRange();
	if (selectedRange.length > 0) {
		textLayout->HitTestTextRange(selectedRange.startPosition, selectedRange.length, 0, 0, 0, 0, &actualHitTestCount);
		std::vector<DWRITE_HIT_TEST_METRICS>hitTestMetrics(actualHitTestCount);
		textLayout->HitTestTextRange(selectedRange.startPosition, selectedRange.length, 0, -scrollY, &hitTestMetrics[0], static_cast<UINT32>(hitTestMetrics.size()), &actualHitTestCount);

		//改变画刷为天蓝色
		brush->SetColor(D2D1::ColorF(D2D1::ColorF::Gold));
		//遍历选中区域并进行填充
		for (UINT32 i = 0; i < actualHitTestCount; i++) {
			const DWRITE_HIT_TEST_METRICS& htm = hitTestMetrics[i];
			D2D1_RECT_F highlightRect = {
				htm.left,
				htm.top,
				(htm.left + htm.width),
				(htm.top + htm.height)
			};
			target->FillRectangle(highlightRect, brush);
		}
	}
}


void Editor::checkUpdate() {
	if (needUpdate) {
		IDWriteTextLayout* temp = createTextLayout(text);
		if (temp) {
			SafeRelease(&textLayout);//释放上一个文本布局
			textLayout = temp;
			needUpdate = false;
		}
		//获取文本区域的宽高
		DWRITE_TEXT_METRICS metrics;
		textLayout->GetMetrics(&metrics);

		//修改更新后的滚动值
		maxScrollY = max(metrics.height - height, 0);
		if (scrollY > maxScrollY)scrollY = maxScrollY;
	}
}
void Editor::onScroll(short delta)
{
	isOnScroll = true;

	//滚动事件发生不意味着滚动值改变

	float nextScroll = scrollY - delta;

	if (nextScroll < 0)
		nextScroll = 0;
	else if (nextScroll > maxScrollY)
		nextScroll = maxScrollY;

	if (nextScroll != scrollY) {
		scrollY = nextScroll;
		needUpdate = true;
	}

}
void Editor::onMouseEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	float x = (float)(short)LOWORD(lp);
	float y = (float)(short)HIWORD(lp);

	float time = timeGetTime() / 1000.f;

	const float doubleClickInterval = 0.3f;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		isOnScroll = false;
		lastSelectLength = getSelectionRange().length;
		setSelectionFromPoint(x, y + scrollY, (GetKeyState(VK_SHIFT) & 0x80) == 0);
		break;
	case WM_LBUTTONUP:
		if (time - lastClickTime < doubleClickInterval) {
			if (lastSelectLength == 0)
				select(SelectMode::all);
		}
		lastClickTime = time;
		break;
	case WM_MOUSEMOVE:
		if ((wp & MK_LBUTTON) != 0)
			setSelectionFromPoint(x, y + scrollY, false);
		break;
	default:
		break;
	}
}

void Editor::onKey(UINT32 vk)
{
	bool heldShift = (GetKeyState(VK_SHIFT) & 0x80) != 0;
	bool heldControl = (GetKeyState(VK_CONTROL) & 0x80) != 0;
	bool heldAlt = (GetKeyState(VK_MENU) & 0x80) != 0;

	switch (vk)
	{
	case VK_RETURN:
		deleteSelection();
		wchar_t chars[3];
		chars[0] = '\n';
		chars[1] = 0;
		text.insert(caretPosition, chars, 1);

		caretPosition += 1;
		caretAnchor = caretPosition;

		needUpdate = true;
		break;
	case VK_BACK:

		if (caretPosition != caretAnchor)
		{
			deleteSelection();
		}
		else if (caretPosition > 0)
		{
			UINT32 count = 1;
			if (caretPosition >= 2
				&& caretPosition <= text.length())
			{
				wchar_t charBackOne = text[caretPosition - 1];
				wchar_t charBackTwo = text[caretPosition - 2];
				if ((IsLowSurrogate(charBackOne) && IsHighSurrogate(charBackTwo))
					|| (charBackOne == '\n' && charBackTwo == '\r'))
				{
					count = 2;
				}
			}

			caretPosition -= count;
			caretAnchor = caretPosition;

			text.erase(caretPosition, count);

			needUpdate = true;

		}
		break;
	case VK_DELETE:
		if (caretPosition != caretAnchor) {
			deleteSelection();
		}
		else {
			DWRITE_HIT_TEST_METRICS hitTestMetrics;
			float caretX, caretY;

			textLayout->HitTestTextPosition(
				caretPosition,
				false,
				&caretX,
				&caretY,
				&hitTestMetrics
			);

			text.erase(hitTestMetrics.textPosition, hitTestMetrics.length);
			needUpdate = true;
		}

		break;
	case VK_TAB:
		break;
	case VK_LEFT:
		if (!heldControl)
			select(SelectMode::lastChar, !heldShift);
		else
			select(SelectMode::lastWord, !heldShift);
		break;

	case VK_RIGHT:
		if (!heldControl)
			select(SelectMode::nextChar, !heldShift);
		else
			select(SelectMode::nextWord, !heldShift);
		break;
	case VK_UP:
		select(SelectMode::up);
		break;
	case VK_DOWN:
		select(SelectMode::down);
		break;
	case VK_HOME:
		select(SelectMode::head);
		break;
	case VK_END:
		select(SelectMode::tile);
		break;
	case 'C':
		if (heldControl)
			copyToClipboard();
		break;
	case VK_INSERT:
		if (heldControl)
			copyToClipboard();
		else if (heldShift) {
			pasteFromClipboard();
		}
		break;
	case 'V':
		if (heldControl) {
			pasteFromClipboard();
		}
		break;
	case 'X':
		//剪切文本，先复制再删除
		if (heldControl) {
			copyToClipboard();
			deleteSelection();
		}
		break;
	case 'A':
		if (heldControl) {
			select(SelectMode::all);
		}
		break;
	default:
		return;
	}
	isOnScroll = false;
	lastInputTime = timeGetTime() / 1000.f;
}
void Editor::onChar(UINT32 c) {
	if (c >= 0x20 || c == 9) {
		deleteSelection();
		UINT32 charsLength = 1;
		wchar_t chars[2] = { static_cast<wchar_t>(c), 0 };
		if (c > 0xFFFF)
		{
			chars[0] = wchar_t(0xD800 + (c >> 10) - (0x10000 >> 10));
			chars[1] = wchar_t(0xDC00 + (c & 0x3FF));
			charsLength++;
		}

		text.insert(caretPosition, chars, charsLength);

		caretPosition += charsLength;
		caretAnchor = caretPosition;

		needUpdate = true;
		isOnScroll = false;

		lastInputTime = timeGetTime() / 1000.f;
	}
}

void Editor::onPaint() {
	checkUpdate();
	if (textLayout) {
		fillSelectedRange();
		drawCaret();
		drawText();
	}
}
void Editor::onResize(UINT32 width, UINT32 height)
{
	needUpdate = true;
}
Editor::~Editor()
{
	SafeRelease(&textLayout);
}
Editor::Editor() {
	maxScrollY = 0.f;
	scrollY = 0.f;

	lastInputTime = -1.f;
	lastClickTime = -1.f;
	lastSelectLength = 0;

	isOnScroll = false;

	textLayout = nullptr;
	needUpdate = true;
	caretAnchor = 0;
	caretPosition = 0;
	text = L"asdfasdfasdfasdf";
}

