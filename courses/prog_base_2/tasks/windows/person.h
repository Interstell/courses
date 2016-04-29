#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>

typedef struct person_s* person_t;

person_t person_new(char* name, char* surname, int birthYear);
void person_free(person_t self);

char* person_getKey(person_t self);
char* person_getValue(person_t self);
void person_insertToList(person_t self, HWND hWndList);