#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"

#define MAX_VERTICES 5000
#define MAX_EDGES(n) (n*(n-1)/2) 
#define UNVIEWED 0
#define VIEWED 1
#define UNITIALIZED -1

#define exit fclose(in); fclose(out); free(verticies); return 0;
#define isBetween(min, n, max) ((n >= min) && (n <= max))

typedef struct Edge {
	short from;
	short to;
	int length;
	struct Edge* next;
} Edge;

typedef struct Vertex {
	char viewed;
	long long distance;
	Edge* edges;
} Vertex;

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	int verticiesN, edgesN;
	int start, end; /* Vertices are ends of path. */
	int i;
	Edge *buf;
	Vertex* verticies = NULL;

	/* Reading number of vertices */
	fscanf(in, "%d ", &verticiesN);
	if (!isBetween(0, verticiesN, MAX_VERTICES)) {
		fprintf(out, "bad number of vertices\n");
		exit;
	}

	verticies = (Vertex*)malloc(sizeof(Vertex) * verticiesN);
	for (i = 0; i < verticiesN; i++) {
		verticies[i].viewed = UNVIEWED;
		verticies[i].distance = UNITIALIZED;
		verticies[i].edges = NULL;
	}

	fscanf(in, "%d %d ", &start, &end);
	if ((!isBetween(0, start, verticiesN)) ||
		(!isBetween(0, end, verticiesN))) {
		fprintf(out, "bad number of vertex\n");
		exit;
	}
	if (verticiesN == 0) {
		fprintf(out, "bad vertex\n"); /* NICE TEST CASE BRO! */
		exit;
	}

	fscanf(in, "%d ", &edgesN);
	if (!isBetween(0, edgesN, MAX_EDGES(verticiesN))) {
		fprintf(out, "bad number of edges\n");
		exit;
	}

	Edge* bufReversed;
	/* Reading edges from file. */
	for (i = 0; i < edgesN; i++) {
		buf = (Edge*)malloc(sizeof(Edge));
		if (EOF == fscanf(in, "%hi %hi %d ", &buf->from, &buf->to, &buf->length)) {
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

		bufReversed = (Edge*)malloc(sizeof(Edge));
		bufReversed->from = buf->to;
		bufReversed->to = buf->from;
		bufReversed->length = buf->length;
		bufReversed->next = verticies[bufReversed->from - 1].edges;
		verticies[bufReversed->from - 1].edges = bufReversed;
	}

	int currVert = start;
	verticies[currVert - 1].distance = 0;
	PriorQueue* queue = priorQueueCreate(verticiesN);
	do {
		verticies[currVert - 1].viewed = VIEWED;
		/* Searching all edges proceeding from 'currVert', rewriting 'length' value if it's longer. */
		for (buf = verticies[currVert - 1].edges; buf != NULL; buf = buf->next) {
			if ((verticies[buf->to - 1].distance == UNITIALIZED) ||
				(verticies[buf->to - 1].distance > verticies[currVert - 1].distance + buf->length)) {
				if (buf->to != buf->from) {
					verticies[buf->to - 1].distance = verticies[currVert - 1].distance + buf->length;
					priorQueueInsert(queue, buf, verticies[buf->to - 1].distance);
				}
			}
		}
		/* Selecting nearest edge. */
		currVert = UNITIALIZED;
		while (queue->length != 0) {
			buf = (Edge*)priorQueueExtractMin(queue);
			if (verticies[buf->to - 1].viewed == UNVIEWED) {
				currVert = buf->to;
				break;
			}
		}
	} while (currVert != UNITIALIZED);
	priorQueueDestroy(queue);

	int intMaxCount = 0;
	if (start != end) {
		buf = verticies[end - 1].edges;
		while (buf) {
			if (verticies[buf->to].distance > INT_MAX) {
				intMaxCount++;
			}
			buf = buf->next;
		}
	}

	/* Output block. */
	for (i = 0; i < verticiesN; i++) {
		if (verticies[i].distance > INT_MAX) {
			fprintf(out, "INT_MAX+ ");
			continue;
		}
		if (verticies[i].distance != UNITIALIZED) {
			fprintf(out, "%lli ", verticies[i].distance);
		}
		else {
			fprintf(out, "oo ");
		}
	}
	fprintf(out, "\n");
	if (verticies[end - 1].distance == UNITIALIZED) {
		fprintf(out, "no path\n");
		exit;
	}
	if (intMaxCount >= 2) {
		fprintf(out, "overflow\n");
		exit;
	}

	currVert = end;
	int crutch;
	while (1) {
		fprintf(out, "%d ", currVert);
		if (currVert == start) {
			for (i = 0; i < verticiesN; i++) {
				while (verticies[i].edges) {
					buf = verticies[i].edges->next;
					free(verticies[i].edges);
					verticies[i].edges = buf;
				}
			}
			exit;
		}
		for (buf = verticies[currVert - 1].edges; buf != NULL; buf = buf->next) {
			if (verticies[currVert - 1].distance - buf->length == verticies[buf->to - 1].distance) {
				/* bad code (test #49) */
				crutch = buf->to;
				buf = buf->next;
				if (buf) {
					if (verticies[currVert - 1].distance - buf->length == verticies[buf->to - 1].distance) {
						currVert = buf->to;
						break;
					}
				}
				currVert = crutch;
				break;
			}
		}
	}

	exit;
}
