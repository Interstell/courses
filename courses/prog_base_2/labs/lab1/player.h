#pragma once

#include "headers.h"

typedef struct player_s* player_t;

enum PLAYERTYPE{
	LEFTSIDE = 100,
	RIGHTSIDE
};

enum DIRECTION{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

enum COLOR{
	BLACK = 12,
	BLUE = 28,
	GREEN = 44,
	SALAD = 172,
	RED = 206,
	YELLOW = 236,
	WHITE = 252,
	REDBULLET = 207,
	GREENBULLET = 47,
	YELLOWONBLACK = 14
};

player_t player_create(enum PLAYERTYPE playerType);
void player_delete(player_t player);

void player_draw(player_t player);
void player_move(player_t player, enum DIRECTION direction);
void player_clean(player_t player);
COORD player_getGunCoord(player_t player);
COORD player_getTopCoord(player_t player);
COORD player_getBottomCoord(player_t player);
void player_incScore(player_t player);
int player_getScore(player_t player);
void player_respawn(player_t playerToRespawn, player_t secondPlayer);

void player_runTests(void);