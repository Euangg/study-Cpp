#include<list>
#include<map>
#include<iostream>
using namespace std;

struct sUnknown {
	int i = 0;
	void Update(double dt) {
		
	};
};

void Test01() {
	list<sUnknown*>listUnknown;
	sUnknown* p = new sUnknown;

	cout << p << endl;
	if (p)cout << "p是有效指针" << endl;

	listUnknown.push_back(p);

	for (auto& u : listUnknown) {
		u->Update(0);
		delete u;
		u = nullptr;
	}
	listUnknown.clear();

	cout << p << endl;
	if (p)cout << "p是有效指针" << endl;
	//p被删了都不知道
}

//句柄思想，用句柄统一管理指针的操作
void Test02() {
	map<int, sUnknown*>mapUnknown;
	mapUnknown[0] = new sUnknown;

	cout << mapUnknown[0] << endl;
	if (mapUnknown[0])cout << "mapUnknown[0]是有效指针" << endl;

	for (auto& u : mapUnknown) {
		if (u.second)u.second->Update(0);
		delete u.second;
		u.second = nullptr;
	}

	cout << mapUnknown[0] << endl;
	if (mapUnknown[0])cout << "mapUnknown[0]是有效指针" << endl;

	cout << mapUnknown.size() << endl;
	mapUnknown.clear();
	cout << mapUnknown.size() << endl;

	cout << mapUnknown[0] << endl;
	if (mapUnknown[0])cout << "mapUnknown[0]是有效指针" << endl;
	cout << mapUnknown.size() << endl;
}


int main() {
	Test02();
}