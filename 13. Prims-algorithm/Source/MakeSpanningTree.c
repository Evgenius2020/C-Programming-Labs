#include <stdio.h>
#include "DataTypes.h"
#include "PriorityQueue.h"
#include "MakeSpanningTree.h"

short makeSpanningTree(Vertex* vertices, short verticesN, FILE* out) {
	PriorQueue* queue = priorQueueCreate(verticesN*2);
	int currVert;
	int nearest = 1;
	int spannedVertices = 0;
	Edge* buf;

	while (1) {
		spannedVertices++;
		if (spannedVertices == verticesN) {
			break;
		}
		currVert = nearest;
		vertices[currVert - 1].viewed = VIEWED;
		for (buf = vertices[currVert - 1].edges; buf; buf = buf->next) {
			if (vertices[currVert - 1].viewed != vertices[buf->to - 1].viewed) {
				priorQueueInsert(queue, buf, buf->length);
			}
		}
		while (queue->length) {
			buf = (Edge*)priorQueueExtractMin(queue);
			if ((vertices[buf->to - 1].viewed == UNVIEWED) && (vertices[buf->from - 1].viewed == VIEWED)) {
				fprintf(out, "%d %d\n", buf->from, buf->to);
				nearest = buf->to;
				break;
			}
			if ((vertices[buf->from - 1].viewed == UNVIEWED) && (vertices[buf->to - 1].viewed == VIEWED)) {
				fprintf(out, "%d %d\n", buf->to, buf->from);
				nearest = buf->from;
				break;
			}
		}
		if (nearest == currVert) {
			break;
		}
	}
	priorQueueDestroy(queue);

	return spannedVertices;
}