#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h";

/* Parses input data, checks validation. Return verticies array and number of it with SUCCESS status code
or with another status code in case of parsing failure. */
InitializationResult* initialize(FILE* in) {
	InitializationResult* result = malloc(sizeof(InitializationResult));
	result->verticies = NULL;
	result->verticiesN = 0;

	int verticiesN, edgesN;
	short i, from;
	Vertex* verticies;
	Edge* buf;

	if (-1 == fscanf(in, "%d ", &verticiesN)) {
		result->statusCode = INIT_BAD_LINES_NUMBER;
		return result;
	}
	if ((verticiesN < 0) || (verticiesN > maxVertices)) {
		result->statusCode = INIT_BAD_VERTEX_NUMBER;
		return result;
	}
	verticies = (Vertex*)malloc(sizeof(Vertex)* verticiesN);
	for (i = 0; i < verticiesN; i++) {
		verticies[i].edges = NULL;
		verticies[i].number = i + 1;
	}

	if (-1 == fscanf(in, "%d ", &edgesN)) {
		result->statusCode = INIT_BAD_LINES_NUMBER;
		return result;
	}
	if ((edgesN < 0) || (edgesN > maxEdges(verticiesN))) {
		result->statusCode = INIT_BAD_EDGES_NUMBER;
		return result;
	}
	for (i = 0; i < edgesN; i++) {
		buf = (Edge*)malloc(sizeof(Edge));
		if (EOF == fscanf(in, "%d %d ", &from, &buf->to)) {
			result->statusCode = INIT_BAD_LINES_NUMBER;
			return result;
		}
		if (((from < 0) || (from > verticiesN)) ||
			((buf->to < 0) || (buf->to > verticiesN))) {
			result->statusCode = INIT_BAD_VERTEX;
			return result;
		}

		buf->next = verticies[from - 1].edges;
		verticies[from - 1].edges = buf;
	}

	result->verticies = verticies;
	result->verticiesN = verticiesN;
	result->statusCode = INIT_SUCCESS;

	return result;
}