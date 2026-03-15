#include<iostream>
#include<Windows.h>
using namespace std;

int main() {
	LPCWSTR lpcwstr1 = L"hsadfkjhs";
	cout << lpcwstr1 << endl;
	wprintf(L"%ls\n", lpcwstr1);

	//LPWSTR lpwstr1 = (LPWSTR)L"SUU";//强转转地址，地址内容还是不能动
	wchar_t szWchar_t[20] = { 0 };
	szWchar_t[0] = 'a';
	LPWSTR lpwstr1 = szWchar_t;

	wcscat(lpwstr1, lpcwstr1);
	wprintf(L"%ls\n", lpwstr1);


	WCHAR wchar1 = 'a';

	return 0;
}