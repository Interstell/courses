#include "listener.h"
#include "gui.h"

listener_t listener_new(char* name, int startRow, int color){
	listener_t l = malloc(sizeof(struct listener_s));
	strcpy(l->name, name);
	l->startRow = startRow;
	l->color = color;
	gui_jumpTo(0, startRow);
	gui_setColor(WHITE);
	for (int i = 0; i < SCREEN_WIDTH - 1; i++){
		printf("-");
	}
	printf("\n");
	printf("Listener: %s\n", name);
	printf("Event log: \n");
	gui_jumpTo(0, startRow + 5);
	for (int i = 0; i < SCREEN_WIDTH - 1; i++){
		printf("-");
	}
	printf("\n");
	return l;
}

void listener_delete(listener_t self){
	free(self);
}

void listener_setCallbacks(listener_t self, addPrint_cb addPrint, removePrint_cb removePrint, addPrint_transfer_cb addPrint_transfer, removePrint_transfer_cb removePrint_transfer, fullProcessing_cb fullProcessing, fullOverflow_cb fullOverflow){
	self->addPrint = addPrint;
	self->removePrint = removePrint;
	self->addPrint_transfer = addPrint_transfer;
	self->removePrint_transfer = removePrint_transfer;
	self->fullProcessing = fullProcessing;
	self->fullOverflow = fullOverflow;
}