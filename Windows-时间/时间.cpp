#include<iostream>
using namespace std;

#include<Windows.h>

//高精度计时器
void Test1() {
	LARGE_INTEGER l;
	QueryPerformanceFrequency(&l);

	cout << l.QuadPart << endl;

	LARGE_INTEGER tag;
	while (1) {
		if (GetAsyncKeyState('A')) {
			QueryPerformanceCounter(&tag);
			cout << tag.QuadPart / l.QuadPart << endl;//秒级
		}
		if (GetAsyncKeyState(VK_ESCAPE))break;
	}
}

//获取日期时间
void Test2() {
	while (1) {
		if (GetAsyncKeyState('A')) {
			std::time_t now = std::time(nullptr);
			std::tm* now_tm = std::localtime(&now);
			cout << now_tm->tm_year+1900 << "-" << now_tm->tm_mon+1 << "-" << now_tm->tm_mday<<"\t"<< now_tm->tm_hour << ":" << now_tm->tm_min << ":" << now_tm->tm_sec << endl;
			//delete now_tm;
		}
		if (GetAsyncKeyState(VK_ESCAPE))break;
	}
}

int main() {
	Test2();
}