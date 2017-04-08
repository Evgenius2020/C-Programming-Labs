#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Initialize.h"

#define isBetween(min, n, max) ((n >= min) && (n <= max))
#define MAX_VERTICES 5000
#define MAX_EDGES(n) (n*(n-1)/2) 

InitializationResult initialize(FILE* in) {
	InitializationResult result;
	int i, verticesN, edgesN;
	Vertex* vertices;
	Edge* buf;
	Edge* bufReversed;

	/* Reading number of vertices*/
	fscanf(in, "%d ", &verticesN);
	if (!isBetween(0, verticesN, MAX_VERTICES)) {
		result.statusCode = INIT_BAD_VERTICES_NUMBER;
		return result;
	}

	vertices = (Vertex*)calloc(sizeof(Vertex), verticesN);
	for (i = 0; i < verticesN; i++) {
		vertices[i].viewed = UNVIEWED;
		vertices[i].edges = NULL;
		vertices[i].number = i + 1;
	}

	fscanf(in, "%d ", &edgesN);
	if (!isBetween(0, edgesN, MAX_EDGES(verticesN))) {
		result.statusCode = INIT_BAD_EDGES_NUMBER;
		return result;
	}

	/*Reading edges from file.*/
	for (i = 0; i < edgesN; i++) {
		buf = (Edge*)malloc(sizeof(Edge));
		if (EOF == fscanf(in, "%d %d %d ", &(buf->from), &(buf->to), &(buf->length))) {
			result.statusCode = INIT_BAD_LINES_NUMBER;
			return result;
		}
		if ((!isBetween(1, buf->from, verticesN)) ||
			(!isBetween(1, buf->to, verticesN))) {
			result.statusCode = INIT_BAD_VERTEX;
			return result;
		}
		if (!isBetween(0, buf->length, INT_MAX)) {
			result.statusCode = INIT_BAD_LENGTH;
			return result;
		}
		buf->next = vertices[buf->from - 1].edges;
		vertices[buf->from - 1].edges = buf;
		bufReversed = (Edge*)malloc(sizeof(Edge));
		bufReversed->length = buf->length;
		bufReversed->to = buf->from;
		bufReversed->from = buf->to;
		bufReversed->next = vertices[buf->to - 1].edges;
		vertices[buf->to - 1].edges = bufReversed;
	}

	result.vertices = vertices;
	result.verticesN = verticesN;
	result.statusCode = INIT_SUCCESS;
	return result;
}