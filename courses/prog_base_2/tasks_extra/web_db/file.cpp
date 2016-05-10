#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "file.h"
#define FILE_ERROR -1

int file_exists(const char * fileName) {
	//return GetFileAttributes(fileName) != INVALID_FILE_ATTRIBUTES;
	std::ifstream infile(fileName);
	return infile.good();
}

int
file_readAllBytes(const char * fileName, char ** const nullBuf) {
	FILE * file;
	file = fopen(fileName, "rb");
	if (!file) {
		return FILE_ERROR;
	}
	fseek(file, 0, SEEK_END);
	int fileLen = ftell(file);
	*nullBuf = (char*)malloc(sizeof(char) * fileLen);
	fseek(file, 0, SEEK_SET);
	fread(*nullBuf, fileLen, 1, file);
	fclose(file);
	return fileLen;
}