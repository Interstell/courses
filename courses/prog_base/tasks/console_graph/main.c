#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
void fillBg(void){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	for (pos.X = 79; pos.X >= 0; pos.X--){
		for (pos.Y = 24; pos.Y >= 0; pos.Y--){
			SetConsoleCursorPosition(hConsole, pos);
			printf(" ");
		}
	}
}
COORD getNewCentre(COORD centre, int x, int y){
	centre.X += x;
	centre.Y -= y;
	return centre;
}
void printAxes(COORD centre, int shiftX, int shiftY, int zoom){
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	pos.Y = centre.Y;
	if ((pos.Y >= 0) && (pos.Y <= 24)){
		for (pos.X = 79; pos.X >= 0; pos.X--){
			SetConsoleCursorPosition(hConsole, pos);
			if (zoom <= 10){
				if ((pos.X - shiftX + 2) % (6 - (int)((zoom - 10)*0.2)) == 0) printf("+");
				else printf("-");
			}
			else {
				if ((pos.X - shiftX + 2) % (6 - (int)((zoom - 10)*0.2)) == 0) printf("+");
				else printf("-");
			}
		}
	}
	pos.X = centre.X;
	if ((pos.X >= 0) && (pos.X <= 79)){
		for (pos.Y = 24; pos.Y >= 0; pos.Y--){
			SetConsoleCursorPosition(hConsole, pos);
			if (zoom <= 10){
				if ((pos.Y - shiftY + 3) % (5 - (int)((zoom - 10)*0.2)) == 0) printf("+");
				else printf("|");
			}
			else {
				if ((pos.Y - shiftY + 3) % (5 + (int)((zoom - 10)*0.2)) == 0) printf("+");
				else printf("|");
			}
		}
	}
}
COORD printDot(COORD center, int x, int y){
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	pos.X = center.X + x;
	pos.Y = center.Y - y;
	if ((pos.X >= 0) && (pos.X <= 79) && (pos.Y >= 0) && (pos.Y <= 24)){
		SetConsoleCursorPosition(hConsole, pos);
		printf(" ");
	}
	return pos;
}
COORD printConnector(COORD prevDot, COORD newDot){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	if (abs(newDot.Y - prevDot.Y) > 1){
		if (newDot.Y > prevDot.Y){ 
			prevDot.X += newDot.X - prevDot.X;
			while (prevDot.Y != newDot.Y){
				if ((prevDot.X >= 0) && (prevDot.X <= 79) && (prevDot.Y >= 0) && (prevDot.Y <= 24)){
					SetConsoleCursorPosition(hConsole, prevDot);
					printf(" ");
				}
				prevDot.Y = (newDot.Y - prevDot.Y < 0) ? (prevDot.Y - 1) : (prevDot.Y + 1);
			}
		}
		else if (newDot.Y < prevDot.Y){
			while (prevDot.Y != newDot.Y){
				if ((prevDot.X >= 0) && (prevDot.X <= 79) && (prevDot.Y >= 0) && (prevDot.Y <= 24)){
					SetConsoleCursorPosition(hConsole, prevDot);
					printf(" ");
				}
				prevDot.Y = (newDot.Y - prevDot.Y < 0) ? (prevDot.Y - 1) : (prevDot.Y + 1);
			}
			if ((prevDot.X >= 0) && (prevDot.X <= 79) && (prevDot.Y >= 0) && (prevDot.Y <= 24)){
				SetConsoleCursorPosition(hConsole, prevDot);
				printf(" ");
			}
		}
	}
}
int func2(int x, int zoom){
	if (zoom < 0) zoom = 0;
	return (-pow(zoom*x*0.1,2) + 3)*(0.1*zoom);
}
int func1(int x, int zoom){
	return (tan(pow(zoom*x*0.1, 2)) + pow(sin(2 *x*zoom*0.1), 2))*(0.1*zoom);
}
void printLegend(funcNum){
	COORD legend;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	legend.X = 1;
	legend.Y = 24;
	SetConsoleCursorPosition(hConsole, legend);
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (int i = 1; i < 79; i++){
		printf(" ");
	}
	SetConsoleCursorPosition(hConsole, legend);
	printf("Switch plot: ENTER | Axis move: WASD | ZOOM: + - | Restart: SPACE | Exit: ESC");
	legend.X = 0;
	legend.Y = 23;
	SetConsoleCursorPosition(hConsole, legend);
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	if (funcNum == 1) printf(" F(x)=tg(x^2)+sin(2*x)^2");
	else printf(" F(x)=-x^2+3");
}
void refreshScreen(COORD centre, int zoom, int shiftX, int shiftY, int funcNum){
	COORD prevDot, newDot, legend;
	fillBg();
	printAxes(centre, shiftX, shiftY, zoom);
	if (funcNum == 1) prevDot = printDot(centre, -60, func1(-60, zoom));
	else prevDot = printDot(centre, -60, func2(-60, zoom));
	for (int i = -59; i <= 60; i++){
		if (funcNum==1) newDot = printDot(centre, i, func1(i, zoom));
		else newDot = printDot(centre, i, func2(i, zoom));
		printConnector(prevDot, newDot);
		prevDot = newDot;
	}
	printLegend(funcNum);
}
void printIntro(void){
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fillBg();
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	for (pos.X=20; pos.X < 60; pos.X++){
		for (pos.Y=9; pos.Y < 17; pos.Y++){
			SetConsoleCursorPosition(hConsole, pos);
			if ((pos.X == 20) || (pos.X == 59) || (pos.Y == 9) || (pos.Y == 16)) printf("@");
			else printf(" ");
		}
	}
	pos.X = 21;
	pos.Y = 10;
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
	SetConsoleCursorPosition(hConsole, pos);
	printf("      Console Function Graphics");
	pos.Y++;
	SetConsoleCursorPosition(hConsole, pos);
	printf("   Performed by Dmitry Urukov KP-52");
	pos.Y+=2;
	SetConsoleCursorPosition(hConsole, pos);
	printf("       Press any key to start... ");
	pos.Y += 2;
	SetConsoleCursorPosition(hConsole, pos);
	printf("               KPI 2015 ");
}
int main(void){
	COORD centre = { 40, 12 };
	int btnInput, shiftX=0, shiftY=0, funcNum=2, zoom=10;
	printIntro();
	getch();
	refreshScreen(centre, zoom, 0, 0, funcNum);
	while (1){
		btnInput = getch();
		if (btnInput == 27) break;
		switch (btnInput) {
		case 32:
			zoom = 10;
			shiftX = 0;
			shiftY = 0;
			centre.X = 40;
			centre.Y = 12;
			refreshScreen(centre, zoom, 0, 0, funcNum);
			break;
		case 13:
			funcNum = (funcNum == 1) ? 2 : 1;
			refreshScreen(centre, zoom, 0, 0, funcNum);
			break;
		case 230: // W - up
			centre = getNewCentre(centre, 0, 1);
			shiftY++;
			refreshScreen(centre, zoom, shiftX, shiftY, funcNum);
			break;
		case 235: // S - down
			centre = getNewCentre(centre, 0, -1);
			shiftY--;
			refreshScreen(centre, zoom, shiftX, shiftY, funcNum);
			break;
		case 162: // D - right
			centre = getNewCentre(centre, 1, 0);
			shiftX++;
			refreshScreen(centre, zoom, shiftX, shiftY, funcNum);
			break;
		case 228: // A - left
			centre = getNewCentre(centre, -1, 0);
			shiftX--;
			refreshScreen(centre, zoom, shiftX, shiftY, funcNum);
			break;
		case 43: //Zoom +
			zoom--;
			refreshScreen(centre, zoom, shiftX, shiftY, funcNum);
			break;
		case 45: //Zoom -
			zoom++;
			refreshScreen(centre, zoom, shiftX, shiftY, funcNum);
			break;
		}
	}
	return 0;
}