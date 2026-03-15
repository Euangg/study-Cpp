#include <iostream>
#include<Windows.h>
#include<atlconv.h>
#include<atlstr.h>
using namespace std;

/*窄字节到宽字节*/
wchar_t* a2w(char* p_a) {
    int need_w_char = MultiByteToWideChar(CP_ACP, 0, p_a, -1, NULL, 0);
    if (need_w_char <= 0)
    {
        return NULL;
    }

    wchar_t* p_w = new wchar_t[need_w_char];
    wmemset(p_w, 0, need_w_char);

    MultiByteToWideChar(CP_ACP, 0, p_a, -1, p_w, need_w_char);
    return p_w;
}
void test01() {
    char p_a[] = "asdfasdf";
    cout << "cout:" << p_a << endl;
    printf("printf:%s\n", p_a);
    wchar_t* p_a_2w = a2w(p_a);
    cout << "cout:" << p_a_2w << endl;//输出的是地址
    cout << "cout-*:" << *p_a_2w << endl;//解出来的是第一个字符的十进制字符编码
    printf("printf-s:%s\n", p_a_2w);//输出的是第一个字符
    printf("printf-ls:%ls\n", p_a_2w);//输出的是完整字符串

    delete[] p_a_2w;
}

/*宽字节到窄字节*/
char* w2a(wchar_t* p_w) {
    int need_a_char = WideCharToMultiByte(CP_ACP, 0, p_w, -1, NULL, 0, NULL, NULL);
    if (need_a_char <= 0) {
        return NULL;
    }

    char* p_a = new char[need_a_char];
    memset(p_a, 0, need_a_char);
    WideCharToMultiByte(CP_ACP, 0, p_w, -1, p_a, need_a_char, NULL, NULL);
    return p_a;
}
void test02() {
    wchar_t p_w[] = L"asdfasdf中国";
    cout << "cout:" << p_w << endl;//输出的是地址
    cout << "cout*:" << *p_w << endl;//解出来的是第一个字符的十进制字符编码
    char* p_w_2a = w2a(p_w);
    cout << "cout:" << p_w_2a << endl;
    delete[] p_w_2a;

}

/*windows宏，字符类型转换*/
void test03() {
    char p_a[] = "2022222";
    CA2W a2wObj(p_a);
    wchar_t* p_a2w = (wchar_t*)a2wObj;
    cout << p_a2w << endl;
    printf("%ls\n", p_a2w);

    wchar_t p_w[] = L"okokokokokokoko";
    CW2A w2aObj(p_w);
    char* p_w2a = (char*)w2aObj;
    cout << p_w2a << endl;
}

void test04() {
    CString str(_T("asdfghjkl"));
    cout << str << endl;//输出的是地址
    printf("%ls\n", str);//输出的是完整字符串
    str += _T("zxcvbnm,          ");
    printf("%ls\n", str);//输出的是完整字符串
    str.Trim();//去掉首尾的不可见字符（如空格、回车）
    printf("%ls\n", str);//输出的是完整字符串
    str.MakeReverse();//翻转
    printf("%ls\n", str);//输出的是完整字符串

}

void test05() {
    CString str2(_T("cabbageabccc"));
    CString str_include = str2.SpanIncluding(_T("abc"));//拿源字符串中的字符逐个对照参数字符串中的字符，有就保留，一旦源字符串中有一个匹配不上就停止
    printf("%ls\n", str_include);//输出的是完整字符串


    CString str(_T("piccc.bmp"));
    CString str_exclude = str.SpanExcluding(_T("."));//效果：去除文件后缀名；匹配上的字符后面全部去除，一次为止
    printf("%ls\n", str_exclude);//输出的是完整字符串
}

void test06() {
    CString str;
    str.Format(_T("qwertyuiop   %d"), 1234);
    printf("%ls\n", str);//输出的是完整字符串
    str.Replace('q', 'r');
    printf("%ls\n", str);//输出的是完整字符串
    str.Replace('rw', 'xx');//替换字符串要注意类型
    printf("%ls\n", str);//输出的是完整字符串  
    str.Replace(_T('wer'), _T('sc'));//替换字符串要等长度？？
    printf("%ls\n", str);//输出的是完整字符串
    //str.Remove(L"rw");不能直接Remove字符串常量
}

/*目标，C-V，改写内容，V-C*/
void test07() {

}

int main() {
    //test01();
    //test02();
    //test03();
    //test04();
    //test05();
    //test06();
}