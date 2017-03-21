#ifndef QUEUE
#define QUEUE

typedef struct QueueElement {
	struct QueueElement* next;
	void* data;
} QueueElement;

typedef struct Queue {
	QueueElement* first;
	QueueElement* last;
} Queue;

Queue* queueCreate();

void* queueFirst(Queue* queue);

void queueEnqueue(Queue* queue, void* data);

void* queueDequeue(Queue* queue);

int queueIsEmpty(Queue* queue);

void queueDestroy(Queue* queue);

#endif