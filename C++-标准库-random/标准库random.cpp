#include<random>
#include<iostream>
using std::cout;
using std::endl;

//投骰子
void test1() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<>dist(1, 6);
	for (int i = 0; i < 50; ++i) {
		cout << dist(gen) << endl;
	}
}
//浮点数
void test2() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<>dist(0, 1);
	for (int i = 0; i < 50; ++i) {
		cout << dist(gen) << endl;
	}
}

//伯努利分布
void test3() {
	std::random_device random_device;
	std::mt19937 mt19937(random_device());
	std::bernoulli_distribution dist(1);//超过[0,1]运行时报错
	for (int i = 0; i < 500; ++i)cout << dist(mt19937) << endl;
}

//二项分布
void test5() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::binomial_distribution<int>dist(1,1);
	for (int i = 0; i < 50; ++i) {
		cout << dist(gen) << endl;
	}

}
//适配器
void test6() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::discard_block_engine<std::mt19937, 3, 2>discard_engine(gen);
	for (int i = 0; i < 50; ++i) {
		cout << discard_engine() << endl;
	}
}

int main() {
	test3();
}