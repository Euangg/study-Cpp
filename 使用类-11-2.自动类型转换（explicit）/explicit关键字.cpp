//在实际开发中，单参构造函数有 构造功能 和 类型转换功能（本质也还是构造，只不过更隐蔽）
//如果功能强调构造，建议加上explicit关键字——关闭自动转换特性，只能显式调用不会隐式调用
//如果功能强调转换，则不用explict关键字

class Basket {
	int weight_;
public:
	Basket() {};
	explicit Basket(int a) { weight_ = a; };//指明为构造函数，弱化转换功能
	//Basket(int a) { weight_ = a; };		重定义，explicit约束不算重载
};

Basket get(Basket basket) { 
	//return 999; 不再允许——返回
	return basket;
}

int main() {
	//Basket b1 = 999; 不再生效
	Basket b2(9999);
	//b2 = 9978789798; 不再生效
	b2 = (Basket)99999;//显式转换
	b2 = Basket(99999);//显式转换

	//get(8881231231); 不再允许——传参
}

