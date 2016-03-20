#define _CRT_SECURE_NO_WARNINGS

#include "check.h"


int main(void){
	char bigStr[] = "abcd123as321dj123aj321jk321da123ash321da";
	char smallStr[] = "123";
	puts("Substrings marked with color:");
	check(bigStr, smallStr, containsCB1, reversedCB1);
	puts("\nSubstrings are not printed: ");
	check(bigStr, smallStr, containsCB2, reversedCB2);
	
	getchar();
	return EXIT_SUCCESS;
}