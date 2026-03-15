#define _CRT_SECURE_NO_WARNINGS
#include<chrono>
#include<iostream>
#include<iomanip>
#include<sstream>
using namespace std;
int main() {
	//静态成员函数chrono::system_clock::now()用于获取系统时间（C++时间）
	chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();

	//静态成员函数chrono::system_clock::to_time_t()把系统时间转换为time_t（UTC时间，世界协调时）
	time_t t_now = chrono::system_clock::to_time_t(now);

	t_now = t_now + 24 * 60 * 60;	//把当前时间加1天
	t_now = t_now - 1 * 60 * 60;	//把当前时间减1小时
	t_now = t_now + 120;			//把当前时间加120秒

	//std::localtime()函数把time_t转化成本地时间（北京时间）
	//注：localtime()不是线程安全的，VS用localtime_s代替，Linux用localtime_r代替
	tm* tm_now = std::localtime(&t_now);

	//格式化输出tm结构体中的成员
	cout << put_time(tm_now, "%Y-%m-%d %H:%M:%S") << endl;
	cout << put_time(tm_now, "%Y-%m-%d") << endl;
	cout << put_time(tm_now, "%H:%M:%S") << endl;
	cout << put_time(tm_now, "%Y%m%d%H%M%S") << endl;

	stringstream ss;
	ss << put_time(tm_now, "%Y-%m-%d %H:%M:%S");
	string timestr = ss.str();
	cout << timestr << endl;
}