#include<random>
#include<iostream>
using namespace std;
//正态分布
void test() {
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<double>dist(1000, 100);//三个参数：类型为double，平均值，标差
	for (int i = 0; i < 100; ++i) {
		cout << dist(gen) << endl;
	}
}

int main() {
	test();
}