#include<iostream>
using namespace std;

struct sGirl_C {

	string name;

	int age;
	int height;

	float weight;

protected://14.结构体也可以使用protected访问权限，但是如果放的很靠前(任何成员变量前)，会导致隐藏的默认构造函数失效
	/*sGirl_C() {
		name = "系式";
		age = 16;
		height = 170;
		weight = 50.5;
	};*/

	/*sGirl_C(int a) {
		name = "系式";
		age = 16;
		height = 170;
		weight = 50.5;
	};*/
	//9.添加任意构造函数，结构体变量都不能使用统一初始化列表进行初始化
public:
	void show() {
		cout << "name:" << name << endl;
		cout << "age:" << age << endl;
		cout << "height:" << height << endl;
		cout << "weight:" << weight << endl;
	}
	
};

struct sGirl{
//private:
	string name;
	int age;
	int height;
	float weight;
public://5.c++结构体成员也可以设置访问权限！
	sGirl() {
		name = "系式";
		age = 16;
		height = 170;
		weight = 50.5;
	};
	//2.c++结构体也可以有构造函数！

	void show() {
		cout << "name:" << this->name << endl;//4.而且也有this指针
		cout << "age:" << age << endl;
		cout << "height:" << height << endl;
		cout << "weight:" << weight << endl;
	}
	//4.c++结构体也可以有成员函数！
};
//6.那么关于结构体和类的区别：
//	结构体的成员和成员函数在默认情况下的访问级别是公有的（public），类的成员和成员函数在默认情况下的访问级别是私有的（private）
//7.这样的访问级别效果同样体现在继承！结构体也可以继承


class cGirl {
private:
	string name;
	int age;
	int height;
	float weight;
public:
	cGirl() {
		name = "系式";
		age = 16;
		height = 170;
		weight = 50.5;
	};
	cGirl(string pname,int page,int pheight,float pweight) {
		name = pname;
		age = page;
		height = pheight;
		weight = pweight;
	};
	//12.类手工添加统一初始化列表构造函数后，也能像结构体一样统一初始化
	void show() {
		cout << "name:" << name << endl;
		cout << "age:" << age << endl;
		cout << "height:" << height << endl;
		cout << "weight:" << weight << endl;
	}
};


int main() {
	sGirl girl;


	//girl.name = "系式";
	//girl.age = 16;
	//girl.height = 170;
	//girl.weight = 50.5;
	//1.一般结构体类型变量创建后，其中的成员要一个一个的赋初值


	/*cout << "name:" << girl.name << endl;
	cout << "age:" << girl.age << endl;
	cout << "height:" << girl.height << endl;
	cout << "weight:" << girl.weight << endl;*/
	//3.一般结构体的操作是面向过程的，像这样的一大段操作如果封装成函数，考虑到代码放的位置和分类，不便于管理
	
	girl.show();


	sGirl_C girl3 = { "貂蝉",17,175,53.5f };
	girl3.show();
	//8.当结构体中没有添加构造函数时，创建结构体变量可以使用统一初始化列表
	//	添加无参构造函数后，不能使用这种初始化

	girl3 = { "杨幂",18,173,54.5f };
	girl3.show();
	//10.统一初始化列表还可以随时进行赋值操作
	//11.根据上述，程序员手工添加构造函数后，原有的构造函数被覆盖，原有的构造函数的参数就是成员参数列表，即统一初始化列表

	cGirl girl2 = { "迪丽热巴",19,179,55.5f };
	girl2.show();
	girl2 = { "王昭君",20,171,51.5f };
	girl2.show();
	//13.类手工添加统一初始化列表构造函数后，不但可以像结构体一样统一初始化，还可以像结构体一样随时进行初始化列表赋值操作
}

//15.在面向对象基本的封装层面，结构体和类主要有两点区别：
//		1.默认成员访问权限不一样（在可添加访问限定符的地方如成员区和继承不明确声明访问权限的话，结构体默认为public，类默认为private）
//		2.默认构造函数不一样，结构体为统一初始化列表，类为无参构造

//OOP（面向对象编程）的四大特性：封装、继承、多态、抽象
//封装：把琐碎的代码打包起来，为编写者提供管理方便，为调用者提供查阅方便
//C语言只能把代码打包到函数中，C++还可以打包到结构体和类中