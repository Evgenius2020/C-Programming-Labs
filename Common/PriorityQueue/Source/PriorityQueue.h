#ifndef PRIOR_QUEUE
#define PRIOR_QUEUE

typedef struct PriorQueueElement {
	int key;
	void* value;
} PriorQueueElement;

typedef struct PriorQueue {
	unsigned int length;
	PriorQueueElement* elements;
} PriorQueue;

PriorQueue* priorQueueCreate(int length);
/* Returns initialized priority queue. */

void priorQueueDestroy(PriorQueue* priorQueue); /* Releases engaged memory. */

char priorQueueIsEmpty(PriorQueue * priorQueue); /* 0 - if priorityQueue has 0 elements or 1 if it has any */

void priorQueueInsert(PriorQueue* priorQueue, void* value, int key); /* Inserts element designated by key. */

void* priorQueueExtractMin(PriorQueue* priorQueue); /* Returns element with minimal key value. */

int priorQueueGetMinKey(PriorQueue* priorQueue);

void* priorQueueGetMinValue(PriorQueue* priorQueue);

#endif