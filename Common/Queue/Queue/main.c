#include <stdio.h>
#include <stdlib.h>
#include "Queue.h";

void main() {
	Queue* queue = queueCreate();

	int* mass = (int*)malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; i++) {
		mass[i] = i + 1;
		printf("%d ", mass[i]);
		queueEnqueue(queue, &mass[i]);
	}

	printf("\n");

	while (!queueIsEmpty(queue)) {
		int* dequeued = (int*)queueDequeue(queue);
		printf("%d ", *dequeued);
	}

	free(mass);
	queueDestroy(queue);
}