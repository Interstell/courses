#pragma once
#include "headers.h"
#include "callbacks.h"

#define MAX_LISTENERS 10



struct listener_s{
	char name[20];
	int startRow;
	int color;
	addPrint_cb addPrint;
	removePrint_cb removePrint;
	addPrint_transfer_cb addPrint_transfer;
	removePrint_transfer_cb removePrint_transfer;
	fullProcessing_cb fullProcessing;
	fullOverflow_cb fullOverflow;
};

listener_t listener_new(char* name, int startRow, int color);
void listener_delete(listener_t self);

void listener_setCallbacks(listener_t self, addPrint_cb addPrint, removePrint_cb removePrint, addPrint_transfer_cb addPrint_transfer, removePrint_transfer_cb removePrint_transfer, fullProcessing_cb fullProcessing, fullOverflow_cb fullOverflow);