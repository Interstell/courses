#ifndef _INC_CUI
#define _INC_CUI

int RunMainMenu(void);
void PrintMainMenu(char* list[], int selected, int x, int y, int size);
void printHighscores(struct GAME Stats[][30], int records[]);
void PrintMenu(char* list[], int selected, int x, int y, int size);
void RunMenu(struct GAME Stats[][30], int records[]);
void printIntro(int* speedLevel, char* name);
void printGameOver(int score, int speedLevel, struct GAME Stats[][30], int records[]);
void refreshScreen(struct BODY Snake[], int snakeLength, struct APPLE Apples[], int appleAmount, struct APPLE eatenApple, int score, struct GAME Stats[][30], int speedLevel, int records[]);
void printHeader(int score);
void printFooter(int score, struct GAME Stats[][30], int speedLevel, int records[]);

#endif