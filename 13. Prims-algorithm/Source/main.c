#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

#define MAX_VERTICES 5000
#define MAX_EDGES(n) (n*(n-1)/2) 
#define UNVIEWED 0
#define VIEWED 1
#define UNINITIALIZED -1

#define exit fclose(in); fclose(out); destroyVerticies(verticies, verticiesN); return 0;
#define isBetween(min, n, max) ((n >= min) && (n <= max))

typedef struct Edge {
	short from;
	short to;
	int length;
	struct Edge* next;
} Edge;

typedef struct Vertex {
	char viewed;
	Edge* edges;
} Vertex;

void destroyVerticies(Vertex* verticies, int vertriciesN) {
	if (!verticies) {
		return;
	}

	int i;
	Edge* buf;
	for (i = 0; i < vertriciesN; i++) {
		while (verticies[i].edges) {
			buf = verticies[i].edges->next;
			free(verticies[i].edges);
			verticies[i].edges = buf;
		}
	}
	free(verticies);
}

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	Vertex* verticies = NULL;
	int verticiesN;
	int edgesN;
	int i;
	/*Contains viewed state of vertices.*/

	/*Reading number of vertices*/
	fscanf(in, "%d ", &verticiesN);
	if (!isBetween(0, verticiesN, MAX_VERTICES)) {
		fprintf(out, "bad number of vertices\n");
		exit;
	}

	if (verticiesN == 0) {
		fprintf(out, "no spanning tree\n");
		exit;
	}

	verticies = (Vertex*)malloc(sizeof(Vertex) * verticiesN);
	for (i = 0; i < verticiesN; i++) {
		verticies[i].viewed = UNVIEWED;
		verticies[i].edges = NULL;
	}

	fscanf(in, "%d ", &edgesN);
	if (!isBetween(0, edgesN, MAX_EDGES(verticiesN))) {
		fprintf(out, "bad number of edges\n");
		exit;
	}
	Edge* buf;
	Edge* bufReverse;
	/* Reading edges from file.*/
	for (i = 0; i < edgesN; i++) {
		buf = (Edge*)malloc(sizeof(Edge));
		if (EOF == fscanf(in, "%d %d %d ", &(buf->from), &(buf->to), &(buf->length))) {
			fprintf(out, "bad number of lines\n");
			exit;
		}
		if ((!isBetween(1, buf->from, verticiesN)) ||
			(!isBetween(1, buf->to, verticiesN))) {
			fprintf(out, "bad vertex\n");
			exit;
		}
		if (!isBetween(0, buf->length, INT_MAX)) {
			fprintf(out, "bad length\n");
			exit;
		}
		buf->next = verticies[buf->from - 1].edges;
		verticies[buf->from - 1].edges = buf;

		bufReverse = (Edge*)malloc(sizeof(Edge));
		bufReverse->from = buf->to;
		bufReverse->to = buf->from;
		bufReverse->length = buf->length;
		bufReverse->next = verticies[bufReverse->from - 1].edges;
		verticies[bufReverse->from - 1].edges = bufReverse;
	}

	PriorQueue* queue = priorQueueCreate(edgesN);
	int currVert;
	int nearest = 1;
	int viewedVertices = 0;
	while (1) {
		viewedVertices++;
		if (viewedVertices == verticiesN) {
			break;
		}
		currVert = nearest;
		verticies[currVert - 1].viewed = VIEWED;
		for (buf = verticies[currVert - 1].edges; buf; buf = buf->next) {
			if (verticies[currVert - 1].viewed != verticies[buf->to - 1].viewed) {
				priorQueueInsert(queue, buf, buf->length);
			}
		}
		while (queue->length) {
			buf = (Edge*)priorQueueExtractMin(queue);
			if ((verticies[buf->to - 1].viewed == UNVIEWED) && (verticies[buf->from - 1].viewed == VIEWED)) {
				fprintf(out, "%d %d\n", buf->from, buf->to);
				nearest = buf->to;
				break;
			}
			if ((verticies[buf->from - 1].viewed == UNVIEWED) && (verticies[buf->to - 1].viewed == VIEWED)) {
				fprintf(out, "%d %d\n", buf->to, buf->from);
				nearest = buf->from;
				break;
			}
		}
		if (nearest == currVert) {
			break;
		}
	};
	priorQueueDestroy(queue);

	/*Not all vertices is in tree.*/
	if (viewedVertices != verticiesN) {
		fclose(out);
		out = fopen("out.txt", "w");
		fprintf(out, "no spanning tree\n");
	}

	exit;
}
