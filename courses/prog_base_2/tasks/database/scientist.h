#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct scientist_s{
	char Surname[50];
	char Name[50];
	char Fathers[50];
	char BirthDate[20];
	double Quotation_index;
	int Science_works;
	int Books;
};

typedef struct scientist_s* scientist_t;

scientist_t scientist_new(char* Surname, char* Name, char* Fathers, char* BirthDate, double Quotation_index, int Science_works, int Books);
void scientist_delete(scientist_t self);
void scientist_print(scientist_t self);
