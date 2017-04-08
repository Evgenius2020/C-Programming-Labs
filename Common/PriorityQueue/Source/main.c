#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

typedef struct TestStruct {
	int number;
	t_key key;
	t_index index;
} TestStruct;

TestStruct* createStruct(number, key) {
	TestStruct* buf = (TestStruct*)malloc(sizeof(TestStruct));
	buf->number = number;
	buf->key = key;

	return buf;
}

void main() {
	PriorQueue* priorQueue = priorQueueCreate(10);
	int i;
	TestStruct* buf;
	TestStruct** mass = (TestStruct**)malloc(sizeof(TestStruct*)* 5);
	mass[0] = createStruct(34, 323);
	mass[1] = createStruct(-1342, 12333);
	mass[2] = createStruct(22555, -122);
	mass[3] = createStruct(45, 2);
	mass[4] = createStruct(22225, -3);

	for (i = 0; i < 5; i++) {
		mass[i]->index = (t_index)i;
		priorQueueInsert(priorQueue, mass[i], mass[i]->key, &mass[i]->index);
		printf("Inserted '%d' with key '%lli'\n", mass[i]->number, mass[i]->key);
	}

	for (i = 0; i < 5; i++) {
		printf("mass['%d']->index = '%d'\n", i, mass[i]->index);
	}

	while (!priorQueueIsEmpty(priorQueue)) {
		buf = (TestStruct*)priorQueueExtractMin(priorQueue);
		printf("Extracted 'TestStruct' : { '%d', '%lli', '%u' }\n", buf->number, buf->key, buf->index);
	}

	free(mass);
	priorQueueDestroy(priorQueue);
}