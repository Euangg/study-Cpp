#include<iostream>
#include<chrono>
using namespace std;

int main() {
	chrono::hours t1(1);					//1–° ±
	chrono::minutes t2(60);					//60∑÷÷”
	chrono::seconds t3(60 * 60);			//60*60√Î
	if (t1 == t2)cout << "t1==t2" << endl;
	if (t1 == t3)cout << "t1==t3" << endl;

	chrono::seconds t4(1);
	chrono::milliseconds t5(1000);			//1000∫¡√Î
	chrono::microseconds t6(1000 * 1000);	//1000*1000Œ¢√Î
	chrono::nanoseconds t7(1000 * 1000 * 1000);//1000*1000*1000ƒ…√Î
	if (t4 == t5)cout << "t4==t5" << endl;
	if (t4 == t6)cout << "t4==t6" << endl;
	if (t4 == t7)cout << "t4==t7" << endl;
	
	cout << "t4=" << t4.count() << endl;
	cout << "t5=" << t5.count() << endl;
	cout << "t6=" << t6.count() << endl;
	cout << "t7=" << t7.count() << endl;
}