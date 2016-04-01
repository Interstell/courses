#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jansson\jansson.h"

#define MAX_NUM_OF_DEGREES 5
#define MAX_NUM_OF_SCIENTISTS_IN_FILE 10

typedef struct scientists_s* scientists_t;

typedef struct degree_s{
	char degreeName[50];
	char achievingDate[20];
	char thesisName[70];
} degree_t;


scientists_t scientists_new(void);
void scientists_delete(scientists_t scientists);

int scientists_parseFromJsonFile(scientists_t self, char* fileName);
int scientists_amount(scientists_t self);

void scientists_printByIndex(scientists_t self, int index);

char * scientists_getFirstName(scientists_t self, int index);
char * scientists_getSurname(scientists_t self, int index);
char * scientists_getFathersName(scientists_t self, int index);
char * scientists_getBirthDate(scientists_t self, int index);
char * scientists_getScienceDomain(scientists_t self, int index);
int scientists_getAmountOfDegrees(scientists_t self, int index);
degree_t* scientists_getAcademicDegrees(scientists_t self, int index);
double scientists_getQuotationIndex(scientists_t self, int index);
double scientists_getHirschIndex(scientists_t self, int index);
int scientists_getNumOfScientificStudies(scientists_t self, int index);
int scientists_getNumOfPatents(scientists_t self, int index);

