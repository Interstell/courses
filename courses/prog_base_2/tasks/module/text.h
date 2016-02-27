#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct text_s* text_t;
enum STATUS{
	OK = 1,
	NULL_POINTER,
	INDEX_OUT_OF_BOUND
};

text_t text_create(void);
void text_remove(text_t self);

void text_addSentenceToEnd(text_t self, char* sentence);
void text_addSentenceByIndex(text_t self, char* sentence, int index); 
void text_setSentenceByIndex(text_t self, char* sentence, int index);
void text_deleteSentenceByIndex(text_t self, int index); 

char* text_getSentence(text_t self, int index); 
char* text_getText(text_t self); 
int text_getSentenceAmount(text_t self);
int text_getWordsAmountInText(text_t self); 


