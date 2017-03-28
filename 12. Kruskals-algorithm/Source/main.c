#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h"

Vertex* makeSet() {
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	vertex->leader = vertex;

	return vertex;
}

Vertex* findSet(Vertex* vertex) {
	Vertex* buf = vertex->leader;
	while (buf->leader != buf) {
		vertex->leader = buf->leader;
		buf = buf->leader;
	}

	return vertex->leader;
}

void unionSets(Vertex* of, Vertex* into) {
	findSet(of)->leader = findSet(into);
}

int compareEdges(Edge* left, Edge* right) {
	return left->length - right->length;
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	if ((!in) || (!out)) {
		return;
	}

	InitializationResult result = initalize();
	qsort(result.edges, result.edgesN, sizeof(Edge), compareEdges)

	/* Making a spanning tree.*/
	while (queue->length) {
		buf = (Edge*)priorQueueExtractMin(queue);
		if (findSet(&vertices[buf->from - 1]) != (findSet(&vertices[buf->to - 1]))) {
			unionSets(findSet(&vertices[buf->from - 1]), findSet(&vertices[buf->to - 1]));
			fprintf(out, "%d %d\n", buf->from, buf->to);
		}
		free(buf);
	}

	/*Checking that all vertices are in the tree.*/
	for (i = 0; i < verticesN - 1; i++) {
		if (findSet(&vertices[i]) != findSet(&vertices[i + 1])) {
			fclose(out);
			out = fopen("out.txt", "w");
			fprintf(out, "no spanning tree\n");
			break;
		}
	}
}