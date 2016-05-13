#pragma once
#include "headers.h"
#include "queue.h"
#include "listener.h"



queueSet_t queueSet_new(void);
void queueSet_delete(queueSet_t self);

void queueSet_initialize(queueSet_t self);
void queueSet_addListener(queueSet_t self, listener_t listener);
void queueSet_endlessIOLoop(queueSet_t self);
