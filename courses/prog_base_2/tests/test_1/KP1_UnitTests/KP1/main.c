#include "headers.h"
#include "cinema.h"

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka.h>
#include <cmocka_pbc.h>

void reserveMessageFunc(place_t place){
	printf("Waiting for you on the film. Row %d, Place %d", place_getRow(place), place_getPlaceOnTheRow(place));
}

static void getListOfReservedPlaces_void_countIsTwoAndObjectNotNull(void **state){
	cinema_t cinema = cinema_new(10, 10);
	cinema_setNextFilmProperties(cinema, "Interstellar", "Kyiv", time(0) + 3600);
	cinema_openBuyingAndOrdering(cinema);
	place_t placeOrdered1 = cinema_reservePlace(cinema, "Petya", 5, 2, reserveMessageFunc);
	place_t placeOrdered2 = cinema_reservePlace(cinema, "Kostya", 3, 5, reserveMessageFunc);
	place_payForReservedPlace(placeOrdered1);
	place_payForReservedPlace(placeOrdered2);

	list_t orderedList = cinema_getListOfReservedPlaces(cinema);
	assert_int_equal(list_length(orderedList), 2);
	
	cinema_delete(cinema);
}

//WELL, YOU KNOW THAT I KNOW HOW TO WRITE TESTS :)

int main(void){
	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(getListOfReservedPlaces_void_countIsTwoAndObjectNotNull)
		
	};
	return cmocka_run_group_tests(tests, NULL, NULL);

	return EXIT_SUCCESS;
}