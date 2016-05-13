#include "queue.h"

static void new_void_zeroSize(void **state){
	queue_t queue = queue_new();
	assert_int_equal(queue_getSize(queue), 0);
	queue_delete(queue);
}

static void add_oneEnqueuedElem_sizeOne(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	assert_int_equal(queue_getSize(queue), 1);
	queue_delete(queue);
}

static void add_QueueIsFull_returnERROR(void **state){
	queue_t queue = queue_new();
	for (int i = 0; i < MAX_QUEUE_SIZE; i++){
		queue_add(queue, i);
	}
	assert_int_equal(queue_add(queue, 100), QUEUE_ERROR);
	queue_delete(queue);
}

static void remove_QueueIsNotEmpty_returnElem(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	assert_int_equal(queue_remove(queue), 10);
	queue_delete(queue);
}

static void remove_QueueIsNotEmpty_doesQueueArrayShift(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	queue_add(queue, 15);
	queue_remove(queue);
	assert_int_equal(queue_peek(queue), 15);
	queue_delete(queue);
}

static void remove_QueueIsEmpty_returnERROR(void **state){
	queue_t queue = queue_new();
	assert_int_equal(queue_remove(queue), QUEUE_ERROR);
	queue_delete(queue);
}

static void peek_QueueIsNotEmpty_returnElemOnPeek(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	assert_int_equal(queue_peek(queue), 10);
	queue_delete(queue);
}

static void peek_QueueIsEmpty_returnERROR(void **state){
	queue_t queue = queue_new();
	assert_int_equal(queue_peek(queue), QUEUE_ERROR);
	queue_delete(queue);
}

static void getSize_QueueIsNotEmpty_correctSize(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	queue_add(queue, 15);
	assert_int_equal(queue_getSize(queue), 2);
	queue_delete(queue);
}

static void getSize_QueueIsEmpty_zeroSize(void **state){
	queue_t queue = queue_new();
	assert_int_equal(queue_getSize(queue), 0);
	queue_delete(queue);
}

static void isEmpty_QueueIsNotEmpty_false(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	assert_false(queue_isEmpty(queue));
	queue_delete(queue);
}

static void isEmpty_QueueIsEmpty_true(void **state){
	queue_t queue = queue_new();
	assert_true(queue_isEmpty(queue), 0);
	queue_delete(queue);
}


void queue_runTests(void){
	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(new_void_zeroSize),
		cmocka_unit_test(add_oneEnqueuedElem_sizeOne),
		cmocka_unit_test(add_QueueIsFull_returnERROR),
		cmocka_unit_test(remove_QueueIsNotEmpty_returnElem),
		cmocka_unit_test(remove_QueueIsNotEmpty_doesQueueArrayShift),
		cmocka_unit_test(remove_QueueIsEmpty_returnERROR),
		cmocka_unit_test(peek_QueueIsNotEmpty_returnElemOnPeek),
		cmocka_unit_test(peek_QueueIsEmpty_returnERROR),
		cmocka_unit_test(getSize_QueueIsNotEmpty_correctSize),
		cmocka_unit_test(getSize_QueueIsEmpty_zeroSize),
		cmocka_unit_test(isEmpty_QueueIsNotEmpty_false),
		cmocka_unit_test(isEmpty_QueueIsEmpty_true),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}