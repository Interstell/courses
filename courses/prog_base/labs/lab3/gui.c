#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include "strings.h"
#include <math.h>
void JumpTo(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}
void printRect(int x1, int y1, int x2, int y2, char border, int color){
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x1;
	pos.Y = y1;
	SetConsoleTextAttribute(hConsole, color);
	for (pos.X; pos.X <= x2; pos.X++){
		for (pos.Y; pos.Y <= y2; pos.Y++){
			JumpTo(pos.X, pos.Y);
			if ((pos.X == x1) || (pos.X == x2) || (pos.Y == y1) || (pos.Y == y2)){
				printf("%c", border);
			}
			else printf(" ");
		}
		pos.Y = y1;
	}
}
void printIntro(char* string){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info, lastinfo, prevlastinfo;
	int input = 0, i = 0, curY = 12, maxX = 71, arrow = 0, wasInput = 0;
	printRect(14, 4, 64, 7, '*', 91);
	JumpTo(15, 5);
	SetConsoleTextAttribute(hConsole, 94);
	printf("                Strings Processor");
	JumpTo(15, 6);
	printf("         Created by Urukov Dmitry KP-52");
	printRect(6, 10, 72, 30, 178, 46);
	JumpTo(8, 11);
	SetConsoleTextAttribute(hConsole, 43);
	printf("Type your string and press Enter:");
	SetConsoleTextAttribute(hConsole, 46);
	JumpTo(8, 12);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lastinfo);
	while (input != 13){
		input = getch();
		if (input == 8){
			i--;
			string[i] = '\0';
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
			if (info.dwCursorPosition.X == 8 && info.dwCursorPosition.Y == 12) continue;
			else if (info.dwCursorPosition.X == 8){
				JumpTo(70, curY - 1);
				curY--;
			}
			else JumpTo(info.dwCursorPosition.X - 1, curY);
			printf("%s", " ");
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
			if (info.dwCursorPosition.X == 8 && info.dwCursorPosition.Y == 12) continue;
			else if (info.dwCursorPosition.X == 8){
				JumpTo(71, curY - 1);
				curY--;
			}
			else JumpTo(info.dwCursorPosition.X - 1, curY);
			continue;
		}

		if (input != 13){
			if (input == 224){
				arrow = 1;
			}
			else if ((arrow) && ((input == 75) || (input == 77) || (input == 72) || (input == 80))){
				arrow = 0;
				if ((input == 75) && (strlen(string)>0)){
					if (wasInput){
						JumpTo(lastinfo.dwCursorPosition.X + 1, lastinfo.dwCursorPosition.Y);
						wasInput = 0;
					}
					else JumpTo(lastinfo.dwCursorPosition.X, lastinfo.dwCursorPosition.Y);
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lastinfo);
					lastinfo.dwCursorPosition.X--;
					i--;
				}
				else if ((input == 77) && (i<strlen(string))){
					if (wasInput){
						JumpTo(lastinfo.dwCursorPosition.X + 2, lastinfo.dwCursorPosition.Y);
						wasInput = 0;
					}
					else JumpTo(lastinfo.dwCursorPosition.X, lastinfo.dwCursorPosition.Y);
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lastinfo);
					lastinfo.dwCursorPosition.X++;
					i++;
				}
			}
			else {
				string[i] = input;
				prevlastinfo = lastinfo;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lastinfo);
				wasInput = 1;
				lastinfo.dwCursorPosition.X--;
				printf("%c", string[i]);
				i++;
			}
		}
		if (strlen(string) % 63 == 0){
			curY++;
			JumpTo(8, curY);
		}
	}
}

