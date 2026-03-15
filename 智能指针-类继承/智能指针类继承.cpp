#include<memory>
#include<iostream>
using std::shared_ptr;
using std::cout;
using std::endl;

struct sA {
	int a{0};
};

struct sB :sA {
	int b{0};
};
void test1(shared_ptr<sA>a) {
	cout << a->a << endl;
}

int main() {
	shared_ptr<sB> b = std::make_shared<sB>();
	b->a = 9;
	test1(std::static_pointer_cast<sA>(b));
}