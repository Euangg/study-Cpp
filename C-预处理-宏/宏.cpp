#include<iostream>

//转字符串(将x替换成"x")，#给参数加""
#define STR(x)#x


//#define CONTACT2(x,y)CONTACT(x,y)
//拼接
		
#define STR2(x)STR(x)
#define build_id_str(x) level_##x
int main() {
	const char* level_id = STR2(build_id_str(9));
	const char* level_id2 = STR(build_id_str(9));
}

//1.参数优先展开:
//在替换类函数宏时，首先完全展开所有参数，再将展开后的结果代入宏体。例外情况是当参数出现在#(字符串化)或##(连接符)操作符前后时，该参数不会被展开。
//2.由内向外递归展开:
//嵌套宏的展开顺序从最内层开始，逐层向外处理。例如MACRO1(MACRO2(x))会先展开MACRO2(x)，再将结果代入MACRO1展开。
//3.单次扫描原则:
//预处理器对每个宏调用进行单次展开：
//先展开宏参数(除非遇到# / ##)
//替换参数到宏体
//扫描结果是否包含新宏，若存在则继续展开
//整个过程类似广度优先搜索，每次扫描处理当前可见的宏定义。
//4.特殊操作符规则:
//#将参数转为字符串字面量，阻止参数宏展开
//示例：STR(__LINE__)会保持为"LINE"字符串
//##连接两个标记为新标识符，若连接的标记是宏则阻止展开
//示例：level_##x若x是宏参数，直接拼接不展开
//5.展开深度限制:
//C标准未规定具体展开层数，但主流编译器通常支持至少15层嵌套展开。当检测到无限递归展开时，编译器会报错终止预处理


int gridBack[66];
void LoadGridData(char* path, int& grid) {}
#define PathName(n) res/data/map##n##/XYZ-##n##_back.csv
#define LoadData(x) LoadGridData(STR2(PathName(x)), gridBack[x]);
void test() {
	//LoadGridData(L"res/data/map01/XYZ-01_back.csv", gridBack[0]);
	LoadData(01);
}