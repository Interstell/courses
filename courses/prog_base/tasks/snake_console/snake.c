#include "headers.h"

void printSnakePart(struct BODY Snake, enum COLORS color, struct APPLE eatenApple){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { Snake.X, Snake.Y };
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, color);
	if (color != BACKGROUND){
		if ((Snake.X == eatenApple.X) && (Snake.Y == eatenApple.Y)) printf("*");
		else if (Snake.Vector == UP) printf("^");
		else if (Snake.Vector == DOWN) printf("V");
		else if (Snake.Vector == LEFT) printf("<");
		else if (Snake.Vector == RIGHT) printf(">");
	}
	else printf("%s", " ");

}
void printSnake(struct BODY Snake[], int length, struct APPLE eatenApple){
	struct APPLE _crutch = { 0, 0 };
	printSnakePart(Snake[0], HEAD, _crutch);
	for (int i = 1; i < length; i++)
		printSnakePart(Snake[i], BODY, eatenApple);
}
void cleanSnake(struct BODY Snake[], int length){
	struct APPLE _crutch = { 0, 0 };
	for (int i = 0; i < length; i++)
		printSnakePart(Snake[i], BACKGROUND, _crutch);
}
void initSnake(struct BODY Snake[]){
	struct APPLE _crutch = { 0, 0 };
	Snake[0].X = 12;
	Snake[0].Y = 7;
	Snake[0].Vector = RIGHT;
	Snake[1].X = 11;
	Snake[1].Y = 7;
	Snake[1].Vector = RIGHT;
	Snake[2].X = 10;
	Snake[2].Y = 7;
	Snake[2].Vector = RIGHT;
	printSnakePart(Snake[0], BACKGROUND, _crutch);
	system("cls");
	printSnake(Snake, 3, _crutch);
}
void shiftVector(struct BODY Snake[], int length){
	for (int i = length - 1; i >= 1; i--)
		Snake[i].Vector = Snake[i - 1].Vector;
}
void moveCoords(struct BODY Snake[], int length){
	for (int i = 0; i < length; i++){
		switch (Snake[i].Vector){
		case RIGHT:
			Snake[i].X++;
			if (Snake[i].X>WINDOW_WIDTH - 1) Snake[i].X = 0;
			break;
		case LEFT:
			Snake[i].X--;
			if (Snake[i].X < 0) Snake[i].X = WINDOW_WIDTH - 1;
			break;
		case UP:
			Snake[i].Y--;
			if (Snake[i].Y < 1) Snake[i].Y = WINDOW_HEIGHT - 1;
			break;
		case DOWN:
			Snake[i].Y++;
			if (Snake[i].Y>WINDOW_HEIGHT - 1) Snake[i].Y = 1;
		}
	}
}
int isPartOfTheBody(int x, int y, struct BODY Snake[], int snakeLength){
	for (int i = 1; i < snakeLength; i++){
		if ((Snake[i].X == x) && (Snake[i].Y == y)) return 1;
	}
	return 0;
}
void growApple(struct BODY Snake[], int snakeLength, struct APPLE Apples[], int appleNum){
	Apples[appleNum].X = rand() % WINDOW_WIDTH;
	Apples[appleNum].Y = rand() % (WINDOW_HEIGHT - 1) + 1;
	while (isPartOfTheBody(Apples[appleNum].X, Apples[appleNum].Y, Snake, snakeLength)){
		Apples[appleNum].X = rand() % WINDOW_WIDTH;
		Apples[appleNum].Y = rand() % (WINDOW_HEIGHT - 1) + 1;
	}
	Apples[appleNum].Color = AppleColors[rand() % 5];
}
void printApple(struct APPLE Apples[], int appleNum){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { Apples[appleNum].X, Apples[appleNum].Y };
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, Apples[appleNum].Color);
	printf("*");
}
int isGameOver(struct BODY Snake[], int snakeLength){
	for (int i = 1; i < snakeLength; i++){
		if ((Snake[0].X == Snake[i].X) && (Snake[0].Y == Snake[i].Y)) return 1;
	}
	return 0;
}
void printApples(struct APPLE Apples[], int appleAmount){
	for (int i = 0; i < appleAmount; i++){
		printApple(Apples, i);
	}
}
