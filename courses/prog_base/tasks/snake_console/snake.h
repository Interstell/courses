#ifndef _INC_SNAKE
#define _INC_SNAKE
void printSnakePart(struct BODY Snake, enum COLORS color, struct APPLE eatenApple);
void printSnake(struct BODY Snake[], int length, struct APPLE eatenApple);
void cleanSnake(struct BODY Snake[], int length);
void initSnake(struct BODY Snake[]);
void shiftVector(struct BODY Snake[], int length);
void moveCoords(struct BODY Snake[], int length);
int isPartOfTheBody(int x, int y, struct BODY Snake[], int snakeLength);
void growApple(struct BODY Snake[], int snakeLength, struct APPLE Apples[], int appleNum);
void printApple(struct APPLE Apples[], int appleNum);
int isGameOver(struct BODY Snake[], int snakeLength);
void printApples(struct APPLE Apples[], int appleAmount);
#endif