#include<iostream>
using std::cout;
using std::endl;
#include<numeric>
#include<vector>

//累加
void test1() {
	std::vector<int>v{1, 2, 3, 4, 5};
	int res = std::accumulate(v.begin(), v.end(), 0);//第三个参数，累加的初值
	cout << res<<endl;
}


int main() {
	test1();
}