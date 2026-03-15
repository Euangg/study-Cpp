//宁可以编译器替换预处理器
//常量定义式通常放在头文件

//关于#define常量

//class专属常量，将常量的作用域限制于class内
//不用define，因为define不重视作用域
//为确保常量至多只有一份实体，必须让它成为一个static成员
class GamePlayer {
private:
	static const int NumTurns = 5;	//常量声明式（不算定义！！！）
	//class专属常量、static、且为整数类型（int char bool）。只要不取地址，就不需要定义式

	int scores[NumTurns];			//使用常量
};
const int GamePlayer::NumTurns;		//定义式

//方法2
//the enum hack式
class GamePlayer2 {
private:
	enum { NumTurns = 5 };

	int scores[NumTurns];
};


//关于#define宏
//template inline函数
//获得宏带来的效率以及一般函数的可预料行为和类型安全性
template<typename T>
inline void callWithMax(const T& a, const T& b) {
	func(a > b ? a : b);
}
//对于形似函数的宏（macros），最好改用inline函数替换#define

