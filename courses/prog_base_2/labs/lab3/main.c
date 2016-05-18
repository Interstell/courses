#include "queue.h"
#include "queueset.h"
#include "gui.h"

int main(void){
	srand(time(NULL));
	gui_changeSize();
	//queue_runTests();

	queueSet_t set = queueSet_new();
	queueSet_initialize(set);
	listener_t l1 = listener_new("Vasya", 0, YELLOW);
	listener_setNotifiers(l1, notify_addPrint1, notify_removePrint1, notify_addTransfer1, notify_removeTransfer1, notify_processing1, notify_overflow1);
	listener_t l2 = listener_new("Petya", 8, GREEN);
	listener_setNotifiers(l2, notify_addPrint2, notify_removePrint2, notify_addTransfer2, notify_removeTransfer2, notify_processing2, notify_overflow2);
	listener_t l3 = listener_new("Ivan", 16, BLUE);
	listener_setNotifiers(l3, notify_addPrint1, notify_removePrint2, NULL, NULL, NULL, notify_overflow1);
	queueSet_addListener(set, l1);
	queueSet_addListener(set, l2);
	queueSet_addListener(set, l3);
	queueSet_endlessIOLoop(set);
	
	listener_delete(l1);
	listener_delete(l2);
	queueSet_delete(set);
	

	return EXIT_SUCCESS;
}