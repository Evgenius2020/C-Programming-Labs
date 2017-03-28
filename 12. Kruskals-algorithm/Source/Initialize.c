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
	Edge* edges;

	/* Reading number of vertices*/
	fscanf(in, "%d ", &verticesN);
	if (!isBetween(0, verticesN, MAX_VERTICES)) {
		result.statusCode = INIT_BAD_VERTICIES_NUMBER;
		return result;
	}

	vertices = (Vertex*)malloc(sizeof(Vertex) * verticesN);
	int newSetNumber = 1;
	for (i = 0; i < verticesN; i++) {
		vertices[i].leader = &vertices[i];
	}

	fscanf(in, "%d ", &edgesN);
	if (!isBetween(0, edgesN, MAX_EDGES(verticesN))) {
		result.statusCode = INIT_BAD_EDGES_NUMBER;
		return result;
	}
	edges = (Edge*)malloc(sizeof(Edge)*edgesN);

	/*Reading edges from file.*/
	for (i = 0; i < edgesN; i++) {
		if (EOF == fscanf(in, "%d %d %d ", &(edges[i].from), &(edges[i].to), &(edges[i].length))) {
			result.statusCode = INIT_BAD_LINES_NUMBER;
			return result;
		}
		if ((!isBetween(1, edges[i].from, verticesN)) ||
			(!isBetween(1, edges[i].to, verticesN))) {
			result.statusCode = INIT_BAD_VERTEX;
			return result;
		}
		if (!isBetween(0, edges[i].length, INT_MAX)) {
			result.statusCode = INIT_BAD_LENGTH;
			return result;
		}
	}

	result.edgesN = edgesN;
	result.verticies = vertices;
	result.verticiesN = verticesN;
	result.statusCode = INIT_SUCCESS;
	return result;
}