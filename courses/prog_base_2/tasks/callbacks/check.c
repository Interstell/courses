#include "check.h"

static void reverseString(char* string){
	int len = strlen(string);
	for (int i = 0; i < len / 2; i++){
		char t = string[i];
		string[i] = string[len - 1 - i];
		string[len - 1 - i] = t;
	}
}

static void setColor(enum COLORS color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void containsCB1(char* bigStr, char*smallStr, int index){
	for (int i = 0; i < index; i++){
		printf("%c", bigStr[i]);
	}
	setColor(RED);
	printf("%s", smallStr);
	setColor(BLACK);
	for (int i = index + strlen(smallStr); i < strlen(bigStr); i++){
		printf("%c", bigStr[i]);
	}
	printf("\n");
}

void containsCB2(char* bigStr, char*smallStr, int index){
	if (strstr(bigStr, smallStr) - bigStr == index){
		for (int i = 0; i < index; i++)
			printf("%c", bigStr[i]);
		int nextPtr = strstr(bigStr + index + 1, smallStr) - bigStr;
		if (nextPtr < 0){
			printf("%s", bigStr + index + strlen(smallStr));
		}
		else {
			for (int i = index + strlen(smallStr); i < nextPtr; i++){
				printf("%c", bigStr[i]);
			}
		}
		return;
	}
	int nextIndex = strstr(bigStr + index + 1, smallStr) - bigStr;
	if (nextIndex < 0){
		printf("%s", bigStr + index + strlen(smallStr));
	}
	else {
		for (int i = index + strlen(smallStr); i < nextIndex; i++)
			printf("%c", bigStr[i]);
	}
}

void reversedCB1(char* bigStr, char*smallStr, int index){
	for (int i = 0; i < index; i++){
		printf("%c", bigStr[i]);
	}
	setColor(YELLOW);
	printf("%s", smallStr);
	setColor(BLACK);
	for (int i = index + strlen(smallStr); i < strlen(bigStr); i++){
		printf("%c", bigStr[i]);
	}
	printf("\n");
}

void reversedCB2(char* bigStr, char*smallStr, int index){
	if (strstr(bigStr, smallStr) - bigStr == index){
		for (int i = 0; i < index; i++)
			printf("%c", bigStr[i]);
		int nextPtr = strstr(bigStr + index + 1, smallStr) - bigStr;
		if (nextPtr < 0){
			printf("|%s", bigStr + index + strlen(smallStr));
		}
		else {
			printf("%c", '|');
			for (int i = index + strlen(smallStr); i < nextPtr; i++){
				printf("%c", bigStr[i]);
			}
		}
		return;
	}
	int nextIndex = strstr(bigStr + index + 1, smallStr) - bigStr;
	if (nextIndex < 0){
		printf("|%s", bigStr + index + strlen(smallStr));
	}
	else {
		printf("%c", '|');
		for (int i = index + strlen(smallStr); i < nextIndex; i++){
			printf("%c", bigStr[i]);
		}
	}
}

int check(char* bigStr, char* smallStr, checkCallback containsCB, checkCallback reversedCB){
	int ptrPos = 0;
	char* ptr;
	if (NULL == containsCB || NULL == reversedCB) return -1;
	printf("String: %s\n", bigStr);
	printf("SubString: %s\n", smallStr);
	while ((ptr = strstr(bigStr + ptrPos, smallStr)) != NULL){
		ptrPos = ptr - bigStr;
		containsCB(bigStr, smallStr, ptrPos++);
	}
	printf("\n");
	reverseString(smallStr);
	ptrPos = 0;
	while ((ptr = strstr(bigStr + ptrPos, smallStr)) != NULL){
		ptrPos = ptr - bigStr;
		reversedCB(bigStr, smallStr, ptrPos++);
	}
	reverseString(smallStr);
	//yes, we can move those two similar "while"s into another callback, but the task is the task.
	return 0;
}