#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define _CRT_SECURE_NO_WARNINGS

#include "text.h"
int main(void){
	text_t text = text_create();
	text_addSentenceToEnd(text,"abcd");
	text_addSentenceByIndex(text, "efgh", 1);
	assert(text_getSentenceAmount(text) == 2);
	assert(strcmp(text_getSentence(text, 0), "abcd") == 0);
	text_addSentenceByIndex(text, "insertion", 1);
	assert(text_getSentenceAmount(text) == 3);
	assert(strcmp(text_getSentence(text, 2), "efgh") == 0);
	text_setSentenceByIndex(text, "change", 2);
	assert(strcmp(text_getSentence(text, 2),"change") == 0);
	text_deleteSentenceByIndex(text, 1);
	assert(text_getSentenceAmount(text) == 2);
	assert(strcmp(text_getSentence(text, 1),"change") == 0);
	assert(strcmp(text_getText(text),"abcd. change. ") == 0);
	text_setSentenceByIndex(text, "abcd + efgh = abcdefgh", 0);
	assert(text_getWordsAmountInText(text) == 4);
	text_remove(text);
}