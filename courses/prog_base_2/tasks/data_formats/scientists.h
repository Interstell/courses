#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jansson\jansson.h"

#define MAX_NUM_OF_DEGREES 5
#define MAX_NUM_OF_SCIENTISTS_IN_FILE 10

typedef struct scientists_s* scientists_t;

scientists_t scientists_new(void);
void scientists_delete(scientists_t scientists);

int scientists_parseFromJsonFile(scientists_t self, char* fileName);
int scientists_amount(scientists_t self);

void scientists_printByIndex(scientists_t self, int index);
