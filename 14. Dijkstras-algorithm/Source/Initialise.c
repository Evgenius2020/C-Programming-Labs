#include <stdio.h>
#include <stdlib.h>
#include "Initialize.h"
#include "DataTypes.h"

#define MAX_VERTICES 5000
#define MAX_EDGES(n) (n*(n-1)/2) 

InitializationResult initialize(FILE* in) {
	InitializationResult result;
	int verticiesN, edgesN;
	int start, end; /* Vertices are ends of path. */
	int i;
	Edge *buf;
	Edge* bufReversed;
	Vertex* verticies = NULL;

	/* Reading number of vertices */
	fscanf(in, "%d ", &verticiesN);
	if (!isBetween(0, verticiesN, MAX_VERTICES)) {
		result.statusCode = INIT_BAD_VERTICES_NUMBER;
		return result;
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
		result.statusCode = INIT_BAD_VERTEX;
		return result;
	}

	fscanf(in, "%d ", &edgesN);
	if (!isBetween(0, edgesN, MAX_EDGES(verticiesN))) {
		result.statusCode = INIT_BAD_EDGES_NUMBER;
		return result;
	}

	/* Reading edges from file. */
	for (i = 0; i < edgesN; i++) {
		buf = (Edge*)malloc(sizeof(Edge));
		if (EOF == fscanf(in, "%hi %hi %d ", &buf->from, &buf->to, &buf->length)) {
			result.statusCode = INIT_BAD_LINES_NUMBER;
			return result;
		}
		if ((!isBetween(1, buf->from, verticiesN)) ||
			(!isBetween(1, buf->to, verticiesN))) {
			result.statusCode = INIT_BAD_VERTEX;
			return result;
		}
		if (!isBetween(0, buf->length, INT_MAX)) {
			result.statusCode = INIT_BAD_LENGTH;
			return result;
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

	result.vertices = verticies;
	result.verticesN = verticiesN;
	result.statusCode = INIT_SUCCESS;
	return result;
}