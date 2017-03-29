#include <stdlib.h>
#include "DataTypes.h"
#include "PriorityQueue.h"
#include "CalculateDistances.h"

void calculateDistances(Vertex* vertices, short verticesN, short start) {
	short currVert = start;
	Edge* buf;
	vertices[currVert - 1].distance = 0;

	PriorQueue* queue = priorQueueCreate(verticesN);
	do {
		vertices[currVert - 1].viewed = VIEWED;
		/* Searching all edges proceeding from 'currVert', rewriting 'length' value if it's longer. */
		for (buf = vertices[currVert - 1].edges; buf != NULL; buf = buf->next) {
			if ((vertices[buf->to - 1].distance == UNITIALIZED) ||
				(vertices[buf->to - 1].distance > vertices[currVert - 1].distance + buf->length)) {
				if (buf->to != buf->from) {
					vertices[buf->to - 1].distance = vertices[currVert - 1].distance + buf->length;
					priorQueueInsert(queue, buf, vertices[buf->to - 1].distance);
				}
			}
		}
		/* Selecting nearest edge. */
		currVert = UNITIALIZED;
		while (queue->length != 0) {
			buf = (Edge*)priorQueueExtractMin(queue);
			if (vertices[buf->to - 1].viewed == UNVIEWED) {
				currVert = buf->to;
				break;
			}
		}
	} while (currVert != UNITIALIZED);
	priorQueueDestroy(queue);
}