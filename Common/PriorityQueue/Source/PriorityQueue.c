#include <stdlib.h>
#include "PriorityQueue.h"

PriorQueue* priorQueueCreate(int length) {
	PriorQueue* queue = (PriorQueue*)malloc(sizeof(PriorQueue));
	queue->elements = calloc(length, sizeof(PriorQueueElement*));
	queue->length = 0;

	return queue;
}

void priorQueueDestroy(PriorQueue* priorQueue) {
	free(priorQueue->elements);
	free(priorQueue);
}

char priorQueueIsEmpty(PriorQueue* priorQueue) {
	if (priorQueue->length == 0) {
		return 1;
	}
	return 0;
}

void priorQueueInsert(PriorQueue* priorQueue, void* value, int key) {
	priorQueue->length++;
	unsigned int i = priorQueue->length - 1;
	priorQueue->elements[i].key = key;
	priorQueue->elements[i].value = value;
	PriorQueueElement buf;
	while ((i > 0) &&
		(priorQueue->elements[i / 2].key > priorQueue->elements[i].key)) {
		buf = priorQueue->elements[i / 2];
		priorQueue->elements[i / 2] = priorQueue->elements[i];
		priorQueue->elements[i] = buf;
		i /= 2;
	}
}

void* priorQueueExtractMin(PriorQueue* priorQueue) {
	if (!priorQueue->length) {
		return NULL;
	}

	void* minValue = priorQueue->elements[0].value;
	priorQueue->length--;
	priorQueue->elements[0] = priorQueue->elements[priorQueue->length];

	/*Heapifying.*/
	PriorQueueElement buf;
	unsigned int i = 0;
	unsigned int smallest, left, right;
	while (1) {
		smallest = i;
		left = smallest * 2 + 1;
		right = smallest * 2 + 2;
		if ((left < priorQueue->length) &&
			(priorQueue->elements[left].key < priorQueue->elements[smallest].key)) {
			smallest = left;
		}
		if ((right < priorQueue->length) &&
			(priorQueue->elements[right].key < priorQueue->elements[smallest].key)) {
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

	return minValue;
}

int priorQueueGetMinKey(PriorQueue* priorQueue) {
	if (priorQueueIsEmpty(priorQueue)) {
		return 0;
	}
	return priorQueue->elements[0].key;
}

void* priorQueueGetMinValue(PriorQueue* priorQueue) {
	if (priorQueueIsEmpty(priorQueue)) {
		return NULL;
	}
	return priorQueue->elements[0].value;
}