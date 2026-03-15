#include<stdio.h>
#include<iostream>
using namespace std;

int main() {
	wchar_t wchar = 0;
	for (wchar = 0; wchar < 2048; wchar++) {
		wprintf(L"%d:\u2261 \n", wchar, wchar);
		
		
		/*printf("%d:", wchar);
		wcout << wchar << endl;*/
	}
}