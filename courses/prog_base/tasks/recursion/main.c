#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char lastHex(char* str, int num){
	if (isxdigit(str[num])) return str[num];
	else if ((!isxdigit(str[num])) && (num == 0)) return '0';
	else return lastHex(str, num - 1);
}
int main(void){
	char str[200];
	gets(str);
	printf("%c", lastHex(str, strlen(str) - 1));
	getchar();
	return EXIT_SUCCESS;
}