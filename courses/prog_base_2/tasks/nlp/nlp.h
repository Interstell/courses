#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SENTENCES_IN_TEXT 1000
#define MAX_WORDS_IN_SENTENCE 100

typedef struct text_s* text_t;
typedef struct sentence_s* sentence_t;
typedef struct word_s* word_t;

text_t text_new(char* textSource);
void text_delete(text_t self);
void text_splitOnSentences(text_t self);
void text_printSentences(text_t self, FILE* outputStream);
void text_printSentencesAndWords(text_t self, FILE* outputStream);
void text_sortUpperCaseStartingWordsAndPrint(text_t self, FILE* outputStream);

sentence_t sentence_new(char* str);
void sentence_delete(sentence_t self);
void sentence_splitOnWords(sentence_t self);

word_t word_new(char* str);
void word_delete(word_t self);



