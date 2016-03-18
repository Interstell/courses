#include "headers.h"

static void create_LEFTSIDE_properCoords(void** state){
	player_t player = player_create(LEFTSIDE);
	COORD top = player_getTopCoord(player);
	assert_int_equal(top.X, 2);
	assert_int_equal(top.Y, 2);
}

static void create_RIGHSIDE_properCoords(void** state){
	player_t player = player_create(RIGHTSIDE);
	COORD top = player_getTopCoord(player);
	assert_int_equal(top.X, WINDOW_WIDTH - 10);
	assert_int_equal(top.Y, 2);
}

static void incScore_void_scoreOne(void** state){
	player_t player = player_create(RIGHTSIDE);
	player_incScore(player);
	assert_int_equal(player_getScore(player), 1);
}

void player_runTests(void){

	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(create_LEFTSIDE_properCoords),
		cmocka_unit_test(create_RIGHSIDE_properCoords),
		cmocka_unit_test(incScore_void_scoreOne)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}