#include"MyWindow.h"

void start();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	start();
	return 0;
}


void start() {
	Editor editor;

	editor.init();
	editor.createWindow(L"XXXXXXXXXXXXXXXXXXXXXX", 0, 0, 800, 500);
	editor.run();

}

