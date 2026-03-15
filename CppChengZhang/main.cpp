#include<iostream>
using namespace std;

class CGirl {
public:
	string m_name;
	int m_age;
	int* m_ptr;//指针成员，计划使用堆内存

	//构造函数
	CGirl() { m_name.clear(); m_age = 0; m_ptr = nullptr; cout << "调用了CGirl()构造函数\n"; };
	//没有重载的（默认的）拷贝构造函数
	CGirl(const CGirl& gg) { 
		m_name = "漂亮的" + gg.m_name; m_age = gg.m_age - 1; 
		m_ptr = new int;
		//*m_ptr = *gg.m_ptr;
		memcpy(m_ptr, gg.m_ptr, sizeof(int));
		cout << "调用了CGirl(const CGirl& gg)拷贝构造函数\n"; };
	//重载的拷贝构造函数
	CGirl(const CGirl& gg, int ii) { m_name = "漂亮的" + gg.m_name; m_age = gg.m_age - ii; m_ptr = gg.m_ptr; cout << "调用了CGirl(const CGirl& gg,int ii)拷贝构造函数\n"; };
	//析构函数
	~CGirl() { 
		delete m_ptr;//delete空指针是安全的
		m_ptr = nullptr;
		cout << "调用了~CGirl()\n"; };


	void show() { cout << "姓名：" << m_name << "，年龄：" << m_age << "，m_ptr=" << m_ptr << ",*m_ptr=" << *m_ptr << endl; };
};


int main() {
	CGirl g1;
	g1.m_name = "西施";
	g1.m_age = 23;
	g1.m_ptr = new int(3);
	g1.show();



	CGirl g2(g1);
	*g2.m_ptr = 8;
	g1.show();
	g2.show();

	cout << "退出main函数" << endl;
}