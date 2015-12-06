#include "headers.h"

int RunMainMenu(void){
	char*commands[] = { "NEW GAME", "HIGHSCORES", "EXIT" };
	int size = sizeof(commands) / sizeof(int*);
	int selected = 0;
	setColor(BACKGROUND);
	system("cls");
	printRect(3, 3, WINDOW_WIDTH - 4, WINDOW_HEIGHT - 4, 177, INTRO);
	JumpTo(27, WINDOW_HEIGHT - 6);
	setColor(INTRO);
	printf("Urukov Dmitry KPI 2015");
	JumpTo(5, 5);
	setColor(INTRO_H);
	printf("\t\t\t   Welcome to Snake Console");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255);
	PrintMainMenu(commands, selected, 34, 8, size);
	while (1){
		int button = _getch();
		if (button == 13) return selected;
		else if (button == 'w') selected--;
		else if (button == 's') selected++;
		if (selected == -1) selected = size - 1;
		if (selected == size) selected = 0;
		PrintMainMenu(commands, selected, 34, 8, size);
	}
}
void PrintMainMenu(char* list[], int selected, int x, int y, int size){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	for (int i = 0; i < size; i++){
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == selected) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30);
		printf("%s", list[i]);
		coord.Y += 2;
	}
}
void printHighscores(struct GAME Stats[][30], int records[]){
	int res;
	printRect(3, 3, WINDOW_WIDTH - 4, WINDOW_HEIGHT - 4, 177, INTRO);
	JumpTo(5, 5);
	setColor(INTRO_H);
	printf("\t\t\t\t   HIGHSCORES");
	JumpTo(25, 7);
	printf("Level:");
	RunMenu(Stats, records);
}
void PrintMenu(char* list[], int selected, int x, int y, int size){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	for (int i = 0; i < size; i++){
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == selected) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30);
		printf("%s", list[i]);
		coord.X += 2;
	}
}
void RunMenu(struct GAME Stats[][30], int records[]){
	char*commands[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	int size = sizeof(commands) / sizeof(int*);
	int selected = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255);
	PrintMenu(commands, selected, 32, 7, size);
	while (1){
		int limit = (records[selected] < 7) ? records[selected] : 7;
		JumpTo(7, 9);
		setColor(30);
		for (int i = 0; i < limit; i++){
			struct tm* aTm = localtime(&(Stats[selected][i].Time));
			printf("%d.%s | Score: %2d | %02d/%02d/%02d %02d:%02d", i + 1, Stats[selected][i].Name, Stats[selected][i].Score, aTm->tm_mday, aTm->tm_mon + 1, aTm->tm_year + 1900, aTm->tm_hour, aTm->tm_min);
			JumpTo(7, 10 + i);
		}
		JumpTo(7, WINDOW_HEIGHT - 5);
		printf("Press Enter to continue...");
		if (records[selected] == 0){
			JumpTo(7, 9);
			printf("No results on this level.");
		}
		char button = _getch();
		if (button == 13 || button == 32) return;
		else if (button == 'a' || button == 's') selected--;
		else if (button == 'd' || button == 'w') selected++;
		if (selected == -1) selected = size - 1;
		if (selected == size) selected = 0;
		printRect(7, 8, WINDOW_WIDTH - 5, WINDOW_HEIGHT - 5, 32, INTRO);
		PrintMenu(commands, selected, 32, 7, size);

	}
}
void printIntro(int* speedLevel, char* name){
	printRect(3, 3, WINDOW_WIDTH - 4, WINDOW_HEIGHT - 4, 177, INTRO);
	JumpTo(5, 5);
	setColor(INTRO_H);
	printf("\t\t\t   Welcome to Snake Console");
	JumpTo(5, 7);
	printf("Type your name: ");
	gets(name);
	JumpTo(5, 9);
	printf("Select a level (1-9) : ");
	if ((scanf("%d", speedLevel) == 0) || (*speedLevel <= 0) || (*speedLevel > 9)){
		JumpTo(5, 10);
		puts("Wrong level selected. Changed to Level 9 as a punishment.");
		*speedLevel = 9;
		_getch();
	};
	*(speedLevel) = *(speedLevel)-1;
	getchar();
}
void printGameOver(int score, int speedLevel, struct GAME Stats[][30], int records[]){
	printRect(6, 6, WINDOW_WIDTH - 7, WINDOW_HEIGHT - 7, 127, INTRO);
	JumpTo(8, 7);
	setColor(INTRO_H);
	printf("\t\t\t GAME OVER :(");
	JumpTo(8, 9);
	printf("Your score on level ");
	setColor(26);
	printf("%d ", speedLevel + 1);
	setColor(INTRO_H);
	printf("is: ");
	setColor(26);
	printf("%d", score);
	setColor(INTRO_H);
	JumpTo(8, 10);
	printf("Level Top right now: ");
	JumpTo(8, 11);
	int limit = (records[speedLevel] < 5) ? records[speedLevel] : 5;
	for (int i = 0; i < limit; i++){
		struct tm* aTm = localtime(&(Stats[speedLevel][i].Time));
		printf("%d.%s | Score: %2d | %02d/%02d/%02d %02d:%02d", i + 1, Stats[speedLevel][i].Name, Stats[speedLevel][i].Score, aTm->tm_mday, aTm->tm_mon + 1, aTm->tm_year + 1900, aTm->tm_hour, aTm->tm_min);
		JumpTo(8, 12 + i);
	}
	if (records[speedLevel] == 0){
		printf("No results on this level.");
	}
	printf("Press any key to start New Game...");
	_getch();
}
void refreshScreen(struct BODY Snake[], int snakeLength, struct APPLE Apples[], int appleAmount, struct APPLE eatenApple, int score, struct GAME Stats[][30], int speedLevel, int records[]){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND);
	system("cls");
	printApples(Apples, appleAmount);
	printSnake(Snake, snakeLength, eatenApple);
	printHeader(score);
	printFooter(score, Stats, speedLevel, records);
}
void printHeader(int score){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, HEADER);
	for (int i = 0; i < WINDOW_WIDTH; i++){
		printf(" ");
	}
	SetConsoleCursorPosition(hConsole, pos);
	printf("    Score: ");
	SetConsoleTextAttribute(hConsole, SCORE);
	printf("%2d", score);
	SetConsoleTextAttribute(hConsole, HEADER);
	printf(" | Control: WASD | Restart: Space | Highscore: TAB | Exit: Esc");

}
void printFooter(int score, struct GAME Stats[][30], int speedLevel, int records[]){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 1, WINDOW_HEIGHT };
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, HEADER);
	for (int i = 1; i < WINDOW_WIDTH - 1; i++){
		printf(" ");
	}
	SetConsoleCursorPosition(hConsole, pos);
	if (records[speedLevel] > 0){
		printf("                     Best result on level %d: ", speedLevel + 1);
		SetConsoleTextAttribute(hConsole, SCORE);
		printf("%2d", Stats[speedLevel][0].Score);
		SetConsoleTextAttribute(hConsole, HEADER);
		printf(" (%s)", Stats[speedLevel][0].Name);
	}
	else printf("                    No results on this level yet.");

}

