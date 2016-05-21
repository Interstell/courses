#include "ArrayList.h"

struct list_s{
	place_t* arr;
	int length;
	int capacity;
};

list_t list_new(int capacity){
	list_t list = malloc(sizeof(struct list_s));
	list->arr = malloc(capacity*sizeof(place_t));
	list->length = 0;
	list->capacity = capacity;
	return list;
}

void list_free(list_t self){
	free(self->arr);
	free(self);
}

list_t list_getCopy(list_t self){
	list_t copy = list_new(self->capacity);
	for (int i = 0; i < self->length; i++){
		list_add(copy, place_getCopy(self->arr[i]));
	}
	return copy;
}

void list_clean(list_t self){
	free(self->arr);
	self->arr = malloc(self->capacity*sizeof(place_t));
	self->length = 0;
}

void list_add(list_t self, place_t data){
	self->arr[self->length++] = data;
}

int list_addByIndex(list_t self, place_t data, int index){
	if (index > self->length || index < 0) return 0;
	for (int i = self->length; i > index; i--){
		self->arr[i] = self->arr[i - 1];
	}
	self->arr[index] = data;
	self->length++;
	return 1;
}

int list_setByIndex(list_t self, place_t data, int index){
	if (index > self->length || index < 0) return 0;
	self->arr[index] = data;
	return 1;
}

place_t list_get(list_t self, int index){
	return self->arr[index];
}

place_t list_delete(list_t self, int index){
	if (index >= self->length || index < 0) return NULL;
	place_t res = self->arr[index];
	for (int i = index; i < self->length - 1; i++){
		self->arr[i] = self->arr[i + 1];
	}
	self->length--;
	return res;
}

place_t list_deleteByObject(list_t self, place_t place){
	if (place == NULL) return NULL;
	for (int i = 0; i < self->length; i++){
		if (self->arr[i] == place){
			return list_delete(self, i);
		}
	}
	return NULL;
}

int list_length(list_t self){
	return self->length;
}

void list_print(list_t self){
	//TODO
}

