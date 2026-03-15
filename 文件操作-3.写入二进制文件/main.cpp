//文本文件：存放的是字符串，以行的方式组织数据，每个字节都是有意义的符号

//二进制文件：存放的不一定是字符串，以数据类型组织数据，内容要作为一个整体来考虑，单个字节没有意义
//注：数据类型可以是C++内置的，也可以是数组、结构体

#include<iostream>
#include<fstream>
using namespace std;

int main() {

	ofstream fout;//创建文件输出流文件（写文件的）

	//string filename = "D:\\test.txt";//
	string filename = R"(D:\test.dat)";//原始字面量
	//string filename = "test.txt";
	//char filename[] = "test.txt";//C++与C风格字符串都可以使用
	fout.open(filename,ios::binary);//打开文件，如果文件不存在则创建它；如果文件已存在，则截断其内容

	//ofstream fout(filename);//也可以在定义的时候传参给构造函数，打开文件
	//参数1：文件名
	//参数2：文件打开模式
	//	ios::out	缺省值：会截断文件内容（覆盖）
	//	ios::trunc	截断文件内容（覆盖）
	//	ios::app	不截断文件内容，只在文件末尾追加内容
	//	ios::binary	以二进制方式打开文件//可以或追加

	//判断打开文件是否成功
	if (fout.is_open() == false) {
		cout << "打开文件" << filename << "失败" << endl;
		return 0;
		//失败的原因主要有
		//1.目录不存在
		//2.磁盘空间已满
		//3.没有权限（Linux平台下很常见）
	}

	//向文件中写入数据
	struct st_girl{
		char name[31];	//姓名
		int no;			//编号
		char memo[301];
		double weight;
	}girl;
	girl = { "西施",3,"第一美女",45.8 };
	fout.write((const char*)&girl, sizeof(st_girl));//写入第一块数据
	girl = { "bb",8,"也是美女",55.2 };
	fout.write((const char*)&girl, sizeof(st_girl));//写入第二块数据
	

	fout.close();//关闭文件，fout对象失效前会自动调用close()

	cout << "文件操作完成" << endl;

	return 0;
}

