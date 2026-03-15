//C++中，文件操作属于技术应用，不是基本语法

//数据持久化的两种方式：文件和数据库

//文件操作属于io
//cin是istream类实例化的全局对象
//cout是ostream类实例化的全局对象
//istream和ostream是ios类派生出的类，而ios类是ios_base派生出的类
//istream类派生出ifstream，用于读文件
//ostream类派生出ofstream，用于写文件

//istream和ostream合并派生出iostream类
//iostream类派生出fstream类

#include<iostream>
#include<fstream>
using namespace std;

int main() {
	ofstream fout;//创建文件输出流文件（写文件的那个）

	//string filename = "D:\\test.txt";//
	string filename = R"(D:\test.txt)";//原始字面量
	//string filename = "test.txt";
	//char filename[] = "test.txt";//C++与C风格字符串都可以使用
	fout.open(filename);//打开文件，如果文件不存在则创建它；如果文件已存在，则截断其内容

	//ofstream fout(filename);//也可以在定义的时候传参给构造函数，打开文件
	//参数1：文件名
	//参数2：文件打开模式
	//	ios::out	缺省值：会截断文件内容（覆盖）
	//	ios::trunc	截断文件内容（覆盖）
	//	ios::app	不截断文件内容，只在文件末尾追加内容

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
	fout << "西施|19|极漂亮\n";
	fout << "冰冰|22|漂亮\n";
	fout << "幂幂|25|一般\n";

	fout.close();//关闭文件，fout对象失效前会自动调用close()

	cout << "文件操作完成" << endl;

	return 0;
}
