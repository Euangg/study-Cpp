#include<iostream>
using namespace std;

int main() {
	string str = R"tag(adfasdf\adasdfads
	sfadsf\a\t)tag";//换行、制表也全部保留
	//tag标签前后要保持一致，不能中文
	cout << str;
}