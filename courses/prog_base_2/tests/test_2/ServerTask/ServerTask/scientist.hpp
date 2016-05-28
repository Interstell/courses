#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C"{
#include "list.h"
}
#include <jansson\jansson.h>

struct scientist_s{
	int Id;
	char Surname[50];
	char Name[50];
	char BirthDate[20];
	double Quotation_index;
	int Books;
};

typedef struct scientist_s* scientist_t;

scientist_t scientist_new(int Id, char* Surname, char* Name, char* BirthDate, double Quotation_index, int Books);
void scientist_delete(scientist_t self);
void scientist_delete_void(void* self);
json_t* scientist_serializeListToJson(list_t* list);
