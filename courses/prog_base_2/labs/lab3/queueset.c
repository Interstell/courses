#include "queueset.h"
#include "gui.h"
struct queueSet_s{
	queue_t queue1;
	queue_t queue2;
	listener_t listeners[MAX_LISTENERS];
	int numOfListeners;
};

static int getRandomInt(void){
	int randNum = rand() % 199 - 99;
	if (!randNum) randNum += (int)pow(-1, rand() % 2);
	return randNum;
}

queueSet_t queueSet_new(void){
	queueSet_t set = malloc(sizeof(struct queueSet_s));
	set->queue1 = queue_new();
	set->queue2 = queue_new();
	set->numOfListeners = 0;
	return set;
}

void queueSet_delete(queueSet_t self){
	queue_delete(self->queue1);
	queue_delete(self->queue2);
	free(self);
}

void queueSet_initialize(queueSet_t self){
	for (int i = 0; i < 3; i++){
		queue_add(self->queue1, abs(getRandomInt()));
		queue_add(self->queue2, abs(getRandomInt()));
	}
}

void queueSet_addListener(queueSet_t self, listener_t listener){
	self->listeners[self->numOfListeners++] = listener;
}


void queueSet_endlessIOLoop(queueSet_t self){
	while (1){
		if (_kbhit()){
			char c = _getch();
			if (c == VK_ESCAPE) {
				queueSet_delete(self);
				break;
			}
		}
		int queueNum = rand() % 2 + 1;
		queue_t queue = (queueNum == 1) ? self->queue1 : self->queue2;
		queue_t anotherQueue = (queueNum == 1) ? self->queue2 : self->queue1;
		int num = getRandomInt();
		if (num > 0){
			queue_add(queue, num);
			for (int i = 0; i < self->numOfListeners; i++){
				if (self->listeners[i]->addPrint) self->listeners[i]->addPrint(self->listeners[i], queueNum, num);
			}
			if (queue_getSize(queue) > 10){
				if (queue_getSize(anotherQueue) < 9){
					Sleep(SLEEP_TIME);
					int prevElem = queue_remove(queue);
					queue_add(anotherQueue, prevElem);
					for (int i = 0; i < self->numOfListeners; i++){
						if (self->listeners[i]->addPrint_transfer) self->listeners[i]->addPrint_transfer(self->listeners[i], queueNum, prevElem);
					}
				}
				else{
					//removing last elements
					int enqueueMain = queue_remove(queue);
					int enqueueAnother = queue_remove(anotherQueue);
					for (int i = 0; i < self->numOfListeners; i++){
						if (self->listeners[i]->fullOverflow) self->listeners[i]->fullOverflow(self->listeners[i], queueNum, enqueueMain, enqueueAnother);
					}
				}
				
			}
		}
		else{
			int prevNum = queue_remove(queue);
			for (int i = 0; i < self->numOfListeners; i++){
				if (self->listeners[i]->removePrint) self->listeners[i]->removePrint(self->listeners[i], queueNum, prevNum);
			}
			if (queue_getSize(anotherQueue) >= 2){
				Sleep(SLEEP_TIME);
				int transNum = queue_remove(anotherQueue);
				queue_add(queue, transNum);
				for (int i = 0; i < self->numOfListeners; i++){
					if (self->listeners[i]->removePrint_transfer) self->listeners[i]->removePrint_transfer(self->listeners[i], queueNum, transNum);
				}
			}
			else{
				//normalizing to three elem/queue
				int num11 = abs(getRandomInt());
				int num12 = abs(getRandomInt());
				int num13 = abs(getRandomInt());
				int num22 = abs(getRandomInt());
				int num23 = abs(getRandomInt());
				queue_add(queue, num11);
				queue_add(queue, num12);
				queue_add(queue, num13);
				queue_add(anotherQueue, num22);
				queue_add(anotherQueue, num23);
				for (int i = 0; i < self->numOfListeners; i++){
					if (self->listeners[i]->fullProcessing) self->listeners[i]->fullProcessing(self->listeners[i], queueNum, num11, num12, num13, num22, num23);
				}
			}
						
		}
		Sleep(SLEEP_TIME);
	}
}


