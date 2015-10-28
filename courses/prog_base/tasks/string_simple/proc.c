#include <string.h>

char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr){
	int result = 0, i, j, foundFlag = 0, extStringFound = 0;
	static char resChar[100];
	for (i = 0; i < linesNum; i++){
		foundFlag = 0;
		for (j = 0; j < linesNum; j++){
			if (((strcmp(textLines[i], textLines[j]) == 0) || (strcmp(textLines[i], extraStr) == 0)) && (i != j)){
				foundFlag = 1;
			}
		}
		if (foundFlag == 0){
			result++;
		}
		if (strcmp(textLines[i], extraStr) == 0){
			extStringFound = 1;
		}
	}
	sprintf(resChar, "%d %s", result, (extStringFound == 1) ? "NULL" : extraStr);
	resultStr = resChar;
	return resultStr;
}
