#include "headers.h"


void JumpTo(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}
void printRect(int x1, int y1, int x2, int y2, char border, int color){
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x1;
	pos.Y = y1;
	SetConsoleTextAttribute(hConsole, color);
	for (pos.X; pos.X <= x2; pos.X++){
		for (pos.Y; pos.Y <= y2; pos.Y++){
			JumpTo(pos.X, pos.Y);
			if ((pos.X == x1) || (pos.X == x2) || (pos.Y == y1) || (pos.Y == y2)){
				printf("%c", border);
			}
			else printf(" ");
		}
		pos.Y = y1;
	}
}
void setColor(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
void changeSize(){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	BOOL ok;
	coord.X = WINDOW_WIDTH;
	coord.Y = WINDOW_HEIGHT + 1;
	ok = SetConsoleScreenBufferSize(hStdout, coord);
	SMALL_RECT test = { 0, 0, coord.X - 1, coord.Y - 1 };
	SetConsoleWindowInfo(hStdout, ok, &test);
}


