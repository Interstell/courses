#ifndef _INC_FILESIO
#define _INC_FILESIO
void saveStats(struct GAME Stats[][30], int size, int records[], int sizeR);
void readStats(struct GAME Stats[][30], int size, int records[], int sizeR);
#endif