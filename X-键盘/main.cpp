#include<Windows.h>
#include<iostream>
#include <bitset> 
using namespace std;


void Test1() {
	unsigned char state_key[256] = { 0 };
	int target = 0;
	while (true)
	{
		//system("cls");
		//GetAsyncKeyState
		/*if (GetAsyncKeyState('A')) {
			cout << " A";
		}*/




		//GetKeyState
		/*if (GetKeyState('S')) {
			cout << " B";
		}*/


		//GetKeyboardState
		GetKeyboardState(state_key);
		/*for (int i = 0; i < 256; i++) {
			printf("%d ", state_key[i]);
			if (i % 16 == 0)cout << endl;
		}*/
		//cout << "state_key['A']:";

		for (int i = target; i < target + 128; i++) {
			printf("%d", state_key[i]);
		}
		printf("\n");
	}
}

void Test2() {
	while (true){
		system("cls");
		short astate = GetAsyncKeyState('A');
		//short astate = GetKeyState('A');
		cout << bitset<sizeof(astate) * 8>(astate);

		if (GetAsyncKeyState(VK_ESCAPE))break;
	}
}


int main() {

	Test2();
	
}