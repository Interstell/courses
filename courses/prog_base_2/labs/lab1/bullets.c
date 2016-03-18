#include "headers.h"

typedef struct player_s* player_t;

struct bullet{
	int status;
	enum PLAYERTYPE shooter;
	COORD coord;
};

struct bullets_s{
	struct bullet bullets[MAX_NUM_OF_BULLETS];
	int count;
};

bullets_t bullets_createList(void){
	bullets_t bulletsList = (bullets_t)malloc(sizeof(struct bullets_s));
	if (NULL == bulletsList) exit(EXIT_FAILURE);
	for (int i = 0; i < MAX_NUM_OF_BULLETS; i++){
		bulletsList->bullets[i].status = 0;
	}
	bulletsList->count = 0;
	return bulletsList;
}

void bullets_deleteList(bullets_t list){
	free(list);
}

void bullets_shoot(bullets_t self, enum PLAYERTYPE playerType, COORD coord){
	for (int i = 0; i < MAX_NUM_OF_BULLETS; i++){
		if (self->bullets[i].status == 0){
			self->bullets[i].status = 1;
			self->bullets[i].shooter = playerType;
			self->bullets[i].coord = coord;
			self->count++;
			break;
		}
	}
}

void bullets_move(bullets_t self){
	for (int i = 0; i < MAX_NUM_OF_BULLETS; i++){
		if (self->bullets[i].status == 1){
			gui_printPixel(self->bullets[i].coord.X, self->bullets[i].coord.Y, BLACK);
			switch (self->bullets[i].shooter){
			case LEFTSIDE:
				self->bullets[i].coord.X++;
				gui_printPixel(self->bullets[i].coord.X, self->bullets[i].coord.Y, REDBULLET);
				break;
			case RIGHTSIDE:
				self->bullets[i].coord.X--;
				gui_printPixel(self->bullets[i].coord.X, self->bullets[i].coord.Y, GREENBULLET);
				break;
			}
			
		}
	}
}

int bullets_checkHitAndBorders(bullets_t self, player_t player1, player_t player2){
	int res = 0;
	for (int i = 0; i < MAX_NUM_OF_BULLETS; i++){
		int toDelete = 0;
		COORD topCoord, botCoord;
		if (self->bullets[i].status == 1){
			switch (self->bullets[i].shooter){
			case LEFTSIDE:
				if (self->bullets[i].coord.X == WINDOW_WIDTH - 1) toDelete = 1;
				topCoord = player_getTopCoord(player2);
				botCoord = player_getBottomCoord(player2);
				if (self->bullets[i].coord.X >= topCoord.X + 2
					&& self->bullets[i].coord.X <= botCoord.X
					&& self->bullets[i].coord.Y >= topCoord.Y
					&& self->bullets[i].coord.Y <= botCoord.Y){
						player_incScore(player1);
						if (player_getScore(player1) == MAX_HIT_RESULT){
							gui_printWin(LEFTSIDE);
							gui_showScores(player1, player2);
							_getch();
							game_restart(&player1, &player2, &self);
							return 1;
						}
						player_clean(player2);
						player_respawn(player2, player1);
						toDelete = 1;
					}
				break;
			case RIGHTSIDE:
				if (self->bullets[i].coord.X == 0) toDelete = 1;
				topCoord = player_getTopCoord(player1);
				botCoord = player_getBottomCoord(player1);
				if (self->bullets[i].coord.X >= topCoord.X
					&& self->bullets[i].coord.X <= botCoord.X - 2
					&& self->bullets[i].coord.Y >= topCoord.Y
					&& self->bullets[i].coord.Y <= botCoord.Y){
					player_incScore(player2);
					if (player_getScore(player2) == MAX_HIT_RESULT){
						gui_printWin(RIGHTSIDE);
						gui_showScores(player1, player2);
						_getch();
						game_restart(&player1, &player2, &self);
						return 1;
					}
					player_clean(player1);
					player_respawn(player1, player2);
					toDelete = 1;
				}
					
				break;
			}
		}
		if (toDelete == 1){
			self->count--;
			if (res == 0) res = 1;
			self->bullets[i].status = 0;
			gui_printPixel(self->bullets[i].coord.X, self->bullets[i].coord.Y, BLACK);
		}
	}
	return res;
}

int bullets_getCount(bullets_t self){
	return self->count;
}
