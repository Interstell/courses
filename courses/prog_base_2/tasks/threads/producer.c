#include "header.h"
#include "producer.h"

struct producer_s{
	thread_t* thread;
};

void * producerFunc(void* args){
	data_t * data = (data_t *)args;
	while (1){
		mutex_lock(data->mutex);
		data->arr[(data->curInsertPos)++] = rand() % 10;
		if (data->curInsertPos == 4) data->curInsertPos = 0;
		mutex_unlock(data->mutex);
		Sleep(SLEEP_TIME);
	}
	return NULL;
}

producer_t producer_new(data_t* data){
	producer_t producer = (producer_t)malloc(sizeof(struct producer_s));
	producer->thread = thread_create_args(producerFunc, data);
	return producer;
}

void producer_delete(producer_t producer){
	thread_free(producer->thread);
	free(producer);
}

void producer_wait(producer_t producer){
	thread_join(producer->thread);
}