void printMainString(char* str, int blink){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	int strJumper = 2;
	printRect(1, 1, 78, 4 + strlen(str) / 74 + 1, 177, 46);
	SetConsoleTextAttribute(hConsole, 43);
	JumpTo(33, 1);
	printf("|MAIN STRING|");
	SetConsoleTextAttribute(hConsole, 46);
	JumpTo(3, strJumper);
	for (int i = 0; i < strlen(str); i++){
		if (i % 74 == 0) {
			strJumper++;
			JumpTo(3, strJumper);
		}
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		SetConsoleTextAttribute(hConsole, rand() % 6 + 42);
		printf("%c", str[i]);
		if (blink) Sleep(14 - ((strlen(str) >= 150) ? 14 : strlen(str) / 10));
		JumpTo(info.dwCursorPosition.X, info.dwCursorPosition.Y);
		SetConsoleTextAttribute(hConsole, 46);
		printf("%c", str[i]);
	}
	Beep(550, 200);
}
void changeSize(){
	COORD crd = { 80, 35 };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hConsole, 1, &src);
	SetConsoleScreenBufferSize(hConsole, crd);
}
void printInputField(char* string){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	JumpTo(3, 7 + strlen(string) / 74);
	SetConsoleTextAttribute(hConsole, 10);
	printf(">>> ");
}
void refreshScreen(char* string, int blink, int color, char* message, int beepFq){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	if (strcmp(message, "") != 0){
		printf(" %s", message);
		Beep(beepFq, 200);
		getch();
	}
	system("cls");
	printMainString(string, blink);
	printInputField(string);
}
int executeCmd(char* cmd, char* string, int Ypos){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *actionNattribute[2], copy[1000];
	const int errorColor = 12, goodColor = 11;
	int wordsNum = 0, maxIndex = 0, maxLength = 0;
	char substr[1000] = "";
	char* words[500];
	char* helpDef[13] = { "               Erase the string", "          Fill string of %N% length with random letters", "        Enter new %STRING%", "    Enter new %STRING% and turn it vice versa", "               Get a list of the words of the string", "            Get the number of words in the string", "             Get the longest word and its length", "              Get the length of the string", " Get number of entries of %SUBSTRING% into main string", "          Get the number of letters in the string", "            Erase odd spaces", "     Raise the fraction in the string to the %EXP% power", "                Exit from the program" };
	char* helpCmd[13] = { "erase", "random %N%", "new %STRING%", "newFlip %STRING%", "words", "wordsNum", "maxWord", "length", "entries %SUBSTRING%", "letters   ", "noSpaces", "expDouble %EXP%", "exit" };
	strcpy(copy, cmd);
	strcat(copy, " ");
	actionNattribute[0] = strtok(copy, " ");
	strToLower(actionNattribute[0]);
	if (strcmp(actionNattribute[0], "help\n") == 0 || strcmp(actionNattribute[0], "help") == 0){
		JumpTo(4, Ypos + 2);
		for (int i = 0; i < 13; i++){
			SetConsoleTextAttribute(hConsole, 10);
			printf("%s", helpCmd[i]);
			SetConsoleTextAttribute(hConsole, 14);
			printf("%s", helpDef[i]);
			JumpTo(4, Ypos + 3 + i);
		}
		SetConsoleTextAttribute(hConsole, 10);
		refreshScreen(string, 0, goodColor, "\n   Press any key to continue...", 700);
	}
	else if (strcmp(actionNattribute[0], "exit\n") == 0 || strcmp(actionNattribute[0], "exit") == 0) return -1;
	else if (strcmp(actionNattribute[0], "erase\n") == 0 || strcmp(actionNattribute[0], "erase") == 0){
		cleanStr(string);
		refreshScreen(string, 0, 0, "", 0);
	}
	else if (strcmp(actionNattribute[0], "random") == 0){
		actionNattribute[1] = strtok(NULL, " ");
		if (isIntNumber(actionNattribute[1])){
			cleanStr(string);
			if (!(atoi(actionNattribute[1]) >= 0 && atoi(actionNattribute[1]) < 1000)){
				refreshScreen(string, 0, errorColor, "\n Error! Function parameter limit is 1000.", 2750);
			}
			else {
				fillRandom(string, atoi(actionNattribute[1]));
				refreshScreen(string, 1, 0, "", 0);
			}
		}
		else refreshScreen(string, 0, errorColor, "\n Error! Wrong function parameter received.", 2750);
	}
	else if (strcmp(actionNattribute[0], "random\n") == 0) refreshScreen(string, 0, errorColor, "\n Error! No parameter received.", 2750);
	else if (strcmp(actionNattribute[0], "new") == 0){
		cleanStr(string);
		strcpy(string, cmd + strlen(actionNattribute[0]));
		*(string + strlen(string) - 1) = '\0';
		refreshScreen(string, 0, 0, "", 0);
	}
	else if (strcmp(actionNattribute[0], "new\n") == 0) refreshScreen(string, 0, errorColor, "\n Error! No parameter received.", 2750);
	else if (strcmp(actionNattribute[0], "newflip") == 0){
		cleanStr(string);
		strcpy(string, cmd + strlen(actionNattribute[0]));
		flipViceVersa(string);
		refreshScreen(string, 1, 0, "", 0);
	}
	else if (strcmp(actionNattribute[0], "newflip\n") == 0) refreshScreen(string, 0, errorColor, "\n Error! No parameter received.", 2750);
	else if (strcmp(actionNattribute[0], "words\n") == 0 || strcmp(actionNattribute[0], "words") == 0){
		getWords(string, words, &wordsNum);
		if (wordsNum == 0){
			refreshScreen(string, 0, errorColor, "\n Error! No words found in string.", 2750);
			return 0;
		}
		for (int i = 0; i < wordsNum; i++){
			*(words[i]) = tolower(*(words[i]));
			SetConsoleTextAttribute(hConsole, 11);
			printf(" %d) ", i + 1);
			SetConsoleTextAttribute(hConsole, 14);
			printf("%s\n", words[i]);
		}
		refreshScreen(string, 0, goodColor, "\n Press any key to continue...", 700);
	}
	else if (strcmp(actionNattribute[0], "wordsnum\n") == 0 || strcmp(actionNattribute[0], "wordsnum") == 0){
		getWords(string, words, &wordsNum);
		printf(" Words in the string:");
		SetConsoleTextAttribute(hConsole, errorColor);
		printf(" %d\n", wordsNum);
		refreshScreen(string, 0, goodColor, "\n Press any key to continue...", 700);
	}
	else if (strcmp(actionNattribute[0], "maxword\n") == 0 || strcmp(actionNattribute[0], "maxword") == 0){
		getWords(string, words, &wordsNum);
		if (wordsNum == 0){
			refreshScreen(string, 0, errorColor, "\n Error! No words found in string.", 2750);
			return 0;
		}
		getMaxWord(words, &maxIndex, &maxLength, wordsNum);
		*(words[maxIndex]) = tolower(*(words[maxIndex]));
		printf(" The longest word is \"");
		SetConsoleTextAttribute(hConsole, errorColor);
		printf("%s", words[maxIndex]);
		SetConsoleTextAttribute(hConsole, 14);
		printf("\" and its length is ");
		SetConsoleTextAttribute(hConsole, errorColor);
		printf("%d\n", maxLength);
		refreshScreen(string, 0, goodColor, "\n Press any key to continue...", 700);
	}
	else if (strcmp(actionNattribute[0], "length\n") == 0 || strcmp(actionNattribute[0], "length") == 0){
		printf(" Length of main string: ");
		SetConsoleTextAttribute(hConsole, errorColor);
		printf("%d\n", getLength(string));
		refreshScreen(string, 0, goodColor, "\n Press any key to continue...", 700);
	}
	else if (strcmp(actionNattribute[0], "entries") == 0){
		cleanStr(substr);
		actionNattribute[1] = strtok(NULL, " ");
		while (actionNattribute[1] != NULL){
			strcat(substr, actionNattribute[1]);
			strcat(substr, " ");
			actionNattribute[1] = strtok(NULL, " ");
		}
		*(substr + strlen(substr) - 2) = '\0';
		printf(" Number of entries of substring: ");
		SetConsoleTextAttribute(hConsole, errorColor);
		printf("%d\n", numOfEntry(string, substr));
		refreshScreen(string, 0, goodColor, "\n Press any key to continue...", 700);
	}
	else if (strcmp(actionNattribute[0], "entries\n") == 0) refreshScreen(string, 0, errorColor, "\n Error! No parameter received.", 2750);
	else if (strcmp(actionNattribute[0], "letters\n") == 0 || strcmp(actionNattribute[0], "letters") == 0){
		printf(" Letters in main string: ");
		SetConsoleTextAttribute(hConsole, errorColor);
		printf("%d\n", numOfAlphas(string));
		refreshScreen(string, 0, goodColor, "\n Press any key to continue...", 700);
	}
	else if (strcmp(actionNattribute[0], "nospaces\n") == 0 || strcmp(actionNattribute[0], "nospaces") == 0){
		deleteSpaces(string);
		refreshScreen(string, 1, 0, "", 0);
	}
	else if (strcmp(actionNattribute[0], "expdouble") == 0){
		actionNattribute[1] = strtok(NULL, " ");
		if (isIntNumber(actionNattribute[1])){
			double res = doubleToExp(string, atoi(actionNattribute[1]));
			if (res == sqrt(2)){
				refreshScreen(string, 0, errorColor, "\n Error! String does not contain fraction number or it is corrupted.", 2750);
				return 0;
			}
			SetConsoleTextAttribute(hConsole, errorColor);
			printf(" %s", string);
			SetConsoleTextAttribute(hConsole, 14);
			printf(" raised into power ");
			SetConsoleTextAttribute(hConsole, errorColor);
			printf("%d", atoi(actionNattribute[1]));
			SetConsoleTextAttribute(hConsole, 14);
			printf(" is ");
			SetConsoleTextAttribute(hConsole, errorColor);
			printf("%.2f\n", res);
			refreshScreen(string, 0, goodColor, "\n Press any key to continue...", 700);
		}
		else refreshScreen(string, 0, errorColor, "\n Error! Wrong function parameter received.", 2750);
	}
	else if (strcmp(actionNattribute[0], "expdouble\n") == 0) refreshScreen(string, 0, errorColor, "\n Error! No parameter received.", 2750);
	else refreshScreen(string, 0, errorColor, "\n Error! Unknown command.", 3500);
	return 0;
}