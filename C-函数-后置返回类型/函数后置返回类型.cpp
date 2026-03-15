
int func(int x, double y) {};
//等同
auto func(int x, double y)->int {};//将函数的返回类型移到了函数声明的后面
