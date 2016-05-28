#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>
#include <conio.h>

#include <sys/stat.h>
#include <sys/types.h>
#include "dirent.h"
#include <windows.h>


int dir_exists(const char * dirname);
int dir_printFiles(const char * dirname);
int file_exists(const char * filename);
long long file_getSize(const char * filename);
time_t file_getCreateTime(const char * filename);
int file_create(const char * filename);
int file_remove(const char * filename);

char* dir_getFilesAsHtmlList(const char * dirname);
