#include<memory>
#include<iostream>
using std::cout;
using std::endl;

void OldCode() {
	int* p1 = new int(6);
	int* p2{ p1 };
	cout << p2 << ":" << *p2 << endl;

	delete p2;
	cout << p1 << ":" << *p1 << endl;//p1成为野指针
}//多指针指向同一块堆内存，释放管理问题

void NewCode() {
	std::shared_ptr<int> p1 = std::make_shared<int>(6);
	auto p2 = p1;
	cout << p2 << ":" << *p2 << endl;

	p2.reset();
	cout << p1 << ":" << *p1 << endl;
}//其实也存在管理问题，要保证创建的shared_ptr都释放，一般shared_ptr放在栈上

void Core() {
	auto sptr1 = std::make_shared<int>(21);
	cout << sptr1.unique() << endl;//是否独占//使用记数是否为1
	cout << sptr1.use_count() << endl;//使用计数
	auto sptr2 = sptr1;//计数+1
	cout << sptr1.unique() << endl;
	cout << sptr1.use_count() << endl;
	cout << sptr2.unique() << endl;
	cout << sptr2.use_count() << endl;
	sptr1.reset();//主动释放，计数-1
	cout << "sptr1:" << sptr1 << endl;//000000
	cout << sptr1.unique() << endl;//0，释放后仍可用
	cout << sptr1.use_count() << endl;//0，释放后仍可用
	cout << sptr2.unique() << endl;
	cout << sptr2.use_count() << endl;
}

int main() {
	//OldCode();
	//NewCode();
	Core();
}