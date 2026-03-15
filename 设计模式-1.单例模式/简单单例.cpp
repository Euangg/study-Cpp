//单例模式保证某个类最多只能有一个对象实例
class cSingleton {
public:
	static cSingleton& GetSingleton() {
		static cSingleton singleton;
		return singleton;
	}
	cSingleton(cSingleton const&) = delete;//删除拷贝构造函数
	void operator=(cSingleton const&) = delete;//删除赋值运算符
private:
	cSingleton() {};//构造函数私有化，不能进行外部构造
	~cSingleton() {};
};