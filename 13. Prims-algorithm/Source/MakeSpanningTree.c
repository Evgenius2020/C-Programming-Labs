#include <stdio.h>
#include "DataTypes.h"
#include "PriorityQueue.h"
#include "MakeSpanningTree.h"

short makeSpanningTree(Vertex* vertices, short verticesN, FILE* out) {
	if (!verticesN) {
		return -1;
	}
	PriorQueue* priorQueue = priorQueueCreate(verticesN);
	Edge* spanningTree = NULL;
	Vertex* currVert;
	Edge* buf;
	short i, spannedVertices = 1;

	priorQueueInsert(priorQueue, &vertices[0], 0, &vertices[0].queueIndex);
	for (i = 1; i < verticesN; i++) {
		priorQueueInsert(priorQueue, &vertices[i], INF, &vertices[i].queueIndex);
	}
	while (priorQueue->length) {
		currVert = (Vertex*)priorQueueExtractMin(priorQueue);
		currVert->viewed = VIEWED;
		for (buf = currVert->edges; buf; buf = buf->next) {
			if ((vertices[buf->to - 1].viewed == UNVIEWED) && (buf->length < priorQueue->elements[vertices[buf->to - 1].queueIndex].key)) {
				priorQueueUpdateKey(priorQueue, vertices[buf->to - 1].queueIndex, buf->length);
				vertices[buf->to - 1].nearest = currVert->number;
			}
		}
		if (currVert->nearest != NO_NEAREST) {
			fprintf(out, "%d %d\n", currVert->number, currVert->nearest);
			spannedVertices++;
		}
	}

	priorQueueDestroy(priorQueue);
	return spannedVertices;
}