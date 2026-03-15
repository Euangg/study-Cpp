//在实际开发中，重载new和delete主要目的是为了实现内存池
//内存池在高性能的服务程序中很常见

//预分配一大块的内存空间——内存池
//	要用内存优先向内存池借

//1）提升分配和归还速度
//2）减少内存碎片


#include<iostream>
using namespace std;

//void* operator new(size_t size) {
//	cout << "调用了全局重载的new:" << size << "byte" << endl;
//	void* ptr = malloc(size);//申请内存
//	cout << "申请到的内存地址是:" << ptr << endl;
//	return ptr;
//}
//
//void operator delete(void* ptr) {
//	cout << "调用了全局重载的delete" << endl;
//	if (ptr == 0)return;//保证对空指针delete是安全的
//	free(ptr);//释放内存
//}

class CGirl {
public:
	int m_bh;
	int m_xw;
	static char* m_pool;//内存池的起始地址

	CGirl(int bh, int xw) { 
		m_bh = bh, m_xw = xw;
		cout << "调用了构造函数CGirl()" << endl;
	}
	~CGirl() {
		cout << "调用了析构函数~CGirl()" << endl;
	}

	static bool initpool() {
		m_pool = (char*)malloc(18);
		if (m_pool == 0)return false;//申请失败返回false
		memset(m_pool, 0, 18);//将内存池的内容初始化为0
		cout << "内存池的起始地址是：" << (void*)m_pool << endl;
		return true;
	}

	static void freepool() {
		if (m_pool == 0)return;
		free(m_pool);
		cout << "内存池已释放" << endl;
	}

	void* operator new(size_t size) {
		//cout << "调用了类重载的new:" << size << "byte" << endl;
		//void* ptr = malloc(size);//申请内存
		//cout << "申请到的内存地址是" << ptr << endl;
		//return ptr;
		//---------------------------------------------------------------改为向内存池申请
		if (m_pool[0] == 0) {//判断第一个位置是否空闲
			cout << "分配了第一块内存:" << (void*)(m_pool + 1) << endl;
			m_pool[0] = 1;	//把第一个位置的标志位置为已分配
			return m_pool + 1;//返回第一个用于存放对象的地址
		}
		if (m_pool[9] == 0) {//判断第二个位置是否空闲
			cout << "分配了第二块内存:" << (void*)(m_pool + 9) << endl;
			m_pool[9] = 1;	//把第二个位置的标志位置为已分配
			return m_pool + 9;//返回第二个用于存放对象的地址
		}
		//如果上面两个位置都不可用，那就直接向系统申请内存
		void* ptr = malloc(size);
		cout << "申请到的内存地址是" << ptr << endl;
		return ptr;

		//如果内存池用完了，一般三种处理方法：
		//1)扩展内存池
		//2)向系统申请内存
		//3)返回空地址（不给分配）
	}

	void operator delete(void* ptr) {
		//cout << "调用了类重载的delete" << endl;
		//if (ptr == 0)return;//保证对空指针安全
		//free(ptr);//free对空指针其实也是安全的
		//---------------------------------------------------------------改为向内存池相关
		if (ptr == 0)return;//保证对空指针安全
		if (ptr == m_pool + 1) {//若传入第一块地址
			cout << "释放了第一块内存" << endl;
			m_pool[0] = 0;//将标志1置位空闲
			return;
		}
		if (ptr == m_pool + 9) {
			cout << "释放了第二块内存" << endl;
			m_pool[9] = 0;//将标志2置位空闲
			return;
		}
		//如果不属于内存池，归还系统
		free(ptr);
	}

};

char* CGirl::m_pool = 0;

int main() {
	//证明：free对空指针安全
	//int* a = nullptr;
	//free(a);
	//cout << "刚刚free了nullptr" << endl;


	//内存池使用效果
	//初始化内存池
	if (CGirl::initpool() == false) {
		cout << "初始化内存池失败" << endl;
		return -1;
	}

	CGirl* p1 = new CGirl(1, 8);
	cout << "p1的地址：" << p1 << "，编号：" << p1->m_bh << "，XW：" << p1->m_xw << endl;

	CGirl* p2 = new CGirl(2, 9);
	cout << "p2的地址：" << p2 << "，编号：" << p2->m_bh << "，XW：" << p2->m_xw << endl;

	CGirl* p3 = new CGirl(3, 10);
	cout << "p3的地址：" << p3 << "，编号：" << p3->m_bh << "，XW：" << p3->m_xw << endl;

	delete p1;

	CGirl* p4 = new CGirl(4, 11);
	cout << "p4的地址：" << p4 << "，编号：" << p4->m_bh << "，XW：" << p4->m_xw << endl;

	delete p2;
	delete p3;
	delete p4;

	CGirl::freepool();//释放内存池

	return 0;
}
