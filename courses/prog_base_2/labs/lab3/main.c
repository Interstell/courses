#include "queue.h"
#include "queueset.h"
#include "gui.h"

int main(void){
	srand(time(NULL));
	gui_changeSize();
	//queue_runTests();
	/*listener_t listener = listener_new("Vasya", 3, 12);
	addPrint1(listener, 1, 3);*/

	queueSet_t set = queueSet_new();
	queueSet_initialize(set);
	listener_t l1 = listener_new("Vasya", 0, GREEN);
	listener_setCallbacks(l1, addPrint1, removePrint1, addPrint_transfer1, removePrint_transfer1, NULL, NULL);
	listener_t l2 = listener_new("Petya", 10, RED);
	listener_setCallbacks(l2, addPrint2, removePrint2, addPrint_transfer2, removePrint_transfer2, NULL, NULL);
	queueSet_addListener(set, l1);
	queueSet_addListener(set, l2);
	queueSet_endlessIOLoop(set);
	
	listener_delete(l1);
	listener_delete(l2);
	

	return EXIT_SUCCESS;
}