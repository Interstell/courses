#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "mutex.h"
#include "thread.h"

#define SLEEP_TIME 1

typedef struct data_s{
	int arr[4];
	int curInsertPos;
	mutex_t *mutex;
} data_t;
