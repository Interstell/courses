#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char *Morse(char letter){
	char *codeMorse;
	static char code[7];
	static int codeSize;
	letter = toupper(letter);
	switch (letter){
	case 'A':
		strcpy(code, ".-");
		break;
	case 'B':
		strcpy(code, "-...");
		break;
	case 'C':
		strcpy(code, "-.-.");
		break;
	case 'D':
		strcpy(code, "-..");
		break;
	case 'E':
		strcpy(code, ".");
		break;
	case 'F':
		strcpy(code, "..-.");
		break;
	case 'G':
		strcpy(code, "--.");
		break;
	case 'H':
		strcpy(code, "....");
		break;
	case 'I':
		strcpy(code, "..");
		break;
	case 'J':
		strcpy(code, ".---");
		break;
	case 'K':
		strcpy(code, "-.-");
		break;
	case 'L':
		strcpy(code, ".-..");
		break;
	case 'M':
		strcpy(code, "--");
		break;
	case 'N':
		strcpy(code, "-.");
		break;
	case 'O':
		strcpy(code, "---");
		break;
	case 'P':
		strcpy(code, ".--.");
		break;
	case 'Q':
		strcpy(code, "--.-");
		break;
	case 'R':
		strcpy(code, ".-.");
		break;
	case 'S':
		strcpy(code, "...");
		break;
	case 'T':
		strcpy(code, "-");
		break;
	case 'U':
		strcpy(code, "..-");
		break;
	case 'V':
		strcpy(code, "...-");
		break;
	case 'W':
		strcpy(code, ".--");
		break;
	case 'X':
		strcpy(code, "-..-");
		break;
	case 'Y':
		strcpy(code, "-.--");
		break;
	case 'Z':
		strcpy(code, "--..");
		break;
	case '.':
		strcpy(code, ".-.-.-");
		break;
	case ',':
		strcpy(code, "--..--");
		break;
	case ':':
		strcpy(code, "---...");
		break;
	case '?':
		strcpy(code, "..--..");
		break;
	case '\'':
		strcpy(code, ".----.");
		break;
	case '-':
		strcpy(code, "-....-");
		break;
	case '/':
		strcpy(code, "-..-.");
		break;
	case '(':
	case ')':
		strcpy(code, "-.--.-");
		break;
	case '"':
		strcpy(code, ".-..-.");
		break;
	case '@':
		strcpy(code, ".--.-.");
		break;
	case '=':
		strcpy(code, "-...-");
		break;
	}
	codeMorse = &code;
	return codeMorse;
}

char *getUnit(char ZerOrOne, int size){
	static char *res;
	static char resString[50] = "\0";
	char unit[2];
	int i;
	for (i = 49; i >= 0; i--){
		resString[i] = '\0';
	}
	unit[0] = ZerOrOne;
	unit[1] = '\0';
	for (i = 1; i <= size; i++){
		strcat(resString, unit);
	}
	resString[strlen(resString)] = '\0';
	res = &resString;
	return res;
}

char *morse_encode(char *signal, const char *message, int unit_len, int pad_len){
	char *res = message;
	static char input[50]; 
	static char resSignal[1000]="\0";
	int i, j, k;
	for (i = 0; i < 1000; i++){
		if (*(res + i) == '\0'){
			break;
		}
		input[i] = *(res + i);
	}
	strcpy(resSignal, getUnit('0', pad_len));
	for (i = 0; i < strlen(input); i++){
		char morseCode[8];
		for (j = 7; j >=0 ; j--){
			morseCode[j] = '\0';
		}
		if (input[i] == ' '){
			//continue;
			for (k = 0; k < 7; k++){
				strcat(resSignal, getUnit('0', unit_len));
			}
			continue;
		}
		strcpy(morseCode, Morse(input[i]));
		for (j = 0; j < strlen(morseCode); j++){
			if (morseCode[j] == '.'){
				strcat(resSignal, getUnit('1', unit_len));
			}
			else if (morseCode[j] == '-'){
				for (k = 0; k < 3; k++){
					strcat(resSignal, getUnit('1', unit_len));
				}
			}
			if (j != strlen(morseCode)-1){
				strcat(resSignal, getUnit('0', unit_len));
			}
		}
		if ((i != strlen(input) - 1) && (input[i + 1] != ' ')){
			for (k = 0; k < 3; k++){
				strcat(resSignal, getUnit('0', unit_len));
			}
		}
	}
	strcat(resSignal, getUnit('0', pad_len));
	signal = &resSignal;
	return signal;
}