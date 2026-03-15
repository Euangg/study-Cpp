#include<iostream>
using namespace std;

struct sPeople {
	int no_;
	string name_;
	sPeople* pnext_;
};

struct Bug {
	bool canClone{ false };
	Bug* child[4] {nullptr};
	Bug* father{ nullptr };
	void CreateChild() {
		Bug* pchild = new Bug();
		child[0] = pchild;
		pchild->father = this;
	}
	void check1() {
		for (auto& c : child) {

		}
	}
	void check2() {
		father;
	}
};

//单向链表，只知道下一任
//双向链表，知道上一任也知道下一任

int main() {
	//1.添加操作
	sPeople* phead = nullptr, * ptail = nullptr, * ptemp = nullptr;//1.一次定义多个指针变量，要保证每个变量名有*开头，怪不得别人定义指针变量是将*与变量名连着写，
	//而我一般*紧接在类型后
	//分配第一个节点
	ptemp = new sPeople({ 1,"王龙" });
	if (phead == nullptr)phead = ptemp;//检查是否需要分配到头
	if (ptail != nullptr)ptail->pnext_ = ptemp;//检查并连接到上一个节点后
	ptail = ptemp;//移动尾指针
	//分配第二个节点
	ptemp = new sPeople({ 2,"水怪" });
	if (phead == nullptr)phead = ptemp;//检查是否需要分配到头
	if (ptail != nullptr)ptail->pnext_ = ptemp;//检查并连接到上一个节点后
	ptail = ptemp;//移动尾指针
	//分配第三个节点
	ptemp = new sPeople({ 3,"八王" });
	if (phead == nullptr)phead = ptemp;//检查是否需要分配到头
	if (ptail != nullptr)ptail->pnext_ = ptemp;//检查并连接到上一个节点后
	ptail = ptemp;//移动尾指针


	//2.遍历操作
	sPeople* phead2 = nullptr, * ptail2 = nullptr, * ptemp2 = nullptr;
	phead2 = phead;
	ptemp2 = phead2;//定位
	while (ptemp2 != nullptr) {
		cout << "编号：" << ptemp2->no_ << "\t名称：" << ptemp2->name_ << "\t下一个：" << ptemp2->pnext_ << endl;
		ptemp2 = ptemp2->pnext_;
	}


	//3.内存释放操作
	sPeople* phead3 = nullptr, * ptail3 = nullptr, * ptemp3 = nullptr;
	phead3 = phead;
	while (phead3 != nullptr) {
		ptemp3 = phead3;//操作节点准备
		cout << "准备删除编号：" << ptemp3->no_ << "\t名称：" << ptemp3->name_ << "\t下一个：" << ptemp3->pnext_ << endl;

		phead3 = phead3->pnext_;//头节点后移
		delete ptemp3;
	}
}