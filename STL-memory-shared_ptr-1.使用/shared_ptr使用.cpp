#include<memory>
#include<iostream>
using std::cout;
using std::endl;

//针对堆内存

void OldCode() {
	int* p = new int(5);
	cout << *p << endl;
	delete p;//必须手动释放
}

void NewCode() {
	std::shared_ptr<int> p = std::make_shared<int>(5);
	cout << *p << endl;
}//离开作用域自动释放

void NewCode2() {
	std::shared_ptr<int> p = std::make_shared<int>(5);
	cout << p << ":" << *p << endl;
	p.reset();//也可以手动释放
	cout << p << endl;//变成00000000000
}


void Core() {
	auto sp = std::make_shared<int>(5);
	int* p = sp.get();//获取原指针
	cout << p << ":" << *p << endl;
	(*p)++;
	cout << p << ":" << *p << endl;
	sp.reset();//计数器归0，释放堆内存
	cout << p << ":" << *p << endl;//变成野指针
	(*p)++;
	cout << p << ":" << *p << endl;//可以访问改写，也不报错
}

int main() {
	//OldCode();
	//NewCode();
	//NewCode2();
	Core();
}