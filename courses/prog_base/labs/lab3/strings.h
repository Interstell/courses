#ifndef __INC_STRINGS
#define __INC_STRINGS

void fillRandom(char* string, int n);
void flipViceVersa(char* string);
void getWords(char* string, char* words[], int* wNum);
void getMaxWord(char* words[], int* maxIndex, int* maxLength, int wordsNum);
int getLength(char* string);
int numOfEntry(char* str, char* substr);
int numOfAlphas(char* str);
void shiftLeft(char* substr);
void deleteSpaces(char* str);
int isRealZero(char* str);
int isRealNumber(char* str);
double doubleToExp(char* str, int exp);
void cleanStr(char* str);
void strToLower(char* str);

#endif