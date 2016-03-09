#include "text.h"

#define MAX_AMOUNT_OF_SENTENCES 30
#define MAX_SIZE_OF_SENTENCE 100

struct text_s{
	int amountOfSentences;
	enum STATUS status;
	char* sentences[MAX_AMOUNT_OF_SENTENCES];
};

text_t text_create(){
	text_t text = (text_t)malloc(sizeof(struct text_s));
	text->status = (text == NULL) ? NULL_POINTER : OK;
	text->amountOfSentences = 0;
	text->status = OK;
	return text;
}

void text_remove(text_t self){
	for (int i = 0; i < self->amountOfSentences; i++){
		free(self->sentences[i]);
	}
	free(self);
}

void text_addSentenceToEnd(text_t self, char* sentence){
	if (sentence == NULL){
		self->status = NULL_POINTER;
		return;
	}
	self->sentences[self->amountOfSentences] = (char*)malloc(MAX_SIZE_OF_SENTENCE*sizeof(char));
	strcpy(self->sentences[self->amountOfSentences], sentence);
	self->amountOfSentences++;
	self->status = OK;
}

char* text_getSentence(text_t self, int index){
	if (index > self->amountOfSentences - 1){
		self->status = INDEX_OUT_OF_BOUND;
		return "NULL";
	}
	self->status = OK;
	return self->sentences[index];
}

void text_setSentenceByIndex(text_t self, char* sentence, int index){
	if (index > self->amountOfSentences - 1 || index < 0){
		self->status = INDEX_OUT_OF_BOUND;
		return;
	}
	if (sentence == NULL){
		self->status = NULL_POINTER;
		return;
	}
	for (int i = strlen(self->sentences[index]); i >= strlen(sentence) - 1; i--){
		self->sentences[index][i] = '\0';
	}
	strcpy(self->sentences[index], sentence);
	self->status = OK;
}

int text_getSentenceAmount(text_t self){
	self->status = OK;
	return self->amountOfSentences;
}

static void strclean(char* str){
	int len = strlen(str);
	for (int i = strlen(str) - 1; i >= 0; i--){
		str[i] = '\0';
	}
}

void text_addSentenceByIndex(text_t self, char* sentence, int index){
	if (index > self->amountOfSentences || index < 0){
		self->status = INDEX_OUT_OF_BOUND;
		return;
	}
	if (sentence == NULL){
		self->status = NULL_POINTER;
		return;
	}
	self->sentences[self->amountOfSentences] = (char*)malloc(MAX_SIZE_OF_SENTENCE*sizeof(char));
	self->amountOfSentences++;
	for (int i = self->amountOfSentences - 1; i > index; i--){
		memcpy(self->sentences[i], self->sentences[i - 1], MAX_SIZE_OF_SENTENCE*sizeof(char));
	}
	strclean(self->sentences[index]);
	strcpy(self->sentences[index], sentence);
	self->status = OK;
}

char* text_getText(text_t self){
	static char text[MAX_SIZE_OF_SENTENCE*MAX_AMOUNT_OF_SENTENCES];
	strclean(text);
	for (int i = 0; i < self->amountOfSentences; i++){
		strcat(text, self->sentences[i]);
		if (text[strlen(text)-1] != '.') strcat(text, ".");
		strcat(text, " ");
	}
	self->status = OK;
	return text;
}

void text_deleteSentenceByIndex(text_t self, int index){
	if (index >= self->amountOfSentences || index < 0){
		self->status = INDEX_OUT_OF_BOUND;
		return;
	}
	for (int i = index; i < self->amountOfSentences - 1; i++){
		memcpy(self->sentences[i], self->sentences[i + 1], MAX_SIZE_OF_SENTENCE*sizeof(char));
	}
	free(self->sentences[self->amountOfSentences - 1]);
	self->amountOfSentences--;
	self->status = OK;
}

int text_getWordsAmountInText(text_t self){
	char* text = text_getText(self);
	char delim[72] = "\x1\x2\x3\x4\x5\x6\a\b\t\n\v\f\r\xe\xf\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&'()*+,-./0123456789:;<=>?@[\\]^_`{|";
	text = strtok(text, delim);
	int count = 0;
	while (text != NULL){
		count++;
		text = strtok(NULL, delim);
	}
	self->status = OK;
	return count;
}

enum STATUS text_getStatus(text_t self){
	return self->status;
}