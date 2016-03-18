#include "headers.h"

static void enqueue_pushingCmd_countOne(void** state){
	game_enqueue(PLAYER1_SHOOT);
	assert_int_equal(game_queueCount(), 1);
}
static void checkCooldown_timeEnoughForNextShoot_returnTrue(void** state){
	SYSTEMTIME now;
	GetLocalTime(&now);
	now.wSecond--;
	assert_true(game_checkCooldown(now));
}
static void checkCooldown_timeNotEnoughForNextShoot_returnFalse(void** state){
	SYSTEMTIME now;
	GetLocalTime(&now);
	assert_false(game_checkCooldown(now));
}
static void checkQueueTick_timeEnoughtForNextTick_returnTrue(void** state){
	SYSTEMTIME now;
	GetLocalTime(&now);
	now.wSecond--;
	assert_true(game_checkQueueTick(now));
}
static void checkQueueTick_timeNotEnoughForNextTick_returnFalse(void** state){
	SYSTEMTIME now;
	GetLocalTime(&now);
	assert_false(game_checkQueueTick(now));
}


void game_runTests(void){

	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(enqueue_pushingCmd_countOne),
		cmocka_unit_test(checkCooldown_timeEnoughForNextShoot_returnTrue),
		cmocka_unit_test(checkCooldown_timeNotEnoughForNextShoot_returnFalse),
		cmocka_unit_test(checkQueueTick_timeEnoughtForNextTick_returnTrue),
		cmocka_unit_test(checkQueueTick_timeNotEnoughForNextTick_returnFalse)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}