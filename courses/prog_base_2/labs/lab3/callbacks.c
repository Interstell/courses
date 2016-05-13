#include "callbacks.h"
#include "gui.h"
#include "listener.h"

static void prepareToPrint(listener_t listener){
	gui_jumpTo(0, listener->startRow + 4);
	for (int i = 0; i < SCREEN_WIDTH - 1; i++){
		printf(" ");
	}
	gui_jumpTo(0, listener->startRow + 4);
	gui_setColor(listener->color);
}

void addPrint1(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Element %d has been added to Queue#%d\n", elem, queueNum);
}

void addPrint2(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d: added %d\n", queueNum, elem);
}

void removePrint1(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Element %d has been removed from Queue#%d\n", elem, queueNum);
}

void removePrint2(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d: removed %d\n", queueNum, elem);
}

void addPrint_transfer1(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d is full! Element %d has been transferred from Queue#%d to Queue#%d\n", queueNum, elem, queueNum, (queueNum == 1) ? 2 : 1);
}

void addPrint_transfer2(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d: FULL, transferred %d to Queue#%d\n", queueNum, elem, (queueNum == 1) ? 2 : 1);
}

void removePrint_transfer1(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d is too small! Element %d has been transferred from Queue#%d to Queue#%d\n", queueNum, elem, (queueNum == 1) ? 2 : 1, queueNum);
}

void removePrint_transfer2(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d: too small, transferred %d from Queue#%d\n", queueNum, elem, (queueNum == 1) ? 2 : 1);
}


