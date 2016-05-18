#include "notify.h"
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

void notify_addPrint1(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Element %d has been added to Queue#%d\n", elem, queueNum);
}

void notify_addPrint2(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d: added %d\n", queueNum, elem);
}

void notify_removePrint1(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Element %d has been removed from Queue#%d\n", elem, queueNum);
}

void notify_removePrint2(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d: removed %d\n", queueNum, elem);
}

void notify_addTransfer1(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d is full! Element %d has been transferred from Queue#%d to Queue#%d\n", queueNum, elem, queueNum, (queueNum == 1) ? 2 : 1);
}

void notify_addTransfer2(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d: FULL, transferred %d to Queue#%d\n", queueNum, elem, (queueNum == 1) ? 2 : 1);
}

void notify_removeTransfer1(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d is too small! Element %d has been transferred from Queue#%d to Queue#%d\n", queueNum, elem, (queueNum == 1) ? 2 : 1, queueNum);
}

void notify_removeTransfer2(listener_t listener, int queueNum, int elem){
	prepareToPrint(listener);
	printf("Queue#%d: too small, transferred %d from Queue#%d\n", queueNum, elem, (queueNum == 1) ? 2 : 1);
}

void notify_processing1(listener_t listener, int queueNum, int num11, int num12, int num13, int num22, int num23){
	prepareToPrint(listener);
	printf("Queues are nearly empty! Normalizing size to 3: adding %d,%d,%d to Queue#%d and %d,%d to Queue#%d\n", num11, num12, num13, queueNum, num22, num23, (queueNum == 1) ? 2 : 1);
}

void notify_processing2(listener_t listener, int queueNum, int num11, int num12, int num13, int num22, int num23){
	prepareToPrint(listener);
	printf("Queues: EMPTY! Filling with new elements: %d,%d,%d to Queue#%d and %d,%d to Queue#%d\n", num11, num12, num13, queueNum, num22, num23, (queueNum == 1) ? 2 : 1);
}

void notify_overflow1(listener_t listener, int queueNum, int enqueued1, int enqueued2){
	prepareToPrint(listener);
	printf("Queues are full! Dequeuing first elements in queues: %d from Queue#%d, %d from Queue#%d", enqueued1, queueNum, enqueued2, (queueNum == 1) ? 2 : 1);
}

void notify_overflow2(listener_t listener, int queueNum, int enqueued1, int enqueued2){
	prepareToPrint(listener);
	printf("Queues: FULL!! Dequeuing first elements: %d from Queue#%d, %d from Queue#%d", enqueued1, queueNum, enqueued2, (queueNum == 1) ? 2 : 1);
}