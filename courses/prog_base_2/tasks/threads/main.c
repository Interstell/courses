#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include "producer.h"
#include "consumer.h"

data_t* data_initialize(void){
	data_t* data = (data_t*)malloc(sizeof(struct data_s));
	data->curInsertPos = 0;
	data->mutex = mutex_new();
	return data;
}

void data_delete(data_t* data){
	mutex_free(data->mutex);
	free(data);
}

int main(void){
	
	// ATTENTION! IF YOU THINK IT IS TOO SLOW - change "SLEEP_TIME" FOR "0" in "header.h"
	// Or just wait a bit, it really works.  \_(0_0)_/
	// With "SLEEP_TIME"==0 it is too quick.

	srand((unsigned)time(NULL));
	data_t * data = data_initialize();
	producer_t producer1 = producer_new(data);
	producer_t producer2 = producer_new(data);
	consumer_t consumer1 = consumer_new(data);
	consumer_t consumer2 = consumer_new(data);
	consumer_wait(consumer2);
	producer_delete(producer1);
	producer_delete(producer2);
	consumer_delete(consumer1);
	consumer_delete(consumer2);
	data_delete(data);

	return EXIT_SUCCESS;
}