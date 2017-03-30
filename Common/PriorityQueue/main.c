#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Source\PriorityQueue.h"

typedef struct TestStruct {
	int value;
} TestStruct;

void main() {
	PriorQueue* queue = priorQueueCreate(10);
	int key, i;
	TestStruct* buf;
	srand(time(NULL));

	for (i = 0; i < 5; i++) {
		buf = (TestStruct*)malloc(sizeof(TestStruct));
		buf->value = rand();
		key = rand();
		priorQueueInsert(queue, buf, key);
		printf("Inserted '%d' with key '%d\n", buf->value, key);
	}

	while (!priorQueueIsEmpty(queue)) {
		buf = priorQueueGetMinValue(queue);
		key = priorQueueGetMinKey(queue);
		priorQueueExtractMin(queue);
		printf("Extracted '%d' with key '%d'\n", buf->value, key);
	}

	priorQueueDestroy(queue);
}