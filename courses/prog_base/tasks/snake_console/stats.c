#include "headers.h"

void sortLevel(struct GAME Stats[], int records[], int speedLevel){
	for (int i = 0; i < records[speedLevel] - 1; i++) {
		for (int j = 0; j < records[speedLevel] - i - 1; j++) {
			if (Stats[j].Score<Stats[j + 1].Score) {
				struct GAME tmp = Stats[j];
				Stats[j] = Stats[j + 1];
				Stats[j + 1] = tmp;
			}
		}
	}
}
void sortAllStat(struct GAME Stats[][30], int records[]){
	for (int i = 0; i < 9; i++){
		sortLevel(Stats[i], records, i);
	}
}
void writeToStat(struct GAME Stats[][30], int recordsAmount[], char* name, int score, int speedLevel){
	strcpy(Stats[speedLevel][recordsAmount[speedLevel]].Name, name);
	Stats[speedLevel][recordsAmount[speedLevel]].Score = score;
	Stats[speedLevel][recordsAmount[speedLevel]].Level = speedLevel;
	time_t t = time(NULL);
	Stats[speedLevel][recordsAmount[speedLevel]].Time = t;
	recordsAmount[speedLevel]++;
	if (speedLevel == 30) speedLevel = 29;
}
