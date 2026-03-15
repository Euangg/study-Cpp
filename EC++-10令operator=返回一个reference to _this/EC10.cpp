void main() {
	int x, y, z;
	x = y = z = 15;	//赋值连锁形式
	//赋值采用右结合定律，所以上述操作解释为
	x = (y = (z = 15));

}


//为了实现连锁赋值，赋值操作符必须返回一个指向操作符左侧的实参
class Widget {
public:
	Widget& operator=(const Widget& rhs) { return *this; };
	//这个协议不仅适用于标准赋值形式，也适用于所有赋值相关运算符：
	Widget& operator+=(const Widget& rhs) { return *this; };
	//即使操作数的参数类型与目标类型不一致
	Widget& operator=(int rhs) { return *this; };
};