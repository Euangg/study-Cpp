#include<iostream>
using namespace std;


struct Vector2 { 
	float x, y;
	//Vector2() {};
	//Vector2(float px, float py) :x(px), y(py) { cout << "构造函数" << endl; };
};

void PrintVector1(Vector2 v) { cout << v.x << "," << v.y << endl; }//拷贝传参
void PrintVector2(const Vector2& v) { cout << v.x << "," << v.y << endl; }//引用传参
void test1() {
	PrintVector1({ 1,2 });
	PrintVector1(Vector2(22, 33));

	PrintVector2(std::move(Vector2{ 66,99 }));
	PrintVector2(std::move(Vector2(11, 22)));
}


int main() {
	test1();
}