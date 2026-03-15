
//令函数返回一个const值，防止客户错误造成意外
class Rational {};
const Rational operator*(const Rational& lhs, const Rational& rhs) {};
//暴行：
Rational a, b, c;
//(a * b) = c;//在a*b的成果上调用operator=


//const成员函数
//1.使class接口容易理解
//2.使“操作const对象”成为可能
//C++鲜为人知的重要特性：函数常量性不同，也可以重载
#include<iostream>
class TextBlock {
	std::string text;
public:
	const char& operator[](size_t position)const { return text[position]; };
	char& operator[](size_t position) { return text[position]; };
};
void Test() {
	TextBlock tb;
	std::cout << tb[0];
	const TextBlock ctb;
	std::cout << ctb[0];
}


//bitwise constness
class CTextBlock {
	char* pText;
public:
	char& operator[](size_t position)const { return pText[position]; };
};
void Test2() {
	const CTextBlock cctb;
	char* pc = &cctb[0];
	*pc = 'J';//还是修改了内容
}
