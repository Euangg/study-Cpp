#include<iostream>
using namespace std;

void 金字塔数列() {
	for (int i = 1; i < 101; i++) {
		cout << i << ":\t" << 1 + (1 + i) * i / 2 << endl;
	}
}

int main() {
	金字塔数列();
}