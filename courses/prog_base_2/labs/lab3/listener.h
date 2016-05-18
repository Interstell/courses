#pragma once
#include "headers.h"
#include "notify.h"

#define MAX_LISTENERS 10

struct listener_s{
	char name[20];
	int startRow;
	int color;
	notify_addPrint_cb addPrint;
	notify_removePrint_cb removePrint;
	notify_addTransfer_cb addPrint_transfer;
	notify_removeTransfer_cb removePrint_transfer;
	notify_fullProcessing_cb fullProcessing;
	notify_fullOverflow_cb fullOverflow;
};

listener_t listener_new(char* name, int startRow, int color);
void listener_delete(listener_t self);

void listener_setNotifiers(listener_t self, notify_addPrint_cb addPrint, notify_removePrint_cb removePrint, notify_addTransfer_cb addPrint_transfer, notify_removeTransfer_cb removePrint_transfer, notify_fullProcessing_cb fullProcessing, notify_fullOverflow_cb fullOverflow);