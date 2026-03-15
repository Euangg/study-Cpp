#include<iostream>
using namespace std;

//数据结构、层次
// 优雅

//面向标准库
//面向过程
//面向对象

class 单位 {

};

class 小兵 :public 单位 {

};

namespace 英雄 {
	class i英雄 :public 单位 {//抽象
	public:
		int hp;
		int mp;

		virtual void Q() { cout << "放个Q" << endl; };
		virtual void R(i英雄) {}
		void Draw() {};
		void 传送(i英雄) {}

		void PrintHp() {
			cout << "hp:" << hp << endl;
		}
	};
	class 盖伦 :public i英雄 {
	public:
		//构造函数
		盖伦() {
			hp = 150;
		}
		void Q() {
			cout << "无畏冲锋" << endl;
		}
		void R(i英雄& hero) {
			hero.hp -= 100;
		}
		void Draw() {
			//画血条
		}
	};
	class 诺手 :public i英雄 {
	public:
		诺手() {
			hp = 120;
		}
		void Q() {
			cout << "宴请四方" << endl;
		}
		void R(i英雄& hero) {
			cout << "R了一下" << endl;
			hero.hp -= 80;
			if (hero.hp <= 0) {
				RefreshR();
			}
		}
		void RefreshR() { cout << "刷新大招！" << endl; }
		void Draw() {
			//HP
			//MP
		}
	};
	class 塞拉斯 :public i英雄 {
	public:
		bool isSteal = false;
		i英雄* target = nullptr;
		void R(i英雄& 英雄) {
			if (isSteal) {
				target->R(英雄);
				cout << "释放你的大招！" << endl;
			}
			else {
				StealR(英雄);
				cout << "偷你的大招！" << endl;
			}
		}
		void StealR(i英雄& hero) {
			target = &hero;
			isSteal = true;
		}

	};
}
using namespace 英雄;

int main() {
	盖伦 gl;
	诺手 ns;
	塞拉斯 sls;

	i英雄* Player[3];
	Player[0] = &gl;
	Player[1] = &ns;
	Player[2] = &sls;

	for (auto& p : Player) {
		p->Draw();
		p->Q();
		p->PrintHp();
	}
	
	sls.R(gl);
	sls.R(gl);

	ns.R(gl);
	ns.R(gl);
}