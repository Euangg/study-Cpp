#pragma once
#include<Windows.h>
//typedef void(*fpMsgProc)(UINT, WPARAM, LPARAM);
typedef void(*fpLoop)();

namespace nXWindow
{
	extern HINSTANCE hins_;
	extern PWSTR className_;
	extern UINT16 wPixs_;
	extern UINT16 hPixs_;
	extern HWND hwnd_;
	extern HDC hdc_;
	extern fpLoop fpInit_;
	extern fpLoop fpLoop_;
	extern fpLoop fpRender_;
	void Init(HINSTANCE hins, PWSTR classname);//绑定实例句柄并注册窗口类
	void GenerateWindow(LPCWSTR wndname, UINT16 wpixs, UINT16 hpixs);//创建窗口
	LRESULT CALLBACK MessageProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);//回调函数
	void RunWindow();//运行窗口

	void emptyLoop();
};
#pragma once
