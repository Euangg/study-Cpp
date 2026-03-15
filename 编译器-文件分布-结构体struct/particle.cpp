#include"particle.h"
#include<iostream>
using std::cout;
using std::endl;

//不能当作命名空间
void sParticle::Print() {
	cout << "pos:" << x << "," << y << endl;
}
