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
void printAxes(COORD centre, int shiftX, int shiftY){
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	pos.Y = centre.Y;
	if ((pos.Y >= 0) && (pos.Y <= 24)){
		for (pos.X = 79; pos.X >= 0; pos.X--){
			SetConsoleCursorPosition(hConsole, pos);
			if ((pos.X-shiftX) % 5 == 0) printf("+");
			else printf("-");
		}
	}
	pos.X = centre.X;
	if ((pos.X >= 0) && (pos.X <= 79)){
		for (pos.Y = 24; pos.Y >= 0; pos.Y--){
			SetConsoleCursorPosition(hConsole, pos);
			if ((pos.Y+shiftY) % 4 == 0) printf("+");
			else printf("|");
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
			prevDot.Y = (newDot.Y - prevDot.Y < 0) ? (prevDot.Y - 1) : (prevDot.Y + 1);
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
int func2(int x, int zoomX, int zoomY){
	zoomY+=10;
	if (zoomY < 0) zoomY = 0;
	return (pow(zoomX*x*0.1*0.5,2) - 3)*(0.05*zoomY);
}
int func1(int x, int zoomX, int zoomY){
	zoomX = zoomX + (zoomX - 10)*0.01;
	return (tan(pow(zoomX*x*0.1, 2)) + pow(sin(2 *x*zoomX*0.1), 2))*(0.5*0.1*zoomY);
}
void printLegend(void){
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
	printf(" Switch plot: ENTER|Axis move: WASD|ZOOM: Ctrl+WASD|Restart: SPACE|Exit: ESC");
}
void refreshScreen(COORD centre, int zoomX, int zoomY, int shiftX, int shiftY, int funcNum){
	COORD prevDot, newDot, legend;
	fillBg();
	printAxes(centre, shiftX, shiftY);
	if (funcNum == 1) prevDot = printDot(centre, -60, func1(-60, zoomX, zoomY));
	else prevDot = printDot(centre, -60, func2(-60, zoomX,zoomY));
	for (int i = -59; i <= 60; i++){
		if (funcNum==1) newDot = printDot(centre, i, func1(i, zoomX, zoomY));
		else newDot = printDot(centre, i, func2(i, zoomX, zoomY));
		printConnector(prevDot, newDot);
		prevDot = newDot;
	}
	printLegend();
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
	int btnInput, shiftX=0, shiftY=0, funcNum=1, zoomX=10, zoomY=10;
	printIntro();
	getch();
	refreshScreen(centre, zoomX, zoomY, 0, 0, funcNum);
	while (1){
		btnInput = getch();
		if (btnInput == 27) break;
		switch (btnInput) {
		case 32:
			zoomX = 10;
			zoomY = 10;
			shiftX = 0;
			shiftY = 0;
			centre.X = 40;
			centre.Y = 12;
			refreshScreen(centre, zoomX, zoomY, 0, 0, funcNum);
			break;
		case 13:
			funcNum = (funcNum == 1) ? 2 : 1;
			refreshScreen(centre, zoomX, zoomY, 0, 0, funcNum);
			break;
		case 230: // W - up
			centre = getNewCentre(centre, 0, 1);
			shiftY++;
			refreshScreen(centre, zoomX, zoomY, shiftX, shiftY, funcNum);
			break;
		case 235: // S - down
			centre = getNewCentre(centre, 0, -1);
			shiftY--;
			refreshScreen(centre, zoomX, zoomY, shiftX, shiftY, funcNum);
			break;
		case 162: // D - right
			centre = getNewCentre(centre, 1, 0);
			shiftX++;
			refreshScreen(centre, zoomX, zoomY, shiftX, shiftY, funcNum);
			break;
		case 228: // A - left
			centre = getNewCentre(centre, -1, 0);
			shiftX--;
			refreshScreen(centre, zoomX, zoomY, shiftX, shiftY, funcNum);
			break;
		case 23: //Zoom Y+
			zoomY++;
			refreshScreen(centre, zoomX, zoomY, shiftX, shiftY, funcNum);
			break;
		case 19: //Zoom Y-
			zoomY--;
			refreshScreen(centre, zoomX, zoomY, shiftX, shiftY, funcNum);
			break;
		case 4: //Zoom X++
			zoomX++;
			refreshScreen(centre, zoomX, zoomY, shiftX, shiftY, funcNum);
			break;
		case 1: //Zoom X--
			zoomX--;
			refreshScreen(centre, zoomX, zoomY, shiftX, shiftY, funcNum);
			break;
		}
	}
	return 0;
}