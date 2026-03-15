#include<iostream>
using namespace std;

template<typename T = long,typename U= int >
void mytest(T t='A',U u='B') {
	cout << "t:" << t << ",u:" << u << endl;
}

int main() {
	mytest('a', 'b');				//<char	,char>
	mytest<int>('a', 'b');			//<int	,char>
	mytest<char>('a', 'b');			//<char	,char>
	mytest<int, char>('a', 'b');	//<int	,char>
	mytest<char, char>('a', 'b');	//<char	,char>
}