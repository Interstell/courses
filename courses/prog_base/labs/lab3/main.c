#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include "strings.h"
#include <math.h>

int main(void){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	static char string[1000] = "";	
	char cmd[1000] = "";
	int exitCheck = 0;
	changeSize();
	printIntro(string);
	SetConsoleTextAttribute(hConsole, 0);
	system("cls");
	printMainString(string, 1);
	printInputField(string);
	while (!exitCheck){
		SetConsoleTextAttribute(hConsole, 14);
		fgets(cmd, 999, stdin);
		if ((strcmp(cmd, "") != 0)) exitCheck = executeCmd(cmd, string, 7 + strlen(string) / 74);
		cleanStr(cmd);
	}
	return 0;
}
