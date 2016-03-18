#pragma once

#include "headers.h"
#define MAX_COMMANDS_IN_QUEUE 30
#define SHOOT_COOLDOWN 500 //msec
#define TICK_COOLDOWN 33
typedef struct player_s* player_t;

enum COMMANDS{
	PLAYER1_UP = 1,
	PLAYER1_DOWN,
	PLAYER1_RIGHT,
	PLAYER1_LEFT,
	PLAYER2_UP,
	PLAYER2_DOWN,
	PLAYER2_RIGHT,
	PLAYER2_LEFT,
	PLAYER1_JUMP,
	PLAYER2_JUMP,
	PLAYER1_SHOOT,
	PLAYER2_SHOOT
};

void game_enqueue(enum COMMANDS cmd);
int game_queueCount(void);
void game_getNProcessInput(player_t player1, player_t player2, bullets_t bulletsList, SYSTEMTIME* lastHit1, SYSTEMTIME* lastHit2, SYSTEMTIME* queueTick);
void game_queuePerform(player_t player1, player_t player2, bullets_t bullets);
int game_checkCooldown(SYSTEMTIME lastHit);
int game_checkQueueTick(SYSTEMTIME lastTick);
void game_restart(player_t* player1, player_t* player2, bullets_t* bulletsList);

void game_runTests(void);