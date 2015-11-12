#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
enum direct{UP=2,DOWN};
int toJump = 0;
int getColor(int x){
	int star = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int bg = 0, res = 0;
	switch (abs(x % 3)){
	case 0:
		bg = BACKGROUND_BLUE;
		break;
	case 1:
		bg = BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	case 2:
		bg = BACKGROUND_GREEN;
		break;
	}
	res = FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | star | bg;
	return res;
}
COORD diag(COORD pos, enum direct direction){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD jumper;
	int i;
	jumper.X = 0;
	jumper.Y = 0;
	while (1){
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, getColor(pos.X));
		printf("*");
		if (toJump == 0){ /*because my console jumps down on the 1st symbol in the down right corner*/
			toJump = 1;
			SetConsoleCursorPosition(hConsole, jumper);
			printf("");
		}
		SetConsoleCursorPosition(hConsole, pos);
		Sleep(8);
		if (direction == UP){
			if ((pos.X + 1 == 80) || (pos.Y - 1 == -1)) break;
			pos.X++;
			pos.Y--;
		}
		else if (direction == DOWN){
			if ((pos.X - 1 == -1) || (pos.Y + 1 == 25)) break;
			pos.X--;
			pos.Y++;
		}
	}
	return pos;
}

int main(void){
	int i;
	COORD pos;
	pos.X = 79;
	pos.Y = 24;
	for (i = 1; i <= 52; i++){
		pos = diag(pos,UP);
		if ((pos.X == 79) && (pos.Y != 0)){
			pos.Y--;
		}
		if (pos.Y == 0){
			pos.X--;
		}
		pos = diag(pos, DOWN);
		if ((pos.Y == 24) && (pos.X != 0)){
			pos.X--;
		}
		else if (pos.X == 0){
			pos.Y--;
		}
	}
	getchar();
	return EXIT_SUCCESS;
}