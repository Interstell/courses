#pragma once

#include "headers.h"
#define MAX_NUM_OF_BULLETS 50
#define MAX_HIT_RESULT 9

typedef struct bullets_s* bullets_t;
typedef struct player_s* player_t;


bullets_t bullets_createList(void);
void bullets_deleteList(bullets_t list);

void bullets_shoot(bullets_t self, enum PLAYERTYPE playerType, COORD coord);
void bullets_move(bullets_t self);
int bullets_checkHitAndBorders(bullets_t self, player_t player1, player_t player2);
int bullets_getCount(bullets_t self);

void bullets_runTests(void);