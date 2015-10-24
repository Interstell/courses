	
#include <stdio.h>
#include <stdlib.h>
void findUnique(char s1[100], char s2[100], int size){
	int i, j, foundFlag = 0, numOfUnique = 0;
	for (i = 0; i < size; i++){
		foundFlag = 0;
		for (j = 0; j < size; j++){
			if (s1[i] == s2[j]){
				foundFlag = 1;
			}
		}
		if (!foundFlag){
			if (numOfUnique == 0){
				printf("Unique symbols: ");
			}
			numOfUnique++;
			printf("%c ", s1[i]);
		}
	}
	printf("\nNum of unique symbols: %d \n", numOfUnique);
}
void findEqual(char s1[100], char s2[100], int size){
	int i, j, numOfSame = 0;
	printf("Equal symbols: ");
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (s1[i] == s2[j]){
				s2[j] = ' ';
				printf("%c ", s1[i]);
				numOfSame++;
			}
		}
	}
	printf("\nNum of equal symbols: %d", numOfSame);
}

int main(void){
	char s1[100], s2[100]; 
	gets_s(s1,100);
	gets_s(s2,100);
	puts(s1);
	puts(s2);
	puts("");
	printf("First comparing to second: \n");
	findUnique(s1, s2, (strlen(s1) > strlen(s2)) ? strlen(s1) : strlen(s2));
	printf("\n");
	printf("Second comparing to first: \n");
	findUnique(s2, s1, (strlen(s1) > strlen(s2)) ? strlen(s1) : strlen(s2));
	printf("\n");
	findEqual(s1, s2, (strlen(s1) > strlen(s2)) ? strlen(s1) : strlen(s2));
	getchar();
	getchar();
}