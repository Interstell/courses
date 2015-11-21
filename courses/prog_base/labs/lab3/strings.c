#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
void fillRandom(char* string, int n){
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++){
		string[i] = rand() % 94 + 33;
	}
}
void flipViceVersa(char* string){ //Змінити строку на нововведену користувачем у зворотньому порядку. ПЕРЕПИСАТЬ
	char t;
	*(string+strlen(string)-1) = '\0';
	for (int i = 0; i < strlen(string) / 2 ; i++){
		t = string[i];
		string[i] = string[strlen(string) - i - 1];
		string[strlen(string) - i - 1] = t;
	}
}
void getWords(char* string, char* words[], int* wNum){ //Вивести всі слова у строці ( //Вивести кількість слів у строці
	static char copy[1000];
	int word = 1;
	strcpy(copy, string);
	for (int i = 0; i < strlen(string); i++){
		if (!(((copy[i] >= 65) && (copy[i] <= 90)) || ((copy[i] >= 97) && (copy[i] <= 122)))) //only letters, no numbers?
			copy[i] = '*';
	}
	words[0] = strtok(copy, "*");

	while (words[word - 1] != NULL)
	{
		words[word] = strtok(NULL, "*");
		word++;
	}
	*wNum = word - 1;
}
void getMaxWord(char* words[], int* maxIndex, int* maxLength, int wordsNum){ //Вивести найдовше зі слів і його довжину
	char tmpWord[1000];
	for (int i = 0; i < wordsNum; i++){
		strcpy(tmpWord, words[i]);
		if (strlen(tmpWord)>*maxLength){
			*maxLength = strlen(tmpWord);
			*maxIndex = i;
		}
	}
}
int getLength(char* string){ //Вивести довжину строки
	return strlen(string);
}
int numOfEntry(char* str, char* substr){ //Вивести кількість входжень введеної строки у робочу строку
	int res = 0, pointer = 0;
	while (strstr(str + pointer, substr) != NULL){
		res++;
		pointer = (strstr(str + pointer, substr) + strlen(substr)) - str;
	}
	return res;
}
int numOfAlphas(char* str){ //Вивести кількість буквенних символів строки
	int res = 0;
	for (int i = 0; i < strlen(str); i++){
		if (isalpha(str[i])) res++;
	}
	return res;
}
void shiftLeft(char* substr){
	for (int i = 0; i < strlen(substr) - 1; i++){
		substr[i] = substr[i + 1];
	}
	substr[strlen(substr) - 1] = '\0';
}
void deleteSpaces(char* str){ //Видалити зі строки лишні пробіли
	for (int i = 1; i < strlen(str); i++){
		if ((str[i - 1] == ' ') && (str[i] == ' ')){
			shiftLeft(str + i);
			i--;
		}
	}
}
int isRealZero(char* str){
	int nDots = 0, nZeros = 0;
	if ((str[0] == '0') && (strlen(str) == 1)) return 1;
	for (int i = 0; i < strlen(str); i++){
		if (str[i] == '0') nZeros++;
		else if (str[i] == '.') nDots++;
	}
	if ((nDots == 1) && (strlen(str) - nZeros == 1) && (str[strlen(str) - 1] == '0')) return 1;
	else return 0;
}
int isRealNumber(char* str){
	int res = 1, nDots = 0;
	if (str[strlen(str)-1] == '\n') str[strlen(str)-1] = '\0';
	//deleteSpaces(str);
	for (int i = 0; i < strlen(str); i++){
		if (!((isdigit(str[i])) || (str[i] == '.') || (str[i]==' '))) res = 0;
		//if (!((isdigit(str[i])) || (str[i] == '.'))) res = 0;
		if (str[i] == '.') nDots++;
	}
	if (nDots != 1) res = 0;
	return res;
}
int isIntNumber(char* str){
	for (int i = 0; i < strlen(str); i++){
		if (!((isdigit(str[i])||(str[i]=='\n')))) return 0;
	}
	if (str[0] == '\n') return 0;
	return 1;
}
double doubleToExp(char* str, int exp){
	if (isRealNumber(str)) return pow(atof(str), exp);
	else if (isRealZero(str)) return 0;
	else return sqrt(2);
}
void cleanStr(char* str){
	for (int i = strlen(str) - 1; i >= 0; i--){
		str[i] = 0;
	}
}
void strToLower(char* str){
	for (int i = 0; i < strlen(str); i++){
		if (isupper(str[i])) str[i]=tolower(str[i]);
	}
}