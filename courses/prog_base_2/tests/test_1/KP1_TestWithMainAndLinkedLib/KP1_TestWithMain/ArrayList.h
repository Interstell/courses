#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "place.h"

typedef struct list_s* list_t;

list_t list_new(int capacity);
void list_free(list_t self);
list_t list_getCopy(list_t self);

void list_clean(list_t self);
void list_add(list_t self, place_t data);
int list_addByIndex(list_t self, place_t data, int index);
int list_setByIndex(list_t self, place_t data, int index);
place_t list_get(list_t self, int index);
place_t list_delete(list_t self, int index);
place_t list_deleteByObject(list_t self, place_t place);
int list_length(list_t self);
void list_print(list_t self);