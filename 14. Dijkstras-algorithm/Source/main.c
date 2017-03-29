#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Output.h"
#include "DataTypes.h"
#include "Initialize.h"
#include "CalculateDistances.h"

void destroyVertices(Vertex* vertices, short verticesN) {
	short i;
	Edge* buf;

	for (i = 0; i < verticesN; i++) {
		while (vertices[i].edges) {
			buf = vertices[i].edges->next;
			free(vertices[i].edges);
			vertices[i].edges = buf;
		}
	}
	free(vertices);
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	if ((!in) || (!out)) {
		return;
	}

	InitializationResult initResult = initialize(in);
	if (initResult.statusCode == INIT_SUCCESS) {
		calculateDistances(initResult.vertices, initResult.verticesN, initResult.start);
		printDistances(initResult.vertices, initResult.verticesN, out);
		printPath(initResult.vertices, initResult.start, initResult.end, out);
		destroyVertices(initResult.vertices, initResult.verticesN);
	}
	else {
		if (initResult.statusCode == INIT_BAD_EDGES_NUMBER) {
			fprintf(out, "bad number of edges\n");
		}
		if (initResult.statusCode == INIT_BAD_LENGTH) {
			fprintf(out, "bad length\n");
		}
		if (initResult.statusCode == INIT_BAD_LINES_NUMBER) {
			fprintf(out, "bad number of lines\n");
		}
		if (initResult.statusCode == INIT_BAD_VERTEX) {
			fprintf(out, "bad vertex\n");
		}
		if (initResult.statusCode == INIT_BAD_VERTICES_NUMBER) {
			fprintf(out, "bad number of vertices\n");
		}
	}

	fclose(in);
	fclose(out);
}