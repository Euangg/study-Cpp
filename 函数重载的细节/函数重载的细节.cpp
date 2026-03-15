//const约束不算重载
//返回值类型不同不算重载

//参数加&约束算重载
//缺省参数算重载，一旦出现二义会报错

void func(int a, int b) {};
void func(int a, int b, int c = 10) {};

//void func(const int a, int b) {};  重定义报错

//int func(int a, int b) { return 0; };  无法区分 按返回值类型重载 的函数

int main() {
	//func(2,3); 二义报错
}

//C++编译器的名称修饰：编译器会对每个函数进行加密，替换函数名，每个函数都会被替换，重载函数不算同一个函数，被分别替换
//所以，经编译器替换后，在程序员眼里同名的重载函数在编译器眼里并不同名