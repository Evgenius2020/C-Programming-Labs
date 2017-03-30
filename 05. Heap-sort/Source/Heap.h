#ifndef PRIOR_QUEUE
#define PRIOR_QUEUE

typedef struct Heap {
	unsigned int length;
	int* elements;
} Heap;

Heap* heapCreate(unsigned int length); /* Returns initialized priority queue.*/

void heapDestroy(Heap* priorQueue); /* Releases engaged memory.*/

void heapInsert(Heap* priorQueue, int key); /* Inserts element designated by key.*/

int heapExtractMin(Heap* priorQueue); /* Returns element with minimal key value.*/

#endif