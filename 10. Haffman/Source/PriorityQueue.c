#include <stdlib.h>
#include "PriorityQueue.h"

PriorQueue* priorQueueCreate() {
	PriorQueue* queue = (PriorQueue*)malloc(sizeof(PriorQueue));
	queue->elements = calloc(PRIOR_QUEUE_SIZE, sizeof(PriorQueueElement*));
	queue->length = 0;

	return queue;
}

void priorQueueDestroy(PriorQueue* priorQueue) {
	free(priorQueue->elements);
	free(priorQueue);
}

void priorQueueInsert(PriorQueue* priorQueue, void* value, int key) {
	priorQueue->length++;
	unsigned short i = priorQueue->length - 1;
	priorQueue->elements[i] = malloc(sizeof(PriorQueueElement));
	priorQueue->elements[i]->key = key;
	priorQueue->elements[i]->value = value;
	PriorQueueElement* buf;
	while ((i > 0) &&
		(priorQueue->elements[i / 2]->key > priorQueue->elements[i]->key)) {
		buf = priorQueue->elements[i / 2];
		priorQueue->elements[i / 2] = priorQueue->elements[i];
		priorQueue->elements[i] = buf;
		i /= 2;
	}
}

PriorQueueElement* priorQueueExtractMin(PriorQueue* priorQueue) {
	if (!priorQueue->length) {
		return NULL;
	}

	PriorQueueElement* min = priorQueue->elements[0];
	priorQueue->length--;
	priorQueue->elements[0] = priorQueue->elements[priorQueue->length];
	priorQueue->elements[priorQueue->length] = NULL;

	/* Heapifying. */
	PriorQueueElement* buf;
	int i = 0;
	int smallest, left, right;
	while (1) {
		smallest = i;
		left = smallest * 2 + 1;
		right = smallest * 2 + 2;
		if ((left < priorQueue->length) &&
			(priorQueue->elements[left]->key < priorQueue->elements[smallest]->key)) {
			smallest = left;
		}
		if ((right < priorQueue->length) &&
			(priorQueue->elements[right]->key < priorQueue->elements[smallest]->key)) {
			smallest = right;
		}
		if (smallest != i) {
			buf = priorQueue->elements[i];
			priorQueue->elements[i] = priorQueue->elements[smallest];
			priorQueue->elements[smallest] = buf;
			i = smallest;
		}
		else {
			break;
		}
	}

	return min;
}