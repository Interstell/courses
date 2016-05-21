#include "headers.h"
#include "cinema.h"

void reserveMessageFunc(place_t place){
	printf("Waiting for you on the film. Row %d, Place %d", place_getRow(place), place_getPlaceOnTheRow(place));
}

int main(void){
	cinema_t cinema = cinema_new(10, 10);
	cinema_setNextFilmProperties(cinema, "Interstellar", "Kyiv", time(0) + 3600);
	cinema_openBuyingAndOrdering(cinema);
	place_t placeBought = cinema_sellPlace(cinema, "Vasya", 2, 3);
	place_t placeOrdered = cinema_reservePlace(cinema, "Petya", 5, 2, reserveMessageFunc);
	place_payForReservedPlace(placeOrdered);
	cinema_closeOrderingAndFreeUnpaidOrders(cinema);

	cinema_delete(cinema);

	getchar();
	return EXIT_SUCCESS;
}