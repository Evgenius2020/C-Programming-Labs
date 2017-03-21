#ifndef PRIOR_QUEUE
#define PRIOR_QUEUE

#define PRIOR_QUEUE_SIZE 256 /* Uses size-fixed array.*/

typedef struct PriorQueueElement {
	int key;
	void* value;
} PriorQueueElement;

typedef struct PriorQueue {
	unsigned short length;
	PriorQueueElement** elements;
} PriorQueue;

PriorQueue* priorQueueCreate(); /* Returns initialized priority queue.*/

void priorQueueDestroy(PriorQueue* priorQueue); /* Releases engaged memory.*/

void priorQueueInsert(PriorQueue* priorQueue, void* value, int key); /* Inserts element designated by key.*/

PriorQueueElement* priorQueueExtractMin(PriorQueue* priorQueue); /* Returns element with minimal key value.*/

#endif