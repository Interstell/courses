#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cinema_s* cinema_t;
typedef struct place_s* place_t;
typedef void(*reservation_message_cb)(place_t place);
