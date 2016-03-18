#include "headers.h"

struct player_s{
	enum PLAYERTYPE playerType;
	COORD topLeftCoord;
	COORD bottomRightCoord;
	COORD gunCoord;
	int score;
};

player_t player_create(enum PLAYERTYPE playerType){
	player_t player = (player_t)malloc(sizeof(struct player_s));
	if (NULL == player) exit(EXIT_FAILURE);
	player->playerType = playerType;
	player->score = 0;
	switch (playerType){
	case LEFTSIDE:
		player->topLeftCoord.X = 2;
		player->topLeftCoord.Y = 2;
		player->bottomRightCoord.X = player->topLeftCoord.X + 7;
		player->bottomRightCoord.Y = player->topLeftCoord.Y + 10;
		player->gunCoord.X = player->topLeftCoord.X + 8;
		player->gunCoord.Y = player->topLeftCoord.Y + 5;
		break;
	case RIGHTSIDE:
		player->topLeftCoord.X = WINDOW_WIDTH - 10;
		player->topLeftCoord.Y = 2;
		player->bottomRightCoord.X = player->topLeftCoord.X + 7;
		player->bottomRightCoord.Y = player->topLeftCoord.Y + 10;
		player->gunCoord.X = player->topLeftCoord.X - 1;
		player->gunCoord.Y = player->topLeftCoord.Y + 5;
		break;
	}

	return player;
}

void player_delete(player_t player){
	free(player);
}


void player_draw(player_t player){
	COORD top = player->topLeftCoord;
	switch (player->playerType){
	case LEFTSIDE:
		gui_printPixel(top.X + 2, top.Y, GREEN);
		gui_printPixel(top.X + 1, top.Y + 1, WHITE);
		gui_printPixel(top.X + 2, top.Y + 1, WHITE);
		gui_printPixel(top.X + 3, top.Y + 1, WHITE);
		gui_printPixel(top.X + 1, top.Y + 2, WHITE);
		gui_printPixel(top.X + 2, top.Y + 2, WHITE);
		gui_printPixel(top.X + 3, top.Y + 2, RED);
		gui_printPixel(top.X + 1, top.Y + 3, WHITE);
		gui_printPixel(top.X + 2, top.Y + 3, WHITE);
		gui_printPixel(top.X + 3, top.Y + 3, WHITE);
		gui_printPixel(top.X + 2, top.Y + 4, WHITE);
		gui_printPixel(top.X + 2, top.Y + 5, WHITE);
		gui_printPixel(top.X + 2, top.Y + 6, WHITE);
		gui_printPixel(top.X + 3, top.Y + 6, WHITE);
		gui_printPixel(top.X + 4, top.Y + 6, WHITE);
		gui_printPixel(top.X + 5, top.Y + 6, WHITE);
		gui_printPixel(top.X + 4, top.Y + 5, RED);
		gui_printPixel(top.X + 5, top.Y + 5, RED);
		gui_printPixel(top.X + 6, top.Y + 5, RED);
		gui_printPixel(top.X + 7, top.Y + 5, RED);
		gui_printPixel(top.X + 4, top.Y + 7, RED);
		gui_printPixel(top.X + 2, top.Y + 7, WHITE);
		gui_printPixel(top.X + 2, top.Y + 8, WHITE);
		gui_printPixel(top.X + 1, top.Y + 9, WHITE);
		gui_printPixel(top.X + 3, top.Y + 9, WHITE);
		gui_printPixel(top.X, top.Y + 10, WHITE);
		gui_printPixel(top.X + 4, top.Y + 10, WHITE);
		break;
	case RIGHTSIDE:
		gui_printPixel(top.X + 5, top.Y, YELLOW);
		gui_printPixel(top.X + 4, top.Y + 1, WHITE);
		gui_printPixel(top.X + 5, top.Y + 1, WHITE);
		gui_printPixel(top.X + 6, top.Y + 1, WHITE);
		gui_printPixel(top.X + 4, top.Y + 2, GREEN);
		gui_printPixel(top.X + 5, top.Y + 2, WHITE);
		gui_printPixel(top.X + 6, top.Y + 2, WHITE);
		gui_printPixel(top.X + 4, top.Y + 3, WHITE);
		gui_printPixel(top.X + 5, top.Y + 3, WHITE);
		gui_printPixel(top.X + 6, top.Y + 3, WHITE);
		gui_printPixel(top.X + 5, top.Y + 4, WHITE);
		gui_printPixel(top.X + 5, top.Y + 5, WHITE);
		gui_printPixel(top.X + 5, top.Y + 6, WHITE);
		gui_printPixel(top.X + 4, top.Y + 6, WHITE);
		gui_printPixel(top.X + 3, top.Y + 6, WHITE);
		gui_printPixel(top.X + 2, top.Y + 6, WHITE);
		gui_printPixel(top.X + 3, top.Y + 5, GREEN);
		gui_printPixel(top.X + 2, top.Y + 5, GREEN);
		gui_printPixel(top.X + 1, top.Y + 5, GREEN);
		gui_printPixel(top.X, top.Y + 5, GREEN);
		gui_printPixel(top.X + 3, top.Y + 7, GREEN);
		gui_printPixel(top.X + 5, top.Y + 7, WHITE);
		gui_printPixel(top.X + 5, top.Y + 8, WHITE);
		gui_printPixel(top.X + 4, top.Y + 9, WHITE);
		gui_printPixel(top.X + 6, top.Y + 9, WHITE);
		gui_printPixel(top.X + 3, top.Y + 10, WHITE);
		gui_printPixel(top.X + 7, top.Y + 10, WHITE);
		break;
	}
}

