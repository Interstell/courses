#include "gui.h"

void gui_changeSize(void){
	COORD crd = { SCREEN_WIDTH, SCREEN_HEIGHT };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hConsole, 1, &src);
	SetConsoleScreenBufferSize(hConsole, crd);
}

void gui_jumpTo(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsole, pos);
}

void gui_setColor(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}