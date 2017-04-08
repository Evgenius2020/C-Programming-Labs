#include <stdio.h>
#include "DataTypes.h"
#include "PriorityQueue.h"
#include "MakeSpanningTree.h"

short makeSpanningTree(Vertex* vertices, short verticesN, FILE* out) {
	if (!verticesN) {
		return -1;
	}
	PriorQueue* queue = priorQueueCreate(verticesN);
	short nearest = 1;
	int spannedVertices = 0;
	Edge* buf;
	Vertex* curr;

	while (1) {
		for (buf = vertices[nearest - 1].edges; buf; buf = buf->next) {
			if (vertices[buf->to - 1].viewed == UNVIEWED) {
				priorQueueInsert(queue, &vertices[buf->to - 1], buf->length);
			}
		}
		while (!priorQueueIsEmpty(queue)) {
			if (((Vertex*)priorQueueGetMinValue)->viewed == VIEWED) {
				priorQueueExtractMin(queue);
			}
			curr = (Vertex*)priorQueueExtractMin(queue);
			if (curr) {
				fprintf(out, "%d ", nearest);
				fprintf(out, "%d\n", curr->number);
				curr->viewed = VIEWED;
				spannedVertices++;
			}
		}
	}

	priorQueueDestroy(queue);
	return spannedVertices;
}