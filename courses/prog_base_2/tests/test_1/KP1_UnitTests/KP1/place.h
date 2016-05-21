#pragma once

#define MAX_PLACES_TO_RESERVE 100
#define MAX_PLACES_TO_BUY 100
#define MAX_ROWS 10
#define MAX_COLS 10

#include "headers.h"

place_t place_new(int placeRow, int placeColumnInRow, char* ordererName, int isPaid, reservation_message_cb reserveMsgCb);
place_t place_newFreePlace(int placeRow, int placeColumnInRow);
void place_delete(place_t self);
place_t place_getCopy(place_t self);

int place_getRow(place_t self);
int place_getPlaceOnTheRow(place_t self);
char* place_getOrdererName(place_t self);
int place_getPaidStatus(place_t self);
reservation_message_cb place_getMsgCb(place_t self);
void place_payForReservedPlace(place_t self);
