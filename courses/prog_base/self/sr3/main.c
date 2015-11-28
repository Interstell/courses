#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
	FILE* fr = fopen("input.txt", "r");
	char exp[1000];
	char copy[1000];
	char punct, punct2;
	char punctuation[100];
	char *expDiv[100];
	int ResSum = 0;
	int expPointer = 2, signpos = 0;
	if (fr == NULL) return EXIT_FAILURE;
	fgets(exp, 1000, fr);
	fclose(fr);
	strcpy(copy, exp);
	expDiv[0] = strtok(copy, "+*");
	while (expDiv[expPointer - 2] != NULL)
	{
		expDiv[expPointer] = strtok(NULL, "+*");
		
		expPointer+=2;
	}
	expPointer = 1;
	for (int i = 0; i < strlen(exp); i++){
		if (exp[i] == '+') {
			expDiv[expPointer] = "+";
			expPointer += 2;
		}
		else if (exp[i] == '*'){
			expDiv[expPointer] = "*";
			expPointer += 2;
		}
	}

	for (int i = 0; i < expPointer; i++){
		if (strcmp(expDiv[i], "*") == 0){
			int n1 = atoi(expDiv[i - 1]);
			int n2 = atoi(expDiv[i + 1]);
			int sum = n1 * n2;
			char res[20];
			sprintf(res, "%d", sum);
			strcpy(expDiv[i - 1], res);
			expDiv[i] = "+";
			expDiv[i + 1] = "0";
		}
	}
	for (int i = 0; i < expPointer; i++){
		if (strcmp(expDiv[i], "+") != 0){
			ResSum += atoi(expDiv[i]);
		}
	}
	printf("%s = %d", exp, ResSum);
	getchar();
	return 0;
}