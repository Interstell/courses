#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nlp.h"

//ATTENTION!
//Variant: 19
// Залишити тільки слова, що починаються із великої літери. 
// Відсортувати їх у порядку зростання довжини слова в межах всього тексту 
// і записати кожне слово у окремому рядку вихідного файлу.

// RESULT IS IN "task.txt" 

int main(void){
	char book[15000];

	FILE* bookFile = fopen("book.txt", "r");
	fread(book, sizeof(char), 15000, bookFile);
	
	text_t text = text_new(book);
	text_splitOnSentences(text);

	FILE* sentFile = fopen("sentences.txt", "w");
	FILE* wordsFile = fopen("words.txt", "w");
	FILE* taskFile = fopen("task.txt", "w"); //RESULT IS HERE

	text_printSentences(text, sentFile);
	text_printSentencesAndWords(text, wordsFile);
	text_sortUpperCaseStartingWordsAndPrint(text, taskFile);
	text_delete(text);

	fclose(sentFile);
	fclose(wordsFile);
	fclose(taskFile);
	
	return EXIT_SUCCESS;
}