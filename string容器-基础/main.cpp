//string是字符容器，内部维护了一个动态的字符数组
//与普通字符数组相比，string容器有三个优点：
//	(1).使用的时候不需要考虑内存的分配和释放问题
//	(2).动态管理内存（可扩展）
//	(3).提供了大量操作容器的API
//缺点是效率略有降低（占用的资源也更多）
//string类是std::basic_string类模板的一个具体化版本的别名，定义如下：
//	using std::string=std::basic_string<char,std::char_traits<char>,std::allocator<char>>

//静态常量成员string::npos为字符数组的最大长度(通常为unsigned int或unsigned long long的最大值)
//NBTS(null-terminated string) ： C风格字符串（以空字符0结束的字符串）
//string类有七个构造函数（C++11新增了两个）


#include<iostream>
using namespace std;

int main() {
	cout << "npos=" << string::npos << endl;

	//1).string()：创建一个长度为0的string对象（默认构造函数）

	//2).string(const char* s)：将string对象初始化为s指向的NBTS（转换函数）

	//3).string(const string& str)：将string对象初始化为str（拷贝构造函数）

	//4).string(const char* s,size_t n)：将string对象初始化为s指向的NBTS的前n个字符，即使超过了NBTS结尾
	// 将string对象初始化为s指向的后n个字节的内容
	//主要用于存放其他类型的数据

	//5).string(const string& str,size_t pos=0,size_t n=npos)：

	//6).template<class T>string(T begin,T end)：将string对象初始化为区间[begin,end]内的字符
	//		其中begin和end的行为就像指针，用于指定位置，范围包括begin在内，不包括end

	//7).string(size_t n,char c)：创建一个由n个字符c组成的string对象
}