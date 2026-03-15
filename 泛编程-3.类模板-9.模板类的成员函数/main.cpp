//——在模板类中创建模板类和函数模板
//在实际开发中，类模板中有类模板和函数模板的情况很常见


#include<iostream>
using namespace std;

template<class T1,class T2>
class AA {
public:
	T1 m_x;
	T2 m_y;

	AA(const T1 x, const T2 y) :m_x(x), m_y(y) {};
	void show(){
		cout << "m_x=" << m_x << ",m_y=" << m_y << endl;
	}

	//类模板
	template<class T>//内部的模板参数名可以和外部的相同，也可以不同（没必要相同）
	class BB {
	public:
		T m_a;
		T1 m_b;//也可以用外模板的类型
		BB() {};
		/*void show() {
			cout << "m_a=" << m_a << ",m_b=" << m_b << endl;
		}*/
		void show();//可以在类外定义，这里只保留声明---------------------------------------------1
	};
	BB<string>m_bb;


	//函数模板
	template<typename T>//这里的通用类型与类模板处的通用类型没有关系
	//void show(T tt)
	//{//与AA原本的show参数不同，可以形成重载
	//	cout << "tt=" << tt << endl;//show也是模板类AA的成员函数，不过它是函数模板
	//	cout << "m_x=" << m_x << ",m_y=" << m_y << endl;//可以访问AA的成员变量
	//	m_bb.show();//m_bb也是成员数据，虽然是模板类实例化，但依然可以访问
	//}

	void show(T tt);//可以在类外定义，这里只保留声明---------------------------------------------2
	//{//与AA原本的show参数不同，可以形成重载
	//	cout << "tt=" << tt << endl;//show也是模板类AA的成员函数，不过它是函数模板
	//	cout << "m_x=" << m_x << ",m_y=" << m_y << endl;//可以访问AA的成员变量
	//	m_bb.show();//m_bb也是成员数据，虽然是模板类实例化，但依然可以访问
	//}
};

//定义-------------------------------------------------------------------------------------------1
template<class T1, class T2>//AA模板类头部标签
template<class T>//BB模板类头部标签
void AA<T1,T2>::BB<T>::show() {//作用域逐级查找声明
	cout << "m_a=" << m_a << ",m_b=" << m_b << endl;
}

//定义-------------------------------------------------------------------------------------------2
template<class T1,class T2>
template<typename T>
void AA<T1,T2>::show(T tt){//与AA原本的show参数不同，可以形成重载
	cout << "tt=" << tt << endl;//show也是模板类AA的成员函数，不过它是函数模板
	cout << "m_x=" << m_x << ",m_y=" << m_y << endl;//可以访问AA的成员变量
	m_bb.show();//m_bb也是成员数据，虽然是模板类实例化，但依然可以访问
}

int main() {
	AA<int, string>a(999, "xxx");
	a.show();
	a.m_bb.m_a = "SUU";
	a.m_bb.m_b = 64;
	a.m_bb.show();
	a.show("xsadasd");
}
