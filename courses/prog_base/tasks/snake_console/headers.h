#ifndef _INC_HEADERS
#define _INC_HEADERS
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "cui.h"
#include "cui_additional.h"
#include "filesIO.h"
#include "snake.h"
#include "stats.h"

static const int WINDOW_WIDTH = 80;
static const int WINDOW_HEIGHT = 25;
static const int AppleColors[5] = { 26, 91, 112, 155, 185 };
static const int AppleLevels[] = { 8, 20, 40, 70, 110, 150 };
static const int SpeedLevels[9] = { 70, 65, 60, 55, 50, 45, 40, 30, 20 };
enum VECTOR { DOWN, UP, LEFT, RIGHT };
enum COLORS { BACKGROUND = 10, BODY = 46, HEAD = 202, HEADER = 138, SCORE = 142, INTRO = 27, INTRO_H = 30 };
struct BODY {
	int X;
	int Y;
	enum VECTOR Vector;
};
struct APPLE{
	int X;
	int Y;
	int Color;
};
struct GAME{
	int Level;
	int Score;
	time_t Time;
	char Name[20];
};


#endif