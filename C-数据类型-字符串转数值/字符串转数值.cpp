#include<iostream>
#include<string>
using namespace std;

int main() {
	string str = "123a45";
	size_t pos;
	int val = stoi(str, &pos, 10);
	cout << "val=" << val << endl;
	cout << "pos=" << pos << endl;
}
