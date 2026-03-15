//C风格的类型转换
//语法：
//(目标类型)表达式
//目标类型(表达式)
//C++认为C风格的类型转换过于松散，可能会带来隐患，不够安全
//C++推出了新的类型转换来替代C风格的类型转换，采用更严格的语法检查，降低使用风险
//C++新增了四个关键字：static_cast    const_cast    reinterpret_cast    dynamic_cast      用于支持C++风格的类型转换
// 1.static_cast：用的最多 1.用于内置数据类型之间的转换  2.用于指针之间的转换
//   static_cast<目标类型>(表达式)
// 
// 2.const_cast： 
//   const_cast<目标类型>(表达式)
// 
//		static_cast不能丢掉指针的const和volitale属性，const_cast可以
// 
// 3.reinterpret_cast：关键字的意思是重新解释，能够将一种对象类型转换为另一种，不管它们是否有关系——想怎么转就怎么转
//   reinterpret_cast<目标类型>(表达式)
//	 注：要求目标类型和表达式中必须有一个是指针类型——因为它只为转换指针的应用场景而设计
//			static_cast不能用于转换不同类型的指针（引用）（不考虑有继承关系的情况），reinterpret_cast可以
//	 应用场景：
//		(1).改变指针(引用)类型
//		(2).将指针(引用)转换成整型变量。整型变量与指针占用的内存字节数必须一致，否则转换可能损失精度
//		(3).将整型变量转换成指针（引用）。
// 
// 4.dynamic_cast：用于多态
//   dynamic_cast<目标类型>(表达式)
// 
// 
// 
// 
//C++的类型转换只是语法上的解释，本质上与C风格的类型转换没什么不同，C语言做不到的事C++也做不到

//static_cast   1.
//#include<iostream>
//using namespace std;
//
//int main(int argc, char* argv[]) {
//	int ii = 3;
//	long ll = ii;	//绝对安全，可以隐式转换，不会出现警告
//
//	double dd = 1.23;
//	long ll1 = dd;	//可以隐式转换，但是会出现可能丢失数据的警告
//
//	long ll2 = (long)dd;	//C风格：显式转换，不会出现警告
//	long ll3 = static_cast<long>(dd);	//C++风格：显式转换，不会出现警告
//
//	cout << "dd=" << dd << endl;
//	cout << "ll1=" << ll1 << endl;
//	cout << "ll2=" << ll2 << endl;
//	cout << "ll3=" << ll3 << endl;
//}


//static_cast   2.
//#include<iostream>
//using namespace std;
//
//void func(void* ptr) {//其它类型指针1->void*指针->其它类型指针2
//	//如果调用的函数需要转换指针，可以把它的形参设计为void*类型
//
//	double* pp = static_cast<double*>(ptr);
//
//}
//
//int main(int argc, char* argv[]) {
//	int ii = 10;
//	//double* pd1 = &ii;		//错误，不能隐式类型转换
//	double* pd2 = (double*)&ii;//C风格，强制类型转换，不过存储方式不同，指针转换不做任何修改或新建操作，所以读取该指针的值不是10.0
//	//double* pd3 = static_cast<double*>(&ii);//C++风格，但是错误，static_cast不支持该类型的指针转换
//	
//	void* pv = &ii;	//任何类型的指针都可以隐式转换成void*
//	double* pd4 = static_cast<double*>(pv);//static_cast可以把void*转换成其他类型的指针
//
//	cout << "ii=" << ii << endl;
//	cout << "*pd2=" << *pd2 << endl;
//	cout << "*pd4=" << *pd4 << endl;
//
//	//调用函数时，当指针用于传递参数，如果调用的函数需要
//	//	如果调用的函数需要转换指针，可以把它的形参设计为void*类型
//	func(&ii);
//}


//reinterpret_cast  
//#include<iostream>
//using namespace std;
//
//void func(void* ptr) {
//	int ii = reinterpret_cast<int>(ptr);//reinterpret_cast可以把指针直接转化成整型
//	cout << "ii=" << ii << endl;
//}
//
//int main() {
//	int ii = 3;
//	//double d1 = reinterpret_cast<double>(ii);//错误，reinterpret_cast不是为这种场景设计的
//	double* pd1 = reinterpret_cast<double*>(&ii);
//	cout << *pd1 << endl;
//
//	func(reinterpret_cast<void*>(ii));//reinterpret_cast可以把整型直接转化成指针
//}


//const_cast
//#include<iostream>
//using namespace std;
//
//void func(int* ii) {
//
//}
//
//int main() {
//	const int ii = 3;
//	int bb = ii;
//
//	const int* pii = &ii;
//	//int* pbb = pii;//报错，对于指针const不能隐式丢掉
//	int* pbb2 = (int*)pii;//C风格强制转换，丢掉const限定符
//	int* pbb3 = const_cast<int*>(pii);//C++风格，丢掉const限定符
//	cout << *pbb2 << endl;
//	cout << *pbb3 << endl;
//	*pbb2 = 1111;
//	cout << *pii << endl;
//	cout << *pbb2 << endl;
//	cout << *pbb3 << endl;
//
//	//func(pii);//报错
//	func(const_cast<int*>(pii));
//
//}




//实验，子类向父类的转换
#include<iostream>
using namespace std;
class Point {
public:
	int x;
	int y;
	float flag;
public:
	void show() {
		cout << x << '\t' << y << '\t' << flag << endl;
	}
};

class Rect :public Point{
public:
	int width;
	int height;
public:
	void show() {
		cout << x << '\t' << y << '\t' << flag << '\t' << width  << '\t' << height  << endl;
	}
	Point GeneratePoint() { return (Point)*this; }//强转符合逻辑
};

//小于0的转换
void Test() {
	double x = -0.231;
	int ix = static_cast<int>(x);
	cout << ix << endl;
}

int main(int argc, char* argv[]) {
	Rect rect;
	rect.x = 9999;
	rect.y = 8888;
	rect.flag = 55.555;
	rect.width = 1111;
	rect.height = 2222;
	rect.show();

	rect.GeneratePoint().show();

	cout << "测试：" << endl;
	Test();
}