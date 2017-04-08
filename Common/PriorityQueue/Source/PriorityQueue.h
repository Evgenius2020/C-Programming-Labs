#ifndef PRIOR_QUEUE
#define PRIOR_QUEUE

typedef unsigned int t_index;
typedef long long t_key;

typedef struct PriorQueueElement {
	t_key key;
	void* value;
	t_index* index;
} PriorQueueElement;

typedef struct PriorQueue {
	t_index length;
	PriorQueueElement* elements;
} PriorQueue;

PriorQueue* priorQueueCreate(t_index length); /* Returns initialized priority queue. */

void priorQueueDestroy(PriorQueue* priorQueue); /* Releases engaged memory. */

char priorQueueIsEmpty(PriorQueue* priorQueue); /* 0 - if priorityQueue has 0 elements or 1 if it has any */

t_index priorQueueInsert(PriorQueue* priorQueue, void* value, t_key key, t_index* indexPtr); /* Inserts element designated by key. */

t_index priorQueueUpdateKey(PriorQueue* priorQueue, t_index index, t_key key);

void* priorQueueExtractMin(PriorQueue* priorQueue); /* Returns minimal key element's value. */

t_key priorQueueGetMinKey(PriorQueue* priorQueue);

void* priorQueueGetMinValue(PriorQueue* priorQueue);

#endif