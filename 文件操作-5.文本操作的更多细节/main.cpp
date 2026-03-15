//在Windows平台下，文本文件的换行标志是"\r\n"
//而在Linux平台下，文本文件的换行标志是"\n"

#include<iostream>
#include<fstream>
using namespace std;

int main() {
	//ofstream fout("D:/test2.txt");//打开文件
	ofstream fout("D:/test2.txt",ios::binary);//二进制方式
	
	//fout << "abcde";				//不写入换行，文件大小5byte
	fout << "abcde" << endl;		//写入换行，文件大小7byte，windows系统下换行是两个byte的空间，对应两个转义字符“\r\n”
	//在Windows平台下，以文本方式打开文件，写入数据的时候系统会将"\n"替换成"\r\n"，在读取数据的时候，系统会将"\r\n"转换成"\n"。————微软自立标准
	//如果以二进制方式打开文件，写和读都不会进行转换

	fout.close();


	//文本方式打开文件读取内容，读到换行符停止
	//二进制方式打开文本读取内容，可以根据需求完全读取
}
