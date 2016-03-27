#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "mutex.h"
#include "thread.h"

typedef struct producer_s* producer_t;

producer_t producer_new(data_t* data);
void producer_delete(producer_t producer);
void producer_wait(producer_t producer);