void player_clean(player_t player){
	COORD top = player->topLeftCoord;
	switch (player->playerType){
	case LEFTSIDE:
		gui_printPixel(top.X + 2, top.Y, BLACK);
		gui_printPixel(top.X + 1, top.Y + 1, BLACK);
		gui_printPixel(top.X + 2, top.Y + 1, BLACK);
		gui_printPixel(top.X + 3, top.Y + 1, BLACK);
		gui_printPixel(top.X + 1, top.Y + 2, BLACK);
		gui_printPixel(top.X + 2, top.Y + 2, BLACK);
		gui_printPixel(top.X + 3, top.Y + 2, BLACK);
		gui_printPixel(top.X + 1, top.Y + 3, BLACK);
		gui_printPixel(top.X + 2, top.Y + 3, BLACK);
		gui_printPixel(top.X + 3, top.Y + 3, BLACK);
		gui_printPixel(top.X + 2, top.Y + 4, BLACK);
		gui_printPixel(top.X + 2, top.Y + 5, BLACK);
		gui_printPixel(top.X + 2, top.Y + 6, BLACK);
		gui_printPixel(top.X + 3, top.Y + 6, BLACK);
		gui_printPixel(top.X + 4, top.Y + 6, BLACK);
		gui_printPixel(top.X + 5, top.Y + 6, BLACK);
		gui_printPixel(top.X + 4, top.Y + 5, BLACK);
		gui_printPixel(top.X + 5, top.Y + 5, BLACK);
		gui_printPixel(top.X + 6, top.Y + 5, BLACK);
		gui_printPixel(top.X + 7, top.Y + 5, BLACK);
		gui_printPixel(top.X + 4, top.Y + 7, BLACK);
		gui_printPixel(top.X + 2, top.Y + 7, BLACK);
		gui_printPixel(top.X + 2, top.Y + 8, BLACK);
		gui_printPixel(top.X + 1, top.Y + 9, BLACK);
		gui_printPixel(top.X + 3, top.Y + 9, BLACK);
		gui_printPixel(top.X, top.Y + 10, BLACK);
		gui_printPixel(top.X + 4, top.Y + 10, BLACK);
		break;
	case RIGHTSIDE:
		gui_printPixel(top.X + 5, top.Y, BLACK);
		gui_printPixel(top.X + 4, top.Y + 1, BLACK);
		gui_printPixel(top.X + 5, top.Y + 1, BLACK);
		gui_printPixel(top.X + 6, top.Y + 1, BLACK);
		gui_printPixel(top.X + 4, top.Y + 2, BLACK);
		gui_printPixel(top.X + 5, top.Y + 2, BLACK);
		gui_printPixel(top.X + 6, top.Y + 2, BLACK);
		gui_printPixel(top.X + 4, top.Y + 3, BLACK);
		gui_printPixel(top.X + 5, top.Y + 3, BLACK);
		gui_printPixel(top.X + 6, top.Y + 3, BLACK);
		gui_printPixel(top.X + 5, top.Y + 4, BLACK);
		gui_printPixel(top.X + 5, top.Y + 5, BLACK);
		gui_printPixel(top.X + 5, top.Y + 6, BLACK);
		gui_printPixel(top.X + 4, top.Y + 6, BLACK);
		gui_printPixel(top.X + 3, top.Y + 6, BLACK);
		gui_printPixel(top.X + 2, top.Y + 6, BLACK);
		gui_printPixel(top.X + 3, top.Y + 5, BLACK);
		gui_printPixel(top.X + 2, top.Y + 5, BLACK);
		gui_printPixel(top.X + 1, top.Y + 5, BLACK);
		gui_printPixel(top.X, top.Y + 5, BLACK);
		gui_printPixel(top.X + 3, top.Y + 7, BLACK);
		gui_printPixel(top.X + 5, top.Y + 7, BLACK);
		gui_printPixel(top.X + 5, top.Y + 8, BLACK);
		gui_printPixel(top.X + 4, top.Y + 9, BLACK);
		gui_printPixel(top.X + 6, top.Y + 9, BLACK);
		gui_printPixel(top.X + 3, top.Y + 10, BLACK);
		gui_printPixel(top.X + 7, top.Y + 10, BLACK);
		break;
	}
}

