#include "headers.h"

static void createList_void_zeroCount(void** state){
	bullets_t bullets = bullets_createList();
	assert_int_equal(bullets_getCount(bullets), 0);
	bullets_deleteList(bullets);
}

static void shoot_playerShooting_countOne(void** state){
	bullets_t bullets = bullets_createList();
	player_t player = player_create(LEFTSIDE);
	COORD pos = { 10, 10 };
	bullets_shoot(bullets, LEFTSIDE, pos);
	assert_int_equal(bullets_getCount(bullets), 1);
	bullets_deleteList(bullets);
}

void bullets_runTests(void){

	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(createList_void_zeroCount),
		cmocka_unit_test(shoot_playerShooting_countOne)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}