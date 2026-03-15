#include<iostream>
#include<sys/stat.h>
using namespace std;

//文件状态
void test1() {
	const char* fileName = "test.txt";
	struct stat buffer;
	int exist = stat(fileName, &buffer);//调用stat函数
	if (exist == 0) {
		cout << fileName << "存在！" << endl;
	}
	else {
		cout << fileName << "不存在！" << endl;
	}
}


//删除文件
//#include<iostream>
//#include<cstdio>
//using namespace std;
//
//int main() {
//	const char* fileName = "data/test.txt";
//	int ok = remove(fileName);
//	if (ok == 0) {
//		cout << fileName << "已删除" << endl;
//	}
//	else {
//		cout << fileName << "不存在" << endl;
//	}
//
//	return 0;
//}

//删除文件夹

int main() {
	const char* fileName = "data";
	int ok = remove(fileName);
	if (ok == 0) {
		cout << fileName << "已删除" << endl;
	}
	else {
		cout << fileName << "不存在" << endl;
	}

	return 0;
}