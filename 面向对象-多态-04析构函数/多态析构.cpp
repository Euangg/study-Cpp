#include<iostream>
using namespace std;

struct sA {
	virtual void Update() {};
	virtual ~sA(){
		cout << "调用了A的析构函数" << endl;
	}
	//将析构函数设为虚函数
};

struct sB:sA{
	void Update()override {};

	~sB()override {
		cout << "调用了B的析构函数" << endl;
	}
};

struct sC :sB {
	void Update()override {};

	~sC() {
		cout << "调用了C的析构函数" << endl;
	} //会逐级调用析构
};

int main() {
	sA* _p = new sC;
	delete _p;
}