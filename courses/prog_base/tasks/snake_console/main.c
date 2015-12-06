#include "headers.h"

int main(void){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	struct BODY Snake[100];
	struct GAME Stats[9][30];
	int recordsAmount[9];
	int snakeLength = 3;
	int speedLevel;
	struct APPLE Apples[10], coordsForApple, eatenApple;
	int appleAmount = 1, appleTime = 0, appleLevel = 0, appleLevelReached = 0;
	int score = 0;
	char c;
	char playerName[100];
	srand((unsigned)time(NULL));
	changeSize();
	readStats(Stats, sizeof(Stats), recordsAmount, sizeof(recordsAmount));
	sortAllStat(Stats, recordsAmount);
	while (1){
		int res = RunMainMenu();
		if (res == 0)
			break;
		else if (res == 1){
			printHighscores(Stats, recordsAmount);
			continue;
		}
		else exit(EXIT_SUCCESS);
	}
	printIntro(&speedLevel, playerName);
	initSnake(Snake);
	growApple(Snake, snakeLength, Apples, 0);
	printApple(Apples, 0);
	printHeader(score);
	printFooter(score, Stats, speedLevel, recordsAmount);
	while (1){
		shiftVector(Snake, snakeLength);
		if (_kbhit()){
			c = _getch();
			switch (c){
			case 'w':
				if (Snake[0].Vector != DOWN)
					Snake[0].Vector = UP;
				break;
			case 's':
				if (Snake[0].Vector != UP)
					Snake[0].Vector = DOWN;
				break;
			case 'd':
				if (Snake[0].Vector != LEFT)
					Snake[0].Vector = RIGHT;
				break;
			case 'a':
				if (Snake[0].Vector != RIGHT)
					Snake[0].Vector = LEFT;
				break;
			case 27:
				saveStats(Stats, sizeof(Stats), recordsAmount, sizeof(recordsAmount));
				exit(EXIT_SUCCESS);
				break;
			case 9:
				printHighscores(Stats, recordsAmount);
				refreshScreen(Snake, snakeLength, Apples, appleAmount, eatenApple, score, Stats, speedLevel, recordsAmount);
			}
		}
		if ((c == 32) || (isGameOver(Snake, snakeLength))){
			if (isGameOver(Snake, snakeLength)){
				writeToStat(Stats, recordsAmount, playerName, score, speedLevel);
				sortLevel(Stats[speedLevel], recordsAmount, speedLevel);
				saveStats(Stats, sizeof(Stats), recordsAmount, sizeof(recordsAmount));
				printGameOver(score, speedLevel, Stats, recordsAmount);
				printIntro(&speedLevel, playerName);
			}
			c = 0;
			snakeLength = 3;
			appleAmount = 1;
			score = 0;
			appleTime = 0;
			appleLevel = 0;
			appleLevelReached = 0;
			initSnake(Snake);
			growApple(Snake, snakeLength, Apples, 0);
			refreshScreen(Snake, snakeLength, Apples, appleAmount, eatenApple, score, Stats, speedLevel, recordsAmount);
		}

		cleanSnake(Snake, snakeLength);
		coordsForApple.X = Snake[snakeLength - 1].X;
		coordsForApple.Y = Snake[snakeLength - 1].Y;
		moveCoords(Snake, snakeLength);
		for (int i = 0; i < appleAmount; i++){
			if ((Apples[i].X == Snake[0].X) && (Apples[i].Y == Snake[0].Y)){
				Snake[snakeLength].X = coordsForApple.X;
				Snake[snakeLength].Y = coordsForApple.Y;
				snakeLength++;
				score++;
				printHeader(score);
				eatenApple.X = Apples[i].X;
				eatenApple.Y = Apples[i].Y;
				appleTime = 0;
				growApple(Snake, snakeLength, Apples, i);
				printApple(Apples, i);
				appleLevelReached = 0;
				break;
			}
		}
		appleTime++;
		if (appleTime > snakeLength){
			eatenApple.X = 0;
			eatenApple.Y = 0;
		}
		if ((score == AppleLevels[appleLevel]) && (!appleLevelReached)){
			appleLevelReached = 1;
			growApple(Snake, snakeLength, Apples, appleAmount);
			printApple(Apples, appleAmount);
			appleAmount++;
			appleLevel++;
		}
		printSnake(Snake, snakeLength, eatenApple);
		if (speedLevel>4)
			Sleep(SpeedLevels[speedLevel] - score / 2);
		else Sleep(SpeedLevels[speedLevel] - score);
	}
	getchar();

}
