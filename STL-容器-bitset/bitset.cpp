#include<bitset>
#include<iostream>
using std::cout;
using std::endl;

//创建
void test1() {
	{
		std::bitset<65> bt;//默认全部位为0
		cout << "sizeof():" << sizeof(bt) << endl;//4byte(32bit)一阶
		cout << "bt=" << bt << ",bt.size():" << bt.size() << endl;
	}
	{
		std::bitset<32> bt(9);//填int，换算2进制，填入低位   9:1001
		cout << "sizeof():" << sizeof(bt) << endl;//4byte(32bit)一阶
		cout << "bt=" << bt << ",bt.size():" << bt.size() << endl;//几个位
	}
	{
		std::bitset<32> bt("0011");//填string，只能包含01，填入低位
		cout << "sizeof():" << sizeof(bt) << endl;//4byte(32bit)一阶
		cout << "bt=" << bt << ",bt.size():" << bt.size() << endl;
	}
}
//访问
void test2() {
	std::bitset<32> bt;
	cout << "bt=" << bt << endl;
	bt[2] = 3;
	cout <<"bt[2]:" << bt[2] << endl;//下标随机访问
	cout << "bt.test(2):" << bt.test(2) << endl;//方法访问

	bt[7] = -1;//填非0就是1
	cout << "bt=" << bt << endl;
	for (int i = 0; i < bt.size(); ++i)bt[i] = 1;
	cout << bt.all() << endl;//是否全为1
	cout << bt.any() << endl;//是否有1
	cout << bt.none() << endl;//是否没1
	cout << bt.count() << endl;//有几个1

	//操作
	bt.set();//不填全部置1
	cout << "bt=" << bt << endl;
	bt.reset();//不填全部置0
	cout << "bt=" << bt << endl;
	bt.flip();//不填全部置反位1-0，0-1
	cout << "bt=" << bt << endl;
	
}
//赋值
void test3() {
	std::bitset<32> bt;
	bt = 11;//取二进制赋入低位1011
	bt.set(bt.size() - 1);
	cout << "bt=" << bt << endl;
	cout << "bt.to_string():"<<bt.to_string() << endl;
	cout << "bt.to_ulong():"<<bt.to_ulong() << endl;
	int res = bt.to_ulong();
	unsigned res2= bt.to_ulong();
	cout << "bt.to_ulong()-int:" << res << endl;
	cout << "bt.to_ulong()-unsigned:" << res2 << endl;

	std::bitset<32> bt2(res);//传带负号的int
	//std::bitset<32> bt2(res2);//传unsigned
	cout << "bt2=" << bt2 << endl;//结果都一样
}

int main() {
	//test1();
	//test2();
	test3();
}