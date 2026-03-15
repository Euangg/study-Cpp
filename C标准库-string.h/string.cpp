#include<string.h>
#include<stdio.h>

//strstr的效果
void test1() {
	printf("hello world\n");

	const char haystack[20] = "HELLO WORLD";
	const char needle[10] = "LLO";
	const char* ret;

	ret = strstr(haystack, needle);
	printf("ret:%s\n", ret);
}
//strstr的返回
void test2() {
	const char* pchCmdLine = "Hello World";
	const char* pchConnectParam = "Wor";
	const char* pchConnect = strstr(pchCmdLine, pchConnectParam);
	printf("pchConnect:%s\n", pchConnect);
	printf("&pchConnect:%d\n", pchConnect);
	printf("&pchCmdLine:%d\n", pchCmdLine);

	pchConnect - pchCmdLine;
}

int main() {
	//test1();
	test2();
	return 0;
}