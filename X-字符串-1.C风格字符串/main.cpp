#include<iostream>
using namespace std;

int main() {
	wchar_t ws1[10] = L"asdf";
	wchar_t ws2[8] = L"asdf";
	
	wprintf(L"ws1:%s\n", ws1);
	wprintf(L"ws2:%s\n", ws2);

	//字符串比较
	//wcscmp
	// 不比较字符串开辟的内存空间的大小（ws1[10]、ws2[8]，只要存的字符串一样，就是相等的）
	// 大小：从首字符开始依次往后比较Unicode码值：相等记0，字符串1大记1，字符串2大记-1，一旦出现不为0的比较立刻退出并返回
	//参数：需要比较的C风格字符串（null结尾）
	//返回值：	<0：1：字符串1更大
	//			=0：字符串相等
	//			>0：-1：字符串2更大
	cout << "wcscmp(ws1, ws2)=" << wcscmp(ws1, ws2) << endl;


}

