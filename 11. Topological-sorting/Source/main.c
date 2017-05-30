#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Stack.h"
#include "Initialize.h"
#include "TopologicalSorting.h"

void dispose(InitializationResult* initResult) {
	int i;
	Edge* buf;
	for (i = 0; i < initResult->verticiesN; i++) {
		while (initResult->verticies[i].edges) {
			buf = initResult->verticies[i].edges->next;
			free(initResult->verticies[i].edges);
			initResult->verticies[i].edges = buf;
		}
	}
	free(initResult->verticies);
	free(initResult);
}

const char* getErrorString(char statusCode) {
	if (statusCode == INIT_BAD_EDGES_NUMBER) {
		return "bad number of edges\n";
	}
	if (statusCode == INIT_BAD_LINES_NUMBER) {
		return "bad number of lines\n";
	}
	if (statusCode == INIT_BAD_VERTEX) {
		return "bad vertex\n";
	}
	if (statusCode == INIT_BAD_VERTEX_NUMBER) {
		return "bad number of vertices\n";
	}
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	if ((!in) || (!out)) {
		return;
	}

	InitializationResult* initResult = initialize(in);
	if (initResult->statusCode == INIT_SUCCESS) {
		Stack* sortedVerticies = topologicalSorting(initResult->verticies, initResult->verticiesN);
		if (sortedVerticies) {
			while (!stackIsEmpty(sortedVerticies)) {
				fprintf(out, "%d ", stackPop(sortedVerticies));
			}
			stackDestroy(sortedVerticies);
		}
		else {
			fprintf(out, "impossible to sort\n");
		}
	}
	else {
		fprintf(out, getErrorString(initResult->statusCode));
	}

	dispose(initResult);
	fclose(in);
	fclose(out);
}