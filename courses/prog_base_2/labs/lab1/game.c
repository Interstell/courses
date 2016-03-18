#include "headers.h"


struct gameQueue{
	int count;
	enum COMMANDS cmd[MAX_COMMANDS_IN_QUEUE];
} queue; //yep, global structure, but encapsulated

void game_enqueue(enum COMMANDS cmd){
	queue.cmd[queue.count++] = cmd;
}

int game_queueCount(void){
	return queue.count;
}

void game_queuePerform(player_t player1, player_t player2, bullets_t bullets){
	for (int i = 0; i < queue.count; i++){
		switch (queue.cmd[i]){
		case PLAYER1_UP:
			player_move(player1, UP);
			break;
		case PLAYER1_DOWN:
			player_move(player1, DOWN);
			break;
		case PLAYER1_RIGHT:
			player_move(player1, RIGHT);
			break;
		case PLAYER1_LEFT:
			player_move(player1, LEFT);
			break;
		case PLAYER2_UP:
			player_move(player2, UP);
			break;
		case PLAYER2_DOWN:
			player_move(player2, DOWN);
			break;
		case PLAYER2_RIGHT:
			player_move(player2, RIGHT);
			break;
		case PLAYER2_LEFT:
			player_move(player2, LEFT);
			break;
		case PLAYER1_SHOOT:
			bullets_shoot(bullets, LEFTSIDE, player_getGunCoord(player1));
			break;
		case PLAYER2_SHOOT:
			bullets_shoot(bullets, RIGHTSIDE, player_getGunCoord(player2));
			break;
		}
	}
	queue.count = 0;
}

int game_checkCooldown(SYSTEMTIME lastHit){
	SYSTEMTIME now;
	GetLocalTime(&now);
	long int lastMs = lastHit.wMilliseconds + lastHit.wSecond * 1000 + lastHit.wMinute * 1000 * 60;
	long int nowMs = now.wMilliseconds + now.wSecond * 1000 + now.wMinute * 1000 * 60;
	return (nowMs - lastMs > SHOOT_COOLDOWN) ? 1 : 0;
}

int game_checkQueueTick(SYSTEMTIME lastTick){
	SYSTEMTIME now;
	GetLocalTime(&now);
	long int lastMs = lastTick.wMilliseconds + lastTick.wSecond * 1000 + lastTick.wMinute * 1000 * 60;
	long int nowMs = now.wMilliseconds + now.wSecond * 1000 + now.wMinute * 1000 * 60;
	return (nowMs - lastMs > TICK_COOLDOWN) ? 1 : 0;
}

void game_getNProcessInput(player_t player1, player_t player2, bullets_t bulletsList, SYSTEMTIME* lastHit1, SYSTEMTIME* lastHit2, SYSTEMTIME* queueTick){
	if (_kbhit()){
		char c = _getch();
		player_clean(player1);
		player_clean(player2);
		switch (c){
		case 'w':
			game_enqueue(PLAYER1_UP);
			break;
		case 'a':
			game_enqueue(PLAYER1_LEFT);
			break;
		case 's':
			game_enqueue(PLAYER1_DOWN);
			break;
		case 'd':
			game_enqueue(PLAYER1_RIGHT);
			break;
		case 56: //NUMPAD UP
			game_enqueue(PLAYER2_UP);
			break;
		case 53: //NUMPAD DOWN
			game_enqueue(PLAYER2_DOWN);
			break;
		case 54: //NUMPAD RIGHT
			game_enqueue(PLAYER2_RIGHT);
			break;
		case 52: //NUMPAD LEFT
			game_enqueue(PLAYER2_LEFT);
			break;
		case 32: //SPACE
			if (game_checkCooldown(*lastHit1)){
				game_enqueue(PLAYER1_SHOOT);
				GetLocalTime(lastHit1);
			}
			break;
		case 48: //NUMPAD ZERO
			if (game_checkCooldown(*lastHit2)){
				game_enqueue(PLAYER2_SHOOT);
				GetLocalTime(lastHit2);
			}
			break;
		case 'r':
			game_restart(&(player1), &(player2), &(bulletsList));
			break;
		case 27: //ESC for exit
			player_delete(player1);
			player_delete(player2);
			bullets_deleteList(bulletsList);
			exit(EXIT_SUCCESS);
			break;
		}
		if (game_checkQueueTick(*queueTick)){
		game_queuePerform(player1, player2, bulletsList);
			GetLocalTime(queueTick);
		}
		player_draw(player1);
		player_draw(player2);
	}
}

void game_restart(player_t* player1, player_t* player2, bullets_t* bulletsList){
	player_delete(*player1);
	*player1 = player_create(LEFTSIDE);
	player_delete(*player2);
	*player2 = player_create(RIGHTSIDE);
	bullets_deleteList(*bulletsList);
	*bulletsList = bullets_createList();
	gui_setColor(BLACK);
	system("cls");
}