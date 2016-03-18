#define _CRT_SECURE_NO_WARNINGS

#include "headers.h"

int main(int argc, char *argv[]){
	if (argc > 1){
		bullets_runTests();
		game_runTests();
		player_runTests();
		_getch();
		exit(EXIT_SUCCESS);
	}

	gui_changeSize();

	player_t player1 = player_create(LEFTSIDE);
	player_draw(player1);
	player_t player2 = player_create(RIGHTSIDE);
	player_draw(player2);
	SYSTEMTIME lastHit1;
	GetLocalTime(&lastHit1);
	SYSTEMTIME lastHit2;
	GetLocalTime(&lastHit2);
	SYSTEMTIME queueTick;
	GetLocalTime(&queueTick);
	bullets_t bulletsList = bullets_createList();

	while (1){
		game_getNProcessInput(player1, player2, bulletsList, &lastHit1, &lastHit2, &queueTick);
		gui_showScores(player1, player2);
		Sleep(18);
		bullets_move(bulletsList);
		gui_printDividingLine();
		int toRedraw = bullets_checkHitAndBorders(bulletsList, player1, player2);
		if (toRedraw){
			player_draw(player1);
			player_draw(player2);
		}
	}

	return EXIT_SUCCESS;
}