#pragma once
#include "headers.h"

#define WINDOW_WIDTH 121
#define WINDOW_HEIGHT 50

void gui_setColor(int color);
void gui_printPixel(int x, int y, int color);
void gui_changeSize();
void gui_JumpTo(int x, int y);
void gui_showScores(player_t player1, player_t player2);
void gui_printDividingLine(void);
void gui_printRectangle(int x1, int y1, int x2, int y2, char border, int color);
void gui_printWin(enum PLAYERTYPE side);