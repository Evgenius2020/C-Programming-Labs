#include <stdio.h>
#include <stdlib.h>
#include "../../Common/PriorityQueue/Source/PriorityQueue.c"

#define isBetween(min, n, max) ((n >= min) && (n <= max))
#define MAX_VERTICES 5000
#define MAX_EDGES(n) (n*(n-1)/2) 
#define exit fclose(in); fclose(out); free(vertices); return 0;

typedef struct Edge {
	short from;
	short to;
	int length;
} Edge;

typedef struct Vertex {
	struct Vertex* leader;
} Vertex;

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

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	int verticesN;
	int edgesN;
	int i, j;
	Vertex* vertices = NULL;
	Edge* buf;

	/* Reading number of vertices*/
	fscanf(in, "%d ", &verticesN);
	if (!isBetween(0, verticesN, MAX_VERTICES)) {
		fprintf(out, "bad number of vertices\n");
		exit;
	}
	if (verticesN == 0) {
		fprintf(out, "no spanning tree\n");
		exit;
	}

	vertices = (Vertex*)malloc(sizeof(Vertex) * verticesN);
	int newSetNumber = 1;
	for (i = 0; i < verticesN; i++) {
		vertices[i] = *makeSet();
	}

	fscanf(in, "%d ", &edgesN);
	if (!isBetween(0, edgesN, MAX_EDGES(verticesN))) {
		fprintf(out, "bad number of edges\n");
		exit;
	}

	/*Reading edges from file.*/
	PriorQueue* queue = priorQueueCreate(edgesN);
	for (i = 0; i < edgesN; i++) {
		buf = (Edge*)malloc(sizeof(Edge));
		if (EOF == fscanf(in, "%d %d %d ", &(buf->from), &(buf->to), &(buf->length))) {
			fprintf(out, "bad number of lines\n");
			exit;
		}
		if ((!isBetween(1, buf->from, verticesN)) ||
			(!isBetween(1, buf->to, verticesN))) {
			fprintf(out, "bad vertex\n");
			exit;
		}
		if (!isBetween(0, buf->length, INT_MAX)) {
			fprintf(out, "bad length\n");
			exit;
		}
		priorQueueInsert(queue, buf, buf->length);
	}

	/* Making a spanning tree.*/
	int oldSetNumber; /* buffer for merging sets*/
	while (queue->length) {
		buf = (Edge*)priorQueueExtractMin(queue);
		if (findSet(&vertices[buf->from - 1]) != (findSet(&vertices[buf->to - 1]))) {
			unionSets(findSet(&vertices[buf->from - 1]), findSet(&vertices[buf->to - 1]));
			fprintf(out, "%d %d\n", buf->from, buf->to);
		}
		free(buf);
	}
	priorQueueDestroy(queue);

	/*Checking that all vertices are in the tree.*/
	for (i = 0; i < verticesN - 1; i++) {
		if (findSet(&vertices[i]) != findSet(&vertices[i + 1])) {
			fclose(out);
			out = fopen("out.txt", "w");
			fprintf(out, "no spanning tree\n");
			break;
		}
	}

	exit;
}