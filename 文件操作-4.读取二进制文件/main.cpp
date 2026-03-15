//二进制文件的格式多样，由业务需求决定
//程序员自定义的二进制文件格式，只有程序员自己知道。除了程序员自己，没人知道他会设计出什么样的二进制数据结构


//为了兼容，有很多通用的数据结构被设计出来：mp3（音乐）、mp4（视频）、bmp（位图）、jpg、png



//文本文件VS二进制文件

//文本文件：由可显示的字符组成，方便阅读（解码），占用的空间较多

//二进制文件：由比特0和1组成，组织数据的格式与文件用途有关，不方便阅读（解码）。
//为了节省存储空间，还可能采用压缩技术。
//为了保证数据安全，也可能采用加密技术。



#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main() {
	//文件名一般用全路径，书写方法如下：
	//1）"D:\test.txt"		//目标路径，不能直接用，会错误
	//2）R"(D;\test.txt)"	//原始字面量，C++11标准
	//3）"D:\\test.txt"		//转义字符
	//4）"D:/test.txt"		//“\”写为“/”
	
	string filename = R"(D:\test.dat)";/* R"(D:\test.dat)"*/


	//创建文件输入流对象
	//open成员函数打开文件
	//参数2——打开方式：
	//	ios::in		//缺省值
	//	ios::binary	//以二进制方式打开
	ifstream fin;
	fin.open(filename, ios::in | ios::binary);


	//判断打开文件是否成功
	//成员函数：is_open
	if (fin.is_open() == false) {
		cout << "打开文件" << filename << "失败" << endl;
	}

	//读取内容 
	//二进制文件，读取时要知道并根根据数据类型进行读取
	struct st_girl {
		char name[31];	//姓名
		int no;			//编号
		char memo[301];
		double weight;
	}girl;

	while (fin.read((char*)&girl, sizeof(girl))) {
		cout << "name=" << girl.name << ",no=" << girl.no << ",memo=" << girl.memo << ",weight=" << girl.weight << endl;
	}

	//read成员函数读取数据，一次读取一个块，块的大小由第二个参数决定



	


	//关闭文件
	fin.close();

	cout << "操作完成" << endl;
}
