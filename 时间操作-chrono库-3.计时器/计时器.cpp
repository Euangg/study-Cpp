#include<iostream>
#include<chrono>
using namespace std;

int main() {
	//静态成员函数chrono::steady_clock::now()获取开始的时间点
	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	//消耗时间
	cout << "开始计时" << endl;
	for (int ii = 0; ii < 1000000; ii++){

	}
	cout << "计时完成" << endl;

	//静态成员函数chrono::steady_clock::now()获取结束的时间点
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	//计算消耗时间
	chrono::nanoseconds dt = end - start;
	cout << "耗时" << dt.count() << "纳秒(" <<(double)dt.count()/(1000*1000*1000)<<"秒)" << endl;
}