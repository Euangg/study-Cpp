//C++98引入异常规范
//C++11已弃用

//实际使用效果并不好，最好不要使用这项功能
//为了阅读以前的代码


#include<iostream>
using namespace std;

int main() {
	try {
		//可能抛出异常的代码
		int ii = 0;
		cout << "1?2?" << endl;
		cin >> ii;
		if (ii == 1)throw "1!";//跳转catch
		if (ii == 2)throw ii;
		if (ii == 3)throw string("sad");//如果捕获到异常不处理，程序会崩溃  

		cout << "2" << endl;
	}
	//catch (...) {//不管什么异常，都在此处处理//不关心异常的类型用catch(...)， 也可以根据throw抛出的数据判断异常
	//	cout << "发现异常" << endl;//处理完后离开try，直接执行后面的内容
	//}
	catch (int ii) {
		cout << "异常类型是int=" << ii << endl;
	}
	catch (const char* ss) {
		cout << "异常类型是const char*=" << ss << endl;
	}
	catch (string str) {
		cout << "异常类型是string=" << str << endl;
	}
}

//throw抛出异常，操作数可以是任意的表达式
//try捕获异常，保护代码
//catch根据捕获的异常执行处理  ...表示处理任何抛出的异常