static int checkBorders(player_t player, enum DIRECTION direction){
	switch (direction){
	case UP:
		if (player->topLeftCoord.Y <= 1) return 0;
		break;
	case DOWN:
		if (player->bottomRightCoord.Y >= WINDOW_HEIGHT - 2) return 0;
		if (player->bottomRightCoord.X >= WINDOW_WIDTH - 2 && player->bottomRightCoord.Y >= WINDOW_HEIGHT - 3) return 0;
		break;
	case LEFT:
		switch (player->playerType){
		case LEFTSIDE:
			if (player->topLeftCoord.X <= 1) return 0;
			break;
		case RIGHTSIDE:
			if (player->topLeftCoord.X <= WINDOW_WIDTH / 2 + 1) return 0;
			break;
		}
		break;
	case RIGHT:
		switch (player->playerType){
		case LEFTSIDE:
			if (player->bottomRightCoord.X >= WINDOW_WIDTH / 2 - 2) return 0;
			break;
		case RIGHTSIDE:
			if (player->bottomRightCoord.X >= WINDOW_WIDTH - 2) return 0;
			if (player->bottomRightCoord.X >= WINDOW_WIDTH - 3 && player->bottomRightCoord.Y >= WINDOW_HEIGHT - 2) return 0;
		}
	}
	return 1;
}

void player_move(player_t player, enum DIRECTION direction){
	if (checkBorders(player, direction)){
		switch (direction){
		case UP:
			player->topLeftCoord.Y-=2;
			player->bottomRightCoord.Y-=2;
			player->gunCoord.Y-=2;
			break;
		case DOWN:
			player->topLeftCoord.Y+=2;
			player->bottomRightCoord.Y+=2;
			player->gunCoord.Y+=2;
			break;
		case RIGHT:
			player->topLeftCoord.X+=2;
			player->bottomRightCoord.X+=2;
			player->gunCoord.X+=2;
			break;
		case LEFT:
			player->topLeftCoord.X-=2;
			player->bottomRightCoord.X-=2;
			player->gunCoord.X-=2;
			break;
		}
	}
}

COORD player_getGunCoord(player_t player){
	return player->gunCoord;
}

COORD player_getTopCoord(player_t player){
	return player->topLeftCoord;
}

COORD player_getBottomCoord(player_t player){
	return player->bottomRightCoord;
}

void player_incScore(player_t player){
	player->score++;
}

int player_getScore(player_t player){
	return player->score;
}

void player_respawn(player_t playerToRespawn, player_t secondPlayer){
	if (secondPlayer->gunCoord.Y >= WINDOW_HEIGHT / 2){
		playerToRespawn->topLeftCoord.Y = 2;
	}
	else playerToRespawn->topLeftCoord.Y = WINDOW_HEIGHT - 12;
	playerToRespawn->bottomRightCoord.Y = playerToRespawn->topLeftCoord.Y + 10;
	playerToRespawn->gunCoord.Y = playerToRespawn->topLeftCoord.Y + 5;
}