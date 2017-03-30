#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

Queue* queueCreate() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->first = NULL;
	queue->last = NULL;
	return queue;
}

void* queueFirst(Queue* queue) {
	if (!queueIsEmpty(queue)) {
		return queue->first->data;
	}

	return NULL;
}

void queueEnqueue(Queue* queue, void* data) {
	QueueElement* element = (QueueElement*)malloc(sizeof(QueueElement));
	element->next = NULL;
	element->data = data;
	if (!queue->first) {
		queue->first = element;
	}

	if (!queue->last) {
		queue->last = element;
	}
	else {
		queue->last->next = element;
		queue->last = element;
	}
}

void* queueDequeue(Queue* queue) {
	if (queue->first) {
		void* data = queue->first->data;
		QueueElement* firstElement = queue->first;
		if (queue->last == firstElement) {
			queue->last = NULL; // dequeueing last element case.
		}
		queue->first = firstElement->next;
		free(firstElement);
		return data;
	}
	return NULL;
}

int queueIsEmpty(Queue* queue) {
	if (queue) {
		if (queue->first) {
			return 0;
		}
	}

	return 1;
}

void queueDestroy(Queue* queue) {
	while (!queueIsEmpty(queue)) {
		queueDequeue(queue);
	}
	free(queue);
}