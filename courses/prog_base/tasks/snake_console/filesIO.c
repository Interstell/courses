#include "headers.h"


void saveStats(struct GAME Stats[][30], int size, int records[], int sizeR){
	FILE *ST;
	ST = fopen("stats.bin", "wb");
	fwrite(Stats, size, 1, ST);
	fflush(ST);
	fclose(ST);
	ST = fopen("system.bin", "wb");
	fwrite(records, sizeR, 1, ST);
	fflush(ST);
	fclose(ST);
}
void readStats(struct GAME Stats[][30], int size, int records[], int sizeR){
	FILE *ST;
	ST = fopen("stats.bin", "rb");
	if (ST == NULL) exit(EXIT_SUCCESS);
	fread(Stats, size, 1, ST);
	fflush(ST);
	fclose(ST);
	ST = fopen("system.bin", "rb");
	if (ST == NULL) exit(EXIT_SUCCESS);
	fread(records, sizeR, 1, ST);
	fflush(ST);
	fclose(ST);
}