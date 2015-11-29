#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifdef min
#undef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif
int main(void){
	char* input=(char*)malloc(1000*sizeof(char));
	char* cmp = (char*)malloc(3 * sizeof(char));
	char* cmp2 = (char*)malloc(3 * sizeof(char));
	gets(input);
	int *i = (int*)malloc(sizeof(int));
	*i = 0;
	for (*i; *i < strlen(input); (*i)++){
		if (isxdigit(input[*i])){
			cmp[0] = input[*i];
			break;
		}
	}
	*i = strlen(input) - 1;
	for (*i; (*i) >= 0; (*i)--){
		if (isxdigit(input[*i])){
			cmp[1] = input[*i];
			break;
		}
	}
	cmp2[0] = tolower(cmp[0]);
	cmp2[1] = tolower(cmp[1]);
	printf("%c", (min(cmp2[0], cmp2[1]) == cmp2[0]) ? cmp[0] : cmp[1]);
	free(input);
	free(cmp);
	free(cmp2);
	free(i);
	getchar();
	return EXIT_SUCCESS;
}