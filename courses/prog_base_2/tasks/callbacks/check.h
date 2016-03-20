#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

enum COLORS{
	BLACK = 7,
	RED = 207,
	YELLOW = 224
};

typedef void(*checkCallback)(char* bigStr, char* smallStr, int index);

int check(char* bigStr, char* smallStr, checkCallback containsCB, checkCallback reversedCB);

void containsCB1(char* bigStr, char*smallStr, int index);
void containsCB2(char* bigStr, char*smallStr, int index);

void reversedCB1(char* bigStr, char*smallStr, int index);
void reversedCB2(char* bigStr, char*smallStr, int index);


