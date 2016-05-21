#include "place.h"

struct place_s{
	int row;
	int col;
	char ordererName[100];
	int isPaid;
	reservation_message_cb reserveMsgCb;
};

place_t place_new(int placeRow, int placeColumnInRow, char* ordererName, int isPaid, reservation_message_cb reserveMsgCb){
	place_t place = malloc(sizeof(struct place_s));
	place->row = placeRow;
	place->col = placeColumnInRow;
	strcpy(place->ordererName, ordererName);
	place->isPaid = 0;
	place->reserveMsgCb = reserveMsgCb;
	return place;
}

place_t place_newFreePlace(int placeRow, int placeColumnInRow){
	place_t place = malloc(sizeof(struct place_s));
	place->row = placeRow;
	place->col = placeColumnInRow;
	place->isPaid = 0;
	strcpy(place->ordererName, "\0");
	place->reserveMsgCb = NULL;
	return place;
}

void place_delete(place_t self){
	free(self);
}

place_t place_getCopy(place_t self){
	place_t copy = place_new(self->row, self->col, self->ordererName, self->isPaid, self->reserveMsgCb);
	return copy;
}

int place_getRow(place_t self){
	return self->row;
}

int place_getPlaceOnTheRow(place_t self){
	return self->col;
}

char* place_getOrdererName(place_t self){
	return self->ordererName;
}

int place_getPaidStatus(place_t self){
	return self->isPaid;
}

reservation_message_cb place_getMsgCb(place_t self){
	return self->reserveMsgCb;
}

void place_payForReservedPlace(place_t self){
	self->isPaid = 1;
}