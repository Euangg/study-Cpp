#include<algorithm>
#include<iostream>
#include<vector>
using std::cout;
using std::endl;

//向上取整，ceil
void pro_ceil() {
	float x = 9.8754f;
	cout << std::ceil(x) << endl;//10
}

//单边钳制，min、max
void pro_min() {
	float x = 1.665f;
	cout << std::min(x, 2.2f) << endl;//1.665f
	cout << std::max(x, 0.2f) << endl;//1.665f
}

//双侧钳制，clamp
void pro_clamp() {
	int a = 10;
	a = std::clamp(a, 2, 4);
	cout << a << endl;//会改写a的值
}

//遍历处理，for_each
void pro_for_each() {
	std::vector<std::pair<int, int>>v(5, { 1,2 });
	for (auto& e : v)cout << e.first << "," << e.second << endl;
	std::for_each(v.begin(), v.end(), [](auto& e) {e.first = 44; e.second = 66; });//参数必须要加&，否则改的只是形参
	for (auto& e : v)cout << e.first << "," << e.second << endl;
}
//按值查找，find
void pro_find() {
	std::vector v{ 1,2,3,4,5 };
	auto d = std::find(v.begin(), v.end(), 5);
	if (d == v.end()) { cout << "end" << endl; }
	else { *d = 8; cout << *d << endl; }
}
//条件查找，find_if
void pro_find_if() {
	std::vector v{ 1,2,3,4,5 };
	auto d = std::find_if(v.begin(), v.end(), [](int& x) {return x == 4; });
	if (d == v.end()) { cout << "end" << endl; }
	else{ cout << *d << endl; }
}
//全部检查，all_of、none_of、any_of
void pro_all_of() {
	std::vector<bool>v(5, true);

	bool b1 = std::all_of(v.begin(), v.end(), [](bool b) {return b; });
	bool b2 = std::any_of(v.begin(), v.end(), [](bool b) {return b; });
	bool b3 = std::none_of(v.begin(), v.end(), [](bool b) {return b; });

	cout << b1 << "," << b2 << "," << b3 << endl;
}

int main() {
	pro_clamp();
	//pro_for_each();
}