#include "headers.h"


void gui_printPixel(int x, int y, int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsole, pos);
	printf((color == REDBULLET || color == GREENBULLET)?"*":" ");
}

void gui_changeSize(){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	BOOL ok;
	coord.X = WINDOW_WIDTH;
	coord.Y = WINDOW_HEIGHT;
	ok = SetConsoleScreenBufferSize(hStdout, coord);
	SMALL_RECT test = { 0, 0, coord.X - 1, coord.Y - 1 };
	SetConsoleWindowInfo(hStdout, ok, &test);
}

void gui_setColor(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void gui_JumpTo(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsole, pos);
}

void gui_showScores(player_t player1, player_t player2){
	gui_JumpTo(WINDOW_WIDTH / 2 - 2, 0);
	gui_setColor(YELLOWONBLACK);
	printf("%d : %d (UNTIL %d)", player_getScore(player1), player_getScore(player2), MAX_HIT_RESULT);
}

void gui_printDividingLine(void){
	gui_setColor(YELLOW);
	for (int i = 2; i < WINDOW_HEIGHT; i+=2){
		gui_JumpTo(WINDOW_WIDTH / 2, i);
		printf(" ");
	}
}

void gui_printRectangle(int x1, int y1, int x2, int y2, char border, int color){
	COORD pos = { x1, y1 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	for (pos.X; pos.X <= x2; pos.X++){
		for (pos.Y; pos.Y <= y2; pos.Y++){
			gui_JumpTo(pos.X, pos.Y);
			if ((pos.X == x1) || (pos.X == x2) || (pos.Y == y1) || (pos.Y == y2)){
				printf("%c", border);
			}
			else printf(" ");
		}
		pos.Y = y1;
	}
}

void gui_printWin(enum PLAYERTYPE side){
	switch (side){
	case LEFTSIDE:
		gui_printRectangle(10, 5, 40, 10, 177, 42);
		gui_JumpTo(20, 7);
		break;
	case RIGHTSIDE:
		gui_printRectangle(WINDOW_WIDTH - 40, 5, WINDOW_WIDTH - 10, 10, 177, 42);
		gui_JumpTo(WINDOW_WIDTH - 30, 7);
		break;
	}
	gui_setColor(46);
	printf((side == LEFTSIDE) ? "PLAYER 1 WIN!" : "PLAYER2 WIN!");

}