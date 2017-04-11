#include <stdlib.h>
#include "PriorityQueue.h"

PriorQueue* priorQueueCreate(t_index length) {
	PriorQueue* priorQueue = malloc(sizeof(PriorQueue));
	priorQueue->elements = calloc(length, sizeof(PriorQueueElement));
	priorQueue->length = 0;

	return priorQueue;
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

void swapElements(PriorQueue* priorQueue, t_index el1, t_index el2) {
	PriorQueueElement buf;

	if (priorQueue->elements[el1].index) {
		*priorQueue->elements[el1].index = el2;
	}
	if (priorQueue->elements[el2].index) {
		*priorQueue->elements[el2].index = el1;
	}

	buf = priorQueue->elements[el1];
	priorQueue->elements[el1] = priorQueue->elements[el2];
	priorQueue->elements[el2] = buf;
}

t_index heapify(PriorQueue* priorQueue, t_index index) {
	t_index left = 2 * index;
	t_index right = 2 * index + 1;
	t_index smallest = index;
	PriorQueueElement* mass = priorQueue->elements;
	PriorQueueElement buf;

	if ((left <= priorQueue->length) && (mass[left - 1].key < mass[smallest - 1].key)) {
		smallest = left;
	}
	if ((right <= priorQueue->length) && (mass[right - 1].key < mass[smallest - 1].key)) {
		smallest = right;
	}
	if (smallest != index) {
		swapElements(priorQueue, index - 1, smallest - 1);
		return heapify(priorQueue, smallest);
	}

	return index - 1;
}

t_index priorQueueInsert(PriorQueue* priorQueue, void* value, t_key key, t_index* indexPtr) {
	t_index i = ++priorQueue->length;
	priorQueue->elements[i - 1].key = key;
	priorQueue->elements[i - 1].value = value;
	priorQueue->elements[i - 1].index = indexPtr;
	while ((i > 1) && (priorQueue->elements[i / 2 - 1].key > priorQueue->elements[i - 1].key)) {
		swapElements(priorQueue, i - 1, i / 2 - 1);
		i /= 2;
	}

	return i;
}

t_index priorQueueUpdateKey(PriorQueue* priorQueue, t_index index, t_key key) {
	if ((!priorQueue) || (index >= priorQueue->length)) {
		return index;
	}
	priorQueue->elements[index].key = key;
	while ((index > 1) && (priorQueue->elements[index / 2 - 1].key > priorQueue->elements[index - 1].key)) {
		swapElements(priorQueue, index - 1, index / 2 - 1);
		index /= 2;
	}

	return index;
}

void* priorQueueExtractMin(PriorQueue* priorQueue) {
	if (!priorQueue->length) {
		return NULL;
	}

	void* minValue = priorQueue->elements[0].value;
	priorQueue->length--;
	priorQueue->elements[0] = priorQueue->elements[priorQueue->length];
	if (priorQueue->elements[0].index) {
		*priorQueue->elements[0].index = 0;
	}
	heapify(priorQueue, 1);

	return minValue;
}

t_key priorQueueGetMinKey(PriorQueue* priorQueue) {
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