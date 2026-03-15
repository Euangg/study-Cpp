#include<stdio.h>


//基本使用
void test() {
	for (int a = 0; a < 0; a++) {
		printf("a=%d\n", a);
	}
	printf("循环结束\n");
}//执行顺序：for(1;2;4)3

int main(){
	test();
}