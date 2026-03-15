//两端都能快速安插元素和移除元素

#include<iostream>
#include<deque>

using namespace std;

void Test1() {
	//创建一个装string的deque
	deque<string> coll;

	//插入元素
	coll.assign(3, string("string"));
	coll.push_back("last string");
	coll.push_front("first string");

	copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, "\n"));
	cout << endl;

	//移除第一个和最后一个元素
	coll.pop_front();
	coll.pop_back();

	//除了第一个字符串，其他串前面加another
	for (unsigned i = 1; i < coll.size(); ++i)
		coll[i] = "another " + coll[i];//支持下标随机访问
	copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, "\n"));
	cout << endl;

	//往大改变大小（从尾巴开始加）
	coll.resize(5, "resized string");//到多大大小，用什么填充新的
	copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, "\n"));
	cout << endl;

	//往小改变大小（从尾巴开始删）
	coll.resize(1, "resized string");
	copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, "\n"));
	cout << endl;
}

int main() {
	Test1();
}