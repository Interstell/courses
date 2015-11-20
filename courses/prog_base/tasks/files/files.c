#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fprocess(const char * pread, const char * pwrite){
	FILE* fr = fopen(pread, "r");
	FILE* fw = fopen(pwrite, "w");
	int input[6];
	char temp[1000];
	for (int i = 1; i <= 16; i++){
		fgets(temp, 1000, fr);
	}
	double r1, r2;
	fscanf(fr, "%d %d %d %d %d %d", &input[0], &input[1], &input[2], &input[3], &input[4], &input[5]);
	r1 = sqrt(pow(input[0] - input[4], 2) + pow(input[1] - input[5], 2));
	r2 = sqrt(pow(input[2] - input[4], 2) + pow(input[3] - input[5], 2));
	(r1 <= r2) ? fprintf(fw, "%d %d", input[0], input[1]) : fprintf(fw, "%d %d", input[2], input[3]);
	fclose(fr);
	fclose(fw);
}