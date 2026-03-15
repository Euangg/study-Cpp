#include<iostream>
#include<initializer_list>

double sum(std::initializer_list<double> i) {
	double total = 0;
	for (auto& e : i)total += e;
	return total;
}

void Test1() {
	double total = sum({ 15,25,2.33,6.9,8.8 });
	std::cout << total << std::endl;
}

int main() {
	Test1();
}