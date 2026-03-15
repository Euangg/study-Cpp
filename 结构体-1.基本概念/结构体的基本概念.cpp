#include<iostream>
using namespace std;

//#pragma pack(1)//22.设置内存对齐，默认为8

struct sPeople {
	int height_ = 160;
	char name_[25] = "mario";
	int age_ = 36;//3.结构体成员可以指定缺省值（C++11标准）
};

struct sPeople2 {
	int height_;
	char name_[25];
	int age_;
};

struct sPeople3 {
	int height_=90;
	char name_[25] = "3类people";
	int age_=9;
	int hp_;
};

int main() {
	struct sPeople people;//1.定义结构体变量的完整方式：struct 结构体名 变量名; //在C++中，前面的struct关键字可以省略
	//2.结构体名是一种标识符，遵守标识符规矩
	cout << "身高：" << people.height_ << "\t姓名：" << people.name_ << "\t年龄：" << people.age_ << endl;

	struct sPeople2 people4 = {};//9.成员完全没设缺省值的结构体创建时不指定初值的情况下使用该变量，编译器报错
	cout << "身高：" << people4.height_ << "\t姓名：" << people4.name_ << "\t年龄：" << people4.age_ << endl;//10.教程说的在不设缺省值的结构体起效
	//11.故总结：完全无缺省值结构体赋初值优先级：构造函数>{}>缺省值

	struct sPeople3 people5;//12.成员部分没设缺省值的结构体创建时不指定初值的情况下使用该变量，编译器不报错，能用，没有缺省值的是随机值
	cout << "身高：" << people5.height_ << "\t姓名：" << people5.name_ << "\t年龄：" << people5.age_ <<  "\t血量：" <<people5.hp_ <<endl;

	//21.结构体大小，用sizeof运算为其成员分别内存对齐后占用的内存大小
}