#include<iostream>
using namespace std;

//递归函数——函数在运行时调用自己
int times = 0;

int func(int x) {
	times++;
	cout << "第" << times << "次" << "递归" << endl;
	if (x == 0)return 0;//停止自调条件————无限递归会造成栈溢出(运行过程中操作系统报错)
	return x + func(x - 1);
}

//1.自调
//2.终止条件判断

//往返运行：第一次走到递归深处，第二次往回执行运算。嵌套调用函数，进入函数的过程是递去，函数逐级返回的过程是归来
//过程中不能出错
//	保证运行收敛（结果、条件可预见）

//意义
//1.替代循环遍历（代码更简洁）


int main() {
	
	cout << func(100) << endl;
	cout << "共递归" << times << "次" << endl;


	int sum = 0;
	for (int i = 0; i <= 100; i++) {
		sum += i;
	}

	cout << sum << endl;
}
