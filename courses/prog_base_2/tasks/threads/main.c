#define _CRT_SECURE_NO_WARNINGS

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


void * producerFunc(void* args){
	data_t * data = (data_t *)args;
	while (1){
		mutex_lock(data->mutex);
		data->arr[(data->curInsertPos)++] = rand()%10;
		if (data->curInsertPos == 4) data->curInsertPos = 0;
		mutex_unlock(data->mutex);
		Sleep(SLEEP_TIME);
	}
	return NULL;
}

void * consumerFunc(void* args){
	data_t * data = (data_t *)args;
	while (1){
		mutex_lock(data->mutex);
		if (data->arr[0] == data->arr[1] - 1
			&& data->arr[1] == data->arr[2] - 1
			&& data->arr[2] == data->arr[3] - 1
			&& data->arr[3] - 3 == data->arr[0]){
			for (int i = 0; i < 4; i++)
				printf("%d ", data->arr[i]);
			printf("\n");
		}
		mutex_unlock(data->mutex);
		Sleep(SLEEP_TIME);
	}
	return NULL;
}

int main(void){
	srand((unsigned)time(NULL));
	data_t data;
	data.curInsertPos = 0;
	data.mutex = mutex_new();
	thread_t* producer1 = thread_create_args(producerFunc, &data);
	thread_t* producer2 = thread_create_args(producerFunc, &data);
	thread_t* consumer1 = thread_create_args(consumerFunc, &data);
	thread_t* consumer2 = thread_create_args(consumerFunc, &data);
	thread_join(consumer2);
	thread_free(producer1);
	thread_free(producer2);
	thread_free(consumer1);
	thread_free(consumer2);
	mutex_free(data.mutex);
	return EXIT_SUCCESS;
}