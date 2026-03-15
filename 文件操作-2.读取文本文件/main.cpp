#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//写读文件，按行读取，使用string类型接收内容
void test1() {
	string filePath = R"(D:\test.txt)";
	ofstream fout(filePath);//文件输出流//不存在会创建

	//判断打开文件是否成功
	if (fout.is_open() == false) {
		cout << "打开文件失败" << endl;
		return;
	}

	//向文件中写入数据
	fout << "1|dfgxcx|1\n";
	fout << "2|azcvgg|2\n";
	fout << "3|x66w|4\n";
	fout.close();//关闭文件，fout对象失效前会自动调用close()

	ifstream fin(filePath);//输入流
	//判断打开文件是否成功
	if (fin.is_open() == false) {
		cout << "打开文件" << filePath << "失败" << endl;
		return;
	}

	//读取文件内容
	//文本一般以行的方式组织数据

	//方式1.
	string buffer;//用于存放从文件读取的数据
	cout << "开始读取:" << endl;
	while (getline(fin, buffer)){//按行读取
		cout << buffer << endl;
	}
	cout << "文件操作完成" << endl;
}

//写读文件，按行读取，使用char[]接收内容
void test2() {
	string filePath = R"(D:\test.txt)";
	ofstream fout(filePath);//文件输出流//不存在会创建
	if (fout.is_open() == false) {	//判断打开文件是否成功
		cout << "打开文件失败" << endl;
		return;
	}
	fout << "1|dfgxcx|1\n";
	fout << "2|azcvgg|2\n";
	fout << "3|x66w|4\n";
	fout.close();//关闭文件，fout对象失效前会自动调用close()

	ifstream fin(filePath);//输入流
	if (fin.is_open() == false) {
		cout << "打开文件" << filePath << "失败" << endl;
		return;
	}
	//方式2.
	char buffer[101];//缓冲区不够时，读取会有异常
	while (fin.getline(buffer, 100)){
		cout << buffer << endl;
	}
}

//写读文件，流式读取
void test3() {
	string filePath = R"(D:\test.txt)";
	ofstream fout(filePath);//文件输出流//不存在会创建
	if (fout.is_open() == false) {	//判断打开文件是否成功
		cout << "打开文件失败" << endl;
		return;
	}
	fout << "1|dfgxcx|1\n";
	fout << "2|azcvgg|2\n";
	fout << "3|x66w|4\n";
	fout.close();//关闭文件，fout对象失效前会自动调用close()

	ifstream fin(filePath);//输入流
	if (fin.is_open() == false) {
		cout << "打开文件" << filePath << "失败" << endl;
		return;
	}
	//方式3.
	string buffer;
	while (fin >> buffer){//一行一行读
		cout << buffer << endl;
	}


	fin.close();//关闭文件
}

//写读文件，写入数值文件，穿插制式段落，格式化写读//不可行
void test4() {
	string filePath = R"(D:\test.csv)";
	ofstream fout(filePath);//文件输出流//不存在会创建
	if (fout.is_open() == false) {	//判断打开文件是否成功
		cout << "打开文件失败" << endl;
		return;
	}
	int a = 10, b = 1001;
	fout << a << "," << b << endl;
	fout << b << "," << b << "," << a << endl;
	fout << b << "," << b << "," << a << endl;
	fout << b << "," << b << "," << a << endl;
	fout.close();//关闭文件，fout对象失效前会自动调用close()

	ifstream fin(filePath);//输入流
	if (fin.is_open() == false) {
		cout << "打开文件" << filePath << "失败" << endl;
		return;
	}
	string buffer;
	while (fin >> buffer) {//一行一行读
		cout << buffer << endl;
	}
	fin.close();//关闭文件

	ifstream fin2(filePath);//输入流
	if (fin2.is_open() == false) {
		cout << "打开文件" << filePath << "失败" << endl;
		return;
	}
	int c[20];
	int i = 0;
	while (fin2 >> c[i]){//只读了一行
		i++;
	}
	cout << i << endl;
	for (int o = 0; o < i; o++)cout << c[o] << ",";
	cout << endl;
}

//写读文件，写入自定义数据类型
void test5() {
	string filePath = R"(D:\test.txt)";
	ofstream fout(filePath);//文件输出流//不存在会创建
	if (fout.is_open() == false) {	//判断打开文件是否成功
		cout << "打开文件失败" << endl;
		return;
	}
	struct sPoint{
		int x, y, z;
	};
	sPoint p{ 1,2,3 };
	//fout << p << endl;//不行，运算符不匹配
	fout.close();//关闭文件，fout对象失效前会自动调用close()
}

int main() {
	//test1();
	//test2();
	//test3();
	//test4();

	return 0;
}