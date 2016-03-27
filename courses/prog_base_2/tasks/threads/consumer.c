#include "header.h"
#include "consumer.h"

struct consumer_s{
	thread_t* thread;
};

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

consumer_t consumer_new(data_t* data){
	consumer_t consumer = (consumer_t)malloc(sizeof(struct consumer_s));
	consumer->thread = thread_create_args(consumerFunc, data);
	return consumer;
}

void consumer_delete(consumer_t consumer){
	thread_free(consumer->thread);
	free(consumer);
}

void consumer_wait(consumer_t consumer){
	thread_join(consumer->thread);
}

