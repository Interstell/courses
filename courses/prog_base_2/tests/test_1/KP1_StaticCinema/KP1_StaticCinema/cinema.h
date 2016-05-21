#pragma once

#include "headers.h"
#include "place.h"
#include "ArrayList.h"

#define TRUE 1
#define FALSE 0

cinema_t cinema_new(int maxRows, int maxPlacesInARow);
void cinema_delete(cinema_t self);

int cinema_getTotalNumOfPlaces(cinema_t self); //1
void cinema_setNextFilmProperties(cinema_t self, char* filmName, char* filmAddress, time_t filmStartTime); //2
char* cinema_getNextFilmName(cinema_t self); // 3
void cinema_openBuyingAndOrdering(cinema_t self); // 4
place_t cinema_sellPlace(cinema_t self, char* ordererName, int row, int placeOnThisRow); //5, returns NULL if place is reserved/bought/does_not_exist/buying_is_closed
place_t cinema_reservePlace(cinema_t self, char* ordererName, int row, int placeOnThisRow, reservation_message_cb msgCb); //6, returns NULL if place is reserved/bought/does_not_exist/reservation_is_closed
void cinema_cancelReservationOfPlace(cinema_t self, place_t place); //7
list_t cinema_getListOfFreePlaces(cinema_t self); //8
list_t cinema_getListOfReservedPlaces(cinema_t self); //9
void cinema_closeBuying(cinema_t self); //10
void cinema_closeOrderingAndFreeUnpaidOrders(cinema_t self); //11




