#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h"

#define maxVertices 1000
#define maxEdges(n) n*(n-1)/2
#define exiterror(errorCode) initResult->statusCode = errorCode; free(vertices); return initResult;

/* Parses input data, checks validation. Return verticies array and number of it with SUCCESS status code
or with another status code in case of parsing failure. */
InitializationResult* initialize(FILE* in) {
	InitializationResult* initResult = malloc(sizeof(InitializationResult));
	initResult->vertices = NULL;
	initResult->verticesN = 0;

	int verticiesN, edgesN;
	short i, from;
	Vertex* vertices = NULL;
	Edge* buf;

	if (-1 == fscanf(in, "%d ", &verticiesN)) {
		exiterror(INIT_BAD_LINES_NUMBER);
	}
	if ((verticiesN < 0) || (verticiesN > maxVertices)) {
		exiterror(INIT_BAD_VERTEX_NUMBER);
	}
	vertices = (Vertex*)malloc(sizeof(Vertex)* verticiesN);
	for (i = 0; i < verticiesN; i++) {
		vertices[i].edges = NULL;
		vertices[i].number = i + 1;
	}

	if (-1 == fscanf(in, "%d ", &edgesN)) {
		exiterror(INIT_BAD_LINES_NUMBER);
	}
	if ((edgesN < 0) || (edgesN > maxEdges(verticiesN))) {
		exiterror(INIT_BAD_EDGES_NUMBER);
	}
	for (i = 0; i < edgesN; i++) {
		buf = (Edge*)malloc(sizeof(Edge));
		if (EOF == fscanf(in, "%hi %hi ", &from, &buf->to)) {
			exiterror(INIT_BAD_LINES_NUMBER);
		}
		if (((from < 0) || (from > verticiesN)) ||
			((buf->to < 0) || (buf->to > verticiesN))) {
			exiterror(INIT_BAD_VERTEX);
		}

		buf->next = vertices[from - 1].edges;
		vertices[from - 1].edges = buf;
	}

	initResult->vertices = vertices;
	initResult->verticesN = verticiesN;
	initResult->statusCode = INIT_SUCCESS;

	return initResult;
}