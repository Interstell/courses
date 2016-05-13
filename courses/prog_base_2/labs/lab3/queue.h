#pragma once
#include "headers.h"

#define MAX_QUEUE_SIZE 20
#define QUEUE_ERROR INT_MAX


queue_t queue_new(void);
void queue_delete(queue_t self);

int queue_add(queue_t self, int elem);
int queue_remove(queue_t self);
int queue_peek(queue_t self);
int queue_getSize(queue_t self);
int queue_isEmpty(queue_t self);
int queue_deleteTail(queue_t self);

void queue_runTests(void);