#include<iostream>
using namespace std;


//没有构造函数的类叫聚合体
struct Vector2 {
	float x, y;
};

struct Rect {
	union {
		struct { float x, y, w, h; };
		struct { Vector2 position, size; };
	};
	float left()const { return x; };
	float top()const { return y; };
	float right()const { return x + w; };
	float bottom()const { return y + h; };
	float center_x()const { return x + w / 2; };
	float center_y()const { return y + h / 2; };
	Vector2 center()const { return { x + w / 2 ,y + h / 2 }; };
	void move_left_to(float l) { x = l; };
	void move_top_to(float t) { y = t; };
	void move_right_to(float r) { x = r - w; };
	void move_bottom_to(float b) { y = b - h; };
	void move_cx_to(float cx) { x = cx - w / 2; };
	void move_cy_to(double cy) { y = cy - h / 2; };
	void move_center_to(Vector2 p) { x = p.x - w / 2, y = p.y - h / 2; };
	void zoom(double multi) { w *= multi, h *= multi; };
	Rect get_offset(float dx, float dy) { return { x + dx,y + dy,w,h }; };
};

int main() {
	Vector2 v{ 9,9 };//聚合构造
	Rect r;
}