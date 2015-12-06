#ifndef _INC_STATS
#define _INC_STATS
void sortLevel(struct GAME Stats[], int records[], int speedLevel);
void sortAllStat(struct GAME Stats[][30], int records[]);
void writeToStat(struct GAME Stats[][30], int recordsAmount[], char* name, int score, int speedLevel);
#endif