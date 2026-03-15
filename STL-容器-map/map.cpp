//关联容器，它存储的元素都是键值对（key-value pair）
//根据键（key）自动排序的容器
//map不允许键重复，每个键在map中只能出现一次。
//map容器的每一个元素都是一个pair结构（pair<t1,t2>）的数据。

#include<map>
#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

//在map上使用算法和lambda
void test() {
	map<string, double>coll{ {"tim",9.9},{"struppi",11.77} };
	//每个元素求平方
	for_each(coll.begin(), coll.end(), 
		[](pair<const string, double>& elem) {elem.second *= elem.second; });
	//打印输出
	for_each(coll.begin(), coll.end(),
		[](pair<const string, double>& elem) {cout << elem.first << ": " << elem.second << endl; });
}

//将map当作关联式数组
void test2() {
	typedef map<string, float>StringFloatMap;

	StringFloatMap stocks;//创建空容器
	//插入元素
	stocks["BASF"] = 369.50;
	stocks["VW"] = 413.50;
	stocks["Daimler"] = 819.00;
	stocks["BMW"] = 834.00;
	stocks["Siemens"] = 842.20;
	//打印所有元素
	StringFloatMap::iterator pos;
	cout << left;//设置格式
	for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
		cout << "stock: " << setw(12) << pos->first
			<< "price: " << pos->second << endl;
	}
	cout << endl;

	//价格翻倍
	for (pos = stocks.begin(); pos != stocks.end(); ++pos) pos->second *= 2;

	for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
		cout << "stock: " << setw(12) << pos->first
			<< "price: " << pos->second << endl;
	}
	cout << endl;

	//移除元素
	stocks["Volkswagen"] = stocks["VW"];
	stocks.erase("VW");
	for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
		cout << "stock: " << setw(12) << pos->first
			<< "price: " << pos->second << endl;
	}
	cout << endl;

}

int main() {
	//test();
	test2();
}