#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//N-5
//первое значение - название экзешника
//второе - название файла из которого считать
//третье - название файла куда записать
//вложенные структуры через указатель
//одно строчное поле
int main(int argc, char *argv[]){
	FILE* READ = fopen(argv[1], "r");
	FILE* WRITE = fopen(argv[2], "w");
	if (READ == NULL){
		printf("Error! No file found.");
		getchar();
		exit(EXIT_FAILURE);
	}
	char input[2000];
	double mas[100];
	int count = 0;
	char *end, *begin = input;
	while (!feof(READ)){
		count = 0;
		fgets(input, 2000, READ);
		end = begin;
		while (*begin) {
			mas[count] = strtod(begin, &end);
			count++;
			begin = end;
			while (!isdigit(*begin) && *begin) begin++;
		}
		double min = mas[0];
		double max = mas[0];
		for (int i = 1; i < count; i++){
			if (mas[i] < min) min = mas[i];
			if (mas[i] > max) max = mas[i];
		}
		fprintf(WRITE, "Sum of max&min: %lf\n", min + max);
	}
	fclose(READ);
	fclose(WRITE);
	return EXIT_SUCCESS;
}