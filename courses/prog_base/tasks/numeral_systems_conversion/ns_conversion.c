#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int charToNumber(char c){
	if (c >= 48 && c <= 57) return c - 48;
	else return c - 55;
}
char numberToChar(int n){
	if (n >= 0 && n <= 9) return n + 48;
	else return n + 55;
}
int IsExistInThisSystem(char* num, unsigned int sourceBase){
	for (int i = 0; i < strlen(num); i++){
		if ((charToNumber(num[i])>sourceBase - 1)&&(num[i]!='.')) return 0;
	}
	return 1;
}
int IsCorrectFormat(char* num){
	int nDots = 0;
	for (int i = 0; i < strlen(num); i++){
		if (num[i] == '.') nDots++;
		else if (num[i] == ' ') return 0;
		else if (!(isalpha(num[i]) || isdigit(num[i]))) return 0;
	}
	if (nDots > 1) return 0;
	if (strlen(num) == nDots) return 0;
	return 1;
}
int IsValid(char* num, int sourceBase){
	return (IsCorrectFormat(num) && IsExistInThisSystem(num, sourceBase));
}
void Split(char* num, char* integral, char* fractional){
	char copy[200];
	strcpy(copy, num);
	for (int i = 0; i < strlen(num); i++){
		if (num[i] == '.'){
			strcpy(fractional, num + i + 1);
			copy[i] = '\0';
			strcpy(integral, copy);
			return;
		}
	}
	strcpy(integral, num);
}
double StrToDecimal(char* integral, char* fractional, unsigned int sourceBase){
	double res = 0;
	int i, j;
	for (i = strlen(integral) - 1, j = 0; i >= 0; i--, j++){
		res += charToNumber(integral[i])*pow(sourceBase, j);
	}
	for (i = 0, j = -1; i < strlen(fractional); i++, j--){
		res += pow(sourceBase, j)*charToNumber(fractional[i]);
	}
	return res;
}
void flipViceVersa(char* string){ 
	char t;
	for (int i = 0; i < strlen(string) / 2; i++){
		t = string[i];
		string[i] = string[strlen(string) - i - 1];
		string[strlen(string) - i - 1] = t;
	}
}
void DecimalToDest(double decimal, unsigned int destBase, char* res){
	int integral=(int)decimal;
	int i = 0;
	double fractional=decimal - integral;
	while (integral>destBase){
		res[i] = numberToChar(integral%destBase);
		integral = (integral - integral%destBase) / destBase;
		i++;
	}
	res[i] = numberToChar(integral%destBase);
	flipViceVersa(res);
	if (fractional != 0){
		res[i + 1] = '.';
		i += 2;
		for (int j = 0; j < 12; j++){
			fractional = fractional*destBase;
			res[i] = numberToChar((int)fractional);
			fractional = fractional - (int)fractional;
			i++;
		}
	}
}
void cleanStr(char* str, int len){
	for (int i = len - 1; i >= 0; i--){
		str[i] = '\0';
	}
}
char* ns_convert(char* number, unsigned int sourceBase, unsigned int destBase){
	static char res[300] = "";
	char integral[300]="";
	char fractional[300]="";
	double decimal;
	cleanStr(res, strlen(res));
	if (!IsValid(number, sourceBase)) return "\0";
	Split(number, integral, fractional);
	decimal = StrToDecimal(integral, fractional, sourceBase);
	DecimalToDest(decimal, destBase, res);
	return res;
}
