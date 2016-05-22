#include "nlp.h"

struct text_s{
	char* str;
	list_t* sentences;
};

struct sentence_s{
	char* str;
	list_t* words;
};


struct word_s{
	char* str;
};

text_t text_new(char* textSource){
	text_t text = malloc(sizeof(struct text_s));
	text->str = malloc((strlen(textSource) + 1) * sizeof(char));
	strcpy(text->str, textSource);
	text->sentences = list_new();
	return text;
}

void text_splitOnSentences(text_t self){
	char* copy = malloc((strlen(self->str) + 1)*sizeof(char));
	char* copyPointer = copy;
	strcpy(copy, self->str);
	char* pointer = strpbrk(copy, ".?!");
	while (pointer != NULL){                  
		char sign = pointer[0];
		copy[pointer - copy] = '\0';
		char sentence[500];
		sprintf(sentence, "%s%c", copy, sign);
		printf("%s\n", sentence);
		sentence_t sent = sentence_new(sentence);
		list_push_back(self->sentences, sent);
		sentence_splitOnWords(sent); //TODO!
		copy += pointer - copy + 1;
		while (!isalnum(abs(copy[0]))) copy++;
		pointer = strpbrk(pointer + 1, ".?!");
	}
	free(copyPointer);
}

void text_delete(text_t self){
	free(self->str);
	for (int i = 0; i < list_getSize(self->sentences); i++){
		sentence_delete(list_get(self->sentences, i));
	}
	list_free(self->sentences);
	free(self);
}

sentence_t sentence_new(char* str){
	sentence_t sentence = malloc(sizeof(struct sentence_s));
	sentence->str = malloc((strlen(str) + 1)*sizeof(char));
	strcpy(sentence->str, str);
	sentence->words = list_new();
	return sentence;
}

void sentence_delete(sentence_t self){
	free(self->str);
	for (int i = 0; i < list_getSize(self->words); i++){
		word_delete(list_get(self->words,i));
	}
	list_free(self->words);
	free(self);
}

void sentence_splitOnWords(sentence_t self){
	char* copy = malloc((strlen(self->str) + 1)*sizeof(char));
	
	char* copyPointer = copy;
	strcpy(copy, self->str);
	char * pch = strtok(copy, " ");
	while (pch != NULL){
		char pchCopy[500];
		strcpy(pchCopy, pch);
		if (!isalnum(abs(pchCopy[strlen(pchCopy) - 1]))){
			pchCopy[strlen(pchCopy) - 1] = '\0';
		}
		list_push_back(self->words, word_new(pchCopy));
		pch = strtok(NULL, " ");
	}
	free(copyPointer);
}

word_t word_new(char* str){
	word_t word = malloc(sizeof(struct word_s));
	word->str = malloc((strlen(str) + 1)*sizeof(char));
	strcpy(word->str, str);
	return word;
}

void word_delete(word_t self){
	free(self->str);
	free(self);
}

void text_printSentences(text_t self, FILE* outputStream){
	for (int i = 0; i < list_getSize(self->sentences); i++){
		fprintf(outputStream, "%s\n", ((sentence_t)list_get(self->sentences,i))->str);
	}
}

void text_printSentencesAndWords(text_t self, FILE* outputStream){
	for (int i = 0; i < list_getSize(self->sentences); i++){
		sentence_t sent = (sentence_t)list_get(self->sentences, i);
		fprintf(outputStream, "%s\n", sent->str);
		for (int j = 0; j < list_getSize(sent->words); j++){
			fprintf(outputStream, "\t%s\n", ((word_t)list_get(sent->words,j))->str);
		}
	}
}

int wordCompareFunction(const void * a, const void * b)
{
	char* wordA = (*(word_t*)a)->str;
	char* wordB = (*(word_t*)b)->str;
	if (strlen(wordA) == strlen(wordB))
		return strcmp(wordA, wordB);
	else return strlen(wordA) - strlen(wordB);
}

void text_sortUpperCaseStartingWordsAndPrint(text_t self, FILE* outputStream){
	int numOfWords = 0;
	for (int i = 0; i < list_getSize(self->sentences); i++){
		sentence_t sent = (sentence_t)list_get(self->sentences, i);
		numOfWords += list_getSize(sent->words);
	}
	word_t* wordArr = malloc(numOfWords*sizeof(struct word_s)); //I use array because I cannot sort the ADS I didn't write
	int count = 0;
	for (int i = 0; i < list_getSize(self->sentences); i++){
		sentence_t sent = (sentence_t)list_get(self->sentences, i);
		for (int j = 0; j < list_getSize(sent->words); j++){
			word_t word = (word_t)list_get(sent->words, j);
			if (isupper(abs(word->str[0]))){
				wordArr[count++] = word;
			}
		}
	}

	qsort(wordArr, count, sizeof(word_t), wordCompareFunction);

	for (int i = 0; i < count; i++){
		fprintf(outputStream, "%s\n", wordArr[i]->str, strlen(wordArr[i]->str));
	}

	free(wordArr);
}





