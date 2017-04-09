#include <stdlib.h>
#include "DataTypes.h"
#include "PriorityQueue.h"
#include "CalculateDistances.h"

void calculateDistances(Vertex* vertices, short verticesN, short start) {
	PriorQueue* priorQueue = priorQueueCreate(verticesN);
	Vertex* currVert;
	short i;
	Edge* buf;

	vertices[start - 1].distance = 0;
	vertices[start - 1].parent = &vertices[start - 1];
	for (i = 0; i < verticesN; i++) {
		priorQueueInsert(priorQueue, &vertices[i], vertices[i].distance, &vertices[i].index);
	}
	while (priorQueue->length) {
		currVert = (Vertex*)priorQueueExtractMin(priorQueue);
		currVert->viewed = VIEWED;
		for (buf = currVert->edges; buf; buf = buf->next) {
			if (vertices[buf->to - 1].viewed == VIEWED) {
				continue;
			}
			if (vertices[buf->to - 1].distance >= currVert->distance + buf->length) {
				vertices[buf->to - 1].distance = currVert->distance + buf->length;
				priorQueueUpdateKey(priorQueue, vertices[buf->to - 1].index, vertices[buf -> to - 1].distance);
				vertices[buf->to - 1].parent = currVert;
			}
		}
	}

	priorQueueDestroy(priorQueue);
}