#include<iostream>
#include<chrono>
using namespace std;

//计算某一帧的瞬时帧率
void Mode1() {
	auto last_time = chrono::high_resolution_clock::now();//瞬时时刻
	float fps = 0;
	while (1) {
		cout << fps << endl;
		system("cls");//清空cmd，会将帧率限制在60帧/s左右

		auto current_time = chrono::high_resolution_clock::now();
		auto delta = chrono::duration_cast<chrono::milliseconds>(current_time - last_time).count();//帧时间间隔
		fps = 1 / (delta / 1000.);//每帧计算一次瞬时帧率
		last_time = current_time;
	}
}

//计算某段时间内的平均帧率
void Mode2() {
	auto last_time = chrono::high_resolution_clock::now();
	int frame_count = 0;
	float fps = 0;
	while (1) {
		cout << fps << endl;
		system("cls");

		frame_count++;
		auto current_time = chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::milliseconds>(current_time - last_time).count();
		if (elapsed >= 500) {//每0.5秒计算一次平均帧率
			fps = frame_count / (elapsed / 1000.);
			frame_count = 0;
			last_time = current_time;
		}
	}
}

int main() {
	//Mode1();
	Mode2();
}