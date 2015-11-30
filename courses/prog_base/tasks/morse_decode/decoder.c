#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *morseToSymbol(char *code){
	static char res[1];
	static int bracket = 0;
	if (strcmp(code, ".-") == 0) res[0] = 'A';
	else if (strcmp(code, "-...") == 0) res[0] = 'B';
	else if (strcmp(code, "-.-.") == 0) res[0] = 'C';
	else if (strcmp(code, "-..") == 0) res[0] = 'D';
	else if (strcmp(code, ".") == 0) res[0] = 'E';
	else if (strcmp(code, "..-.") == 0) res[0] = 'F';
	else if (strcmp(code, "--.") == 0) res[0] = 'G';
	else if (strcmp(code, "....") == 0) res[0] = 'H';
	else if (strcmp(code, "..") == 0) res[0] = 'I';
	else if (strcmp(code, ".---") == 0) res[0] = 'J';
	else if (strcmp(code, "-.-") == 0) res[0] = 'K';
	else if (strcmp(code, ".-..") == 0) res[0] = 'L';
	else if (strcmp(code, "--") == 0) res[0] = 'M';
	else if (strcmp(code, "-.") == 0) res[0] = 'N';
	else if (strcmp(code, "---") == 0) res[0] = 'O';
	else if (strcmp(code, ".--.") == 0) res[0] = 'P';
	else if (strcmp(code, "--.-") == 0) res[0] = 'Q';
	else if (strcmp(code, ".-.") == 0) res[0] = 'R';
	else if (strcmp(code, "...") == 0) res[0] = 'S';
	else if (strcmp(code, "-") == 0) res[0] = 'T';
	else if (strcmp(code, "..-") == 0) res[0] = 'U';
	else if (strcmp(code, "...-") == 0) res[0] = 'V';
	else if (strcmp(code, ".--") == 0) res[0] = 'W';
	else if (strcmp(code, "-..-") == 0) res[0] = 'X';
	else if (strcmp(code, "-.--") == 0) res[0] = 'Y';
	else if (strcmp(code, "--..") == 0) res[0] = 'Z';
	else if (strcmp(code, ".-.-.-") == 0) res[0] = '.';
	else if (strcmp(code, "--..--") == 0) res[0] = ',';
	else if (strcmp(code, "---...") == 0) res[0] = ':';
	else if (strcmp(code, "..--..") == 0) res[0] = '?';
	else if (strcmp(code, ".----.") == 0) res[0] = '\'';
	else if (strcmp(code, "-....-") == 0) res[0] = '-';
	else if (strcmp(code, "-..-.") == 0) res[0] = '/';
	else if (strcmp(code, "-.--.-") == 0){
		res[0] = (!bracket) ? '(' : ')';
		bracket = !bracket;
	}
	else if (strcmp(code, ".-..-.") == 0) res[0] = '"';
	else if (strcmp(code, ".--.-.") == 0) res[0] = '@';
	else if (strcmp(code, "-...-") == 0) res[0] = '=';
	return res;
}
char *morse_decode(char *message, const char *signal){
	static char input[1000];
	char code[10]="";
	static char result[1000]="";
	int i,j, foundOne = 0, writePos = 0;
	int unitLength = 0, currSequenceLength=0;
	char currBin = '1';

	//first read and deleting zeros in the beginning
	for (i = 0; i < strlen(signal); i++){
		if (*(signal + i) == '1'){
			foundOne = 1;
		}
		if (foundOne){
			input[writePos] = *(signal + i);
			writePos++;
		}
	}
	//deleting zeros in the end
	for (i = strlen(input) - 1; i >= 0; i--){
		if (input[i] == '0'){
			input[i] = '\0';
		}
		else break;
	}
	strcat(input, "0");
	//establishing the length of the unit
	for (i = 0; i < strlen(input); i++){
		if (input[i] == '0'){
			unitLength++;
		}
		if ((input[i] == '0') && (input[i + 1] == '1')){
			break;
		}
	}

	for (i = 0; i < strlen(input); i++){
		if (input[i] == currBin){
			currSequenceLength++;
		}
		else {
			if (currBin == '1'){
				if (currSequenceLength == unitLength) {
					strcat(code, ".");
				}
				else if (currSequenceLength == 3 * unitLength){
					strcat(code, "-");
				}
			}
			else if (currBin == '0'){
				if (currSequenceLength == 3 * unitLength){
					strcat(result, morseToSymbol(code));
					for (j = strlen(code) - 1; j >= 0; j--){
						code[j] = '\0';
					}
				}
				if (currSequenceLength % (7 * unitLength) == 0){
					strcat(result, morseToSymbol(code));
					for (j = strlen(code) - 1; j >= 0; j--){
						code[j] = '\0';
					}
					for (j = 1; j <= currSequenceLength / 7; j++){
						strcat(result, " ");
					}
				}
			}
			currBin = (currBin == '1') ? '0' : '1';
			currSequenceLength = 1;
		}

	}
	strcat(result, morseToSymbol(code));
	return result;

}