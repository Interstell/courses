#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "mutex.h"
#include "thread.h"

typedef struct consumer_s* consumer_t;

consumer_t consumer_new(data_t* data);
void consumer_delete(consumer_t consumer);
void consumer_wait(consumer_t consumer);