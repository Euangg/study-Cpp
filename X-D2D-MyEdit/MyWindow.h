#pragma once
#include<d2d1.h>
#pragma comment(lib,"d2d1.lib")
#include<string>
#include<dwrite.h>
#pragma comment(lib,"dwrite.lib")


class MyWindow {
public:
	//窗口尺寸
	UINT32 width;
	UINT32 height;


	HWND hWnd;//窗口句柄
	ID2D1HwndRenderTarget* target;//用于呈现绘制效果

	//使用dwrite和D2D必要的
	ID2D1Factory* d2dFactory;
	IDWriteFactory* dwriteFactory;

	ID2D1SolidColorBrush* brush;//画刷

	
	bool isRunning;//窗口是否正在运行
public:
	MyWindow();
	~MyWindow();


	//窗口事件，由派生类负责实现
	virtual void onKey(UINT32 vk) {}
	virtual void onChar(UINT32 c) {}
	virtual void onScroll(short delta) {}
	virtual void onMouseEvent(UINT msg, WPARAM wp, LPARAM lp) {}
	virtual void onPaint() {}
	virtual void onResize(UINT32 width, UINT32 height) {}

	//使用字符串创建用于绘制的文本布局(这个就是文本编辑器？)
	IDWriteTextLayout* createTextLayout(const std::wstring& txt);

	void run();
	void createD2DResource();
	void createWindow(const std::wstring& windowTitle, int left, int top, int width, int height);
	LRESULT messageProc(UINT msg, WPARAM wp, LPARAM lp);
	void registerWindow();
	void init();


};


//定义光标移动的方式
enum class SelectMode {
	head, tile,
	lastChar, nextChar,
	lastWord, nextWord,
	absoluteLeading, absoluteTrailing,
	lastLine, nextLine,
	all,
	up, down,
};


class Editor :public MyWindow {
	//Y方向最大滚动 及 当前滚动
	float maxScrollY;
	float scrollY;
	//编辑状态时需要 保持 光标可见，此变量用于 判断 当前是否为滚轮在滚动
	bool isOnScroll;
	//光标所在位置 及 锚点位置，两者之间的文本处于选中状态
	UINT32 caretAnchor;
	UINT32 caretPosition;


	//被编辑的字符串
	std::wstring text;
	//需要更新文本布局的标记，每帧检查
	bool needUpdate;

	//呈现在窗口上的文本布局
	IDWriteTextLayout* textLayout;

	//在输入状态时，光标不应闪烁
	//使用次变量以记录上次的输入时间，绘制时比较当前时间与其差值以判断是否闪烁
	float lastInputTime;

	//记录上次点击时间，用于双击的判断
	float lastClickTime;

	//鼠标双击时，文本会被全选
	//若当前选择不为空，则不进行全选
	UINT32 lastSelectLength;

public:
	Editor();
	~Editor();

	//重写基类函数以响应事件
	void onResize(UINT32 width, UINT32 height)override;
	void onPaint()override;
	void onMouseEvent(UINT msg, WPARAM wp, LPARAM lp)override;
	void onScroll(short delta)override;
	void onKey(UINT32 vk)override;
	void onChar(UINT32 c)override;

	//检查 及 更新 文本布局
	void checkUpdate();

	//三个绘制函数
	void fillSelectedRange();//绘制选中区域
	void drawCaret();//绘制光标
	void drawText();//绘制文本

	//得到选中文本的范围
	DWRITE_TEXT_RANGE getSelectionRange();

	//删除选中文本
	void deleteSelection();

	//使用指定方式移动光标
	void select(SelectMode mode, bool moveAnchor = true);

	//判断两个字符是否是一组
	bool isUnicodeUnit(wchar_t char1, wchar_t char2);

	//复制及粘贴
	void copyToClipboard();
	void pasteFromClipboard();

	//移动光标至指定点
	void setSelectionFromPoint(float x, float y, bool moveAnchor);
};