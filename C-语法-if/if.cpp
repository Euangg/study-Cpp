#include<iostream>
using namespace std;

int main() {
	bool b = true;

	//if (b)cout << "true" << endl; cout << "if之后" << endl;//往后识别一个分号

	if (b)
		cout << "true" << endl; cout << "if之后" << endl;//往后识别一个分号


	//if (b)cout << "true" << endl; //cout << "后置" << endl;//多分号就不行，哪怕在同一行
	//else cout << "false" << endl; cout << "else之后" << endl;//不加括号往后识别一个分号
}