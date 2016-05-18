#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 40
#define SLEEP_TIME 300

enum COLORS{
	WHITE = 15,
	RED = 12,
	GREEN = 10,
	BLUE = 11,
	YELLOW = 14
};

void gui_changeSize(void);
void gui_jumpTo(int x, int y);
void gui_setColor(int color);