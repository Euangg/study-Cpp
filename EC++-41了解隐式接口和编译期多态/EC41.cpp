
class Widget {
public:
	Widget();
	virtual ~Widget();
	virtual size_t size()const;
	virtual void normalize();
	void swap(Widget& other);
};
void doProcessing(Widget& w) {
	if (w.size() > 10 && w != someNastyWidget) {
		Widget temp(w);
		temp.normalize();
		temp.swap(w);
	}
}
//关于doProcessing内的w，理解：
//·由于w的类型被声明为Widget，所以w必须支持Widget接口。
//我们可以在源码中找出这个接口，看看它是什么样子
//所以我们称此为一个【显式接口】，也就是在源码中可见
//·由于Widget的某些成员函数是virtual，w对那些函数的调用将呈现出【运行期多态】
//也就是说将于运行期根据w的动态类型决定究竟调用哪一个函数

//泛型编程的世界，显式接口和运行期多态仍然存在，但重要性降低。
//但是【隐式接口】和【编译期多态】移到前头了。
template<typename T>
void doProcessing(T& w) {
	if (w.size() > 10 && w != someNastyWidget) {
		T temp(W);
		temp.normalize();
		temp.swap(w);
	}
}
//关于doProcessing内的w，理解：
//·w必须支持哪一种接口，由template中执行于w身上的操作来决定。本例看来，w的类型T
//必须支持size、normalize和swap成员函数、copy构造函数（建立temp）、不等比较
//重要的是，这一组表达式便是T必须支持的一组【隐式接口】。
//·凡涉及w的任何函数调用，例如operator>和operator!=，有可能造成template具现化，
//使这些调用得以成功。这样的具现化行为发生在编译期。
//“以不同的template参数具现化function templates”会导致调用不同的函数，
//这便是所谓的【编译期多态】