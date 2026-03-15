#include<map>
#include<string>
#include<iostream>
using namespace std;
//为模板起别名-typedef
template<typename T>
struct MyMap { typedef map<int, T> mapType; };
template<typename T>
class Container {
public:
	void print(T& t) {
		auto it = t.begin();
		for (; it != t.end(); ++it) cout << it->first << "," << it->second << endl;
	}
};
void test1() {
	MyMap<int>::	mapType mm1;//使用别名
	mm1.insert(make_pair(1, 1));
	mm1.insert(make_pair(2, 2));
	mm1.insert(make_pair(3, 3));
	Container<MyMap<int>::mapType>c1;//使用遍历
	c1.print(mm1);

	MyMap<double>::	mapType mm2;
	mm2.insert(make_pair(1, 1.1));
	mm2.insert(make_pair(2, 2.2));
	mm2.insert(make_pair(3, 3.3));

	MyMap<string>::	mapType mm3;
	mm3.insert(make_pair(1, "hello"));
	mm3.insert(make_pair(2, "world"));
	mm3.insert(make_pair(3, "asdf"));
}

//为模板起别名-using
template<typename T>
using MMap = map<int, T>;
void test2() {
	MMap<int>mm1;
	mm1.insert(make_pair(1, 1));
	mm1.insert(make_pair(2, 2));
	mm1.insert(make_pair(3, 3));
	Container<MMap<int>>c1;//使用遍历
	c1.print(mm1);
}


int main() {
	//test1();
	test2();
}