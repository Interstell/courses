#include "cinema.h"

struct cinema_s{
	int placesTotal;
	int** places; //0 - free, 1 - not free
	int rows; 
	int cols;
	char nextFilmName[100];
	char nextFilmAddress[100];
	time_t nextFilmStartTime;
	list_t reservedPlaces;
	int placesReservedNum;
	int reservationAllowed;
	list_t boughtPlaces;
	int placesBoughtNum;
	int buyingAllowed;
};

cinema_t cinema_new(int maxRows, int maxPlacesInARow){
	cinema_t cinema = malloc(sizeof(struct cinema_s));
	cinema->places = (int**)malloc(maxRows*sizeof(int*));
	for (int i = 0; i < maxRows; i++){
		cinema->places[i] = (int*)malloc(maxPlacesInARow*sizeof(int));
		for (int j = 0; j < maxPlacesInARow; j++){
			cinema->places[i][j] = 0;
		}
	}
	cinema->rows = maxRows;
	cinema->cols = maxPlacesInARow;
	cinema->placesTotal = maxRows * maxPlacesInARow;
	
	cinema->boughtPlaces = list_new(cinema->placesTotal);
	cinema->reservedPlaces = list_new(cinema->placesTotal);

	cinema->placesBoughtNum = 0;
	cinema->placesReservedNum = 0;
	cinema->reservationAllowed = 0; //closed By Default
	cinema->buyingAllowed = 0; //closed By Default
	return cinema;
}

void cinema_delete(cinema_t self){
	for (int i = 0; i < self->rows; i++){
		free(self->places[i]);
	}
	free(self->places);
	list_free(self->boughtPlaces);
	list_free(self->reservedPlaces);
}

int cinema_getTotalNumOfPlaces(cinema_t self){ //1
	return self->placesTotal;
}

void cinema_setNextFilmProperties(cinema_t self, char* filmName, char* filmAddress, time_t filmStartTime){ //2
	strcpy(self->nextFilmName, filmName);
	strcpy(self->nextFilmAddress, filmAddress);
	self->nextFilmStartTime = filmStartTime;
}
char* cinema_getNextFilmName(cinema_t self){ // 3
	return self->nextFilmName;
}

void cinema_openBuyingAndOrdering(cinema_t self){ // 4
	self->buyingAllowed = 1;
	self->reservationAllowed = 1;
}

place_t cinema_sellPlace(cinema_t self, char* ordererName, int row, int placeOnThisRow){ //5, returns NULL if place is reserved/bought/does_not_exist/buying_is_closed
	if (row >= self->rows 
		|| row < 0 
		|| placeOnThisRow >= self->cols 
		|| placeOnThisRow < 0 
		|| self->places[row][placeOnThisRow] == 1 
		|| !self->buyingAllowed) return NULL;
	place_t resPlace = place_new(row, placeOnThisRow, ordererName, TRUE, NULL);
	list_add(self->boughtPlaces, resPlace);
	self->placesBoughtNum++;
	self->places[row][placeOnThisRow] = 1;
	return resPlace;
}

place_t cinema_reservePlace(cinema_t self, char* ordererName, int row, int placeOnThisRow, reservation_message_cb msgCb){ //6, returns NULL if place is reserved/bought/does_not_exist/reservation_is_closed
	if (row >= self->rows 
		|| row < 0 
		|| placeOnThisRow >= self->cols 
		|| placeOnThisRow < 0 
		|| self->places[row][placeOnThisRow] == 1 
		|| !self->reservationAllowed) return NULL;
	place_t resPlace = place_new(row, placeOnThisRow, ordererName, FALSE, msgCb);
	list_add(self->reservedPlaces, resPlace);
	self->placesReservedNum++;
	self->places[row][placeOnThisRow] = 1;
	return resPlace;
}

void cinema_cancelReservationOfPlace(cinema_t self, place_t place){ //7
	if (place == NULL) return;
	list_deleteByObject(self->reservedPlaces, place);
	self->placesReservedNum--;
	self->places[place_getRow(place)][place_getPlaceOnTheRow(place)] = 0;
	place_delete(place);
}

list_t cinema_getListOfFreePlaces(cinema_t self){ //8
	list_t listOfFreePlaces = list_new(self->placesTotal);
	for (int i = 0; i < self->cols; i++){
		for (int j = 0; j < self->rows; j++){
			if (self->places[i][j] == 0){ //if place is not bought/reserved
				list_add(listOfFreePlaces, place_newFreePlace(i, j));
			}
		}
	}
	return listOfFreePlaces;
}

list_t cinema_getListOfReservedPlaces(cinema_t self){ //9
	return list_getCopy(self->reservedPlaces);
}

void cinema_closeBuying(cinema_t self){ //10
	self->buyingAllowed = 0;
}

void cinema_closeOrderingAndFreeUnpaidOrders(cinema_t self){ //11
	self->reservationAllowed = 0;
	for (int i = 0; i < list_length(self->reservedPlaces); i++){
		place_t place = list_get(self->reservedPlaces, i);
		if (place_getPaidStatus(place) == 1){ //we notify ONLY those who have paid for the ticket
			place_getMsgCb(place)(place); //by executing their callback here
		}
	}
	list_clean(self->reservedPlaces); //anyway, we clean the content of the list (without(!) deleting objects by place_delete)
	self->placesReservedNum = 0;
}