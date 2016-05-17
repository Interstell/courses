#include "nlp.h"

struct text_s{
	char* str;
	int numOfSentences;
	sentence_t sentences[MAX_SENTENCES_IN_TEXT];
};

struct sentence_s{
	char* str;
	int numOfWords;
	word_t words[MAX_WORDS_IN_SENTENCE];
};


struct word_s{
	char* str;
};

text_t text_new(char* textSource){
	text_t text = malloc(sizeof(struct text_s));
	text->str = malloc((strlen(textSource) + 1) * sizeof(char));
	text->numOfSentences = 0;
	strcpy(text->str, textSource);
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
		self->sentences[self->numOfSentences] = sentence_new(sentence);
		sentence_splitOnWords(self->sentences[self->numOfSentences++]);
		copy += pointer - copy + 1;
		while (!isalnum(abs(copy[0]))) copy++;
		pointer = strpbrk(pointer + 1, ".?!");
	}
	free(copyPointer);
}

void text_delete(text_t self){
	free(self->str);
	for (int i = 0; i < self->numOfSentences; i++){
		sentence_delete(self->sentences[i]);
	}
	free(self);
}

sentence_t sentence_new(char* str){
	sentence_t sentence = malloc(sizeof(struct sentence_s));
	sentence->str = malloc((strlen(str) + 1)*sizeof(char));
	strcpy(sentence->str, str);
	sentence->numOfWords = 0;
	return sentence;
}

void sentence_delete(sentence_t self){
	free(self->str);
	for (int i = 0; i < self->numOfWords; i++){
		word_delete(self->words[i]);
	}
	free(self);
}

void sentence_splitOnWords(sentence_t self){
	char* copy = malloc((strlen(self->str) + 1)*sizeof(char));
	char* copyPointer = copy;
	strcpy(copy, self->str);
	char * pch = strtok(copy, " ");
	while (pch != NULL){
		self->words[self->numOfWords] = word_new(pch);
		if (!isalnum(abs(self->words[self->numOfWords]->str[strlen(self->words[self->numOfWords]->str) - 1]))){
			self->words[self->numOfWords]->str[strlen(self->words[self->numOfWords]->str) - 1] = '\0';
		}
		self->numOfWords++;
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
	for (int i = 0; i < self->numOfSentences; i++){
		fprintf(outputStream, "%s\n", self->sentences[i]->str);
	}
}

void text_printSentencesAndWords(text_t self, FILE* outputStream){
	for (int i = 0; i < self->numOfSentences; i++){
		fprintf(outputStream, "%s\n", self->sentences[i]->str);
		for (int j = 0; j < self->sentences[i]->numOfWords; j++){
			fprintf(outputStream, "\t%s\n", self->sentences[i]->words[j]->str);
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
	for (int i = 0; i < self->numOfSentences; i++){
		numOfWords += self->sentences[i]->numOfWords;
	}
	word_t* wordArr = malloc(numOfWords*sizeof(struct word_s));
	int count = 0;
	for (int i = 0; i < self->numOfSentences; i++){
		for (int j = 0; j < self->sentences[i]->numOfWords; j++){
			if (isupper(abs(self->sentences[i]->words[j]->str[0]))){
				wordArr[count++] = self->sentences[i]->words[j];
			}
		}
	}

	qsort(wordArr, count, sizeof(word_t), wordCompareFunction);

	for (int i = 0; i < count; i++){
		fprintf(outputStream, "%s\n", wordArr[i]->str, strlen(wordArr[i]->str));
	}

	free(wordArr);
}





