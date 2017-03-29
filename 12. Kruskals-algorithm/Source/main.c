#include <stdio.h>
#include <stdlib.h>
#include "Initialize.h"
#include "MakeSpannigTree.h"
#include "DataTypes.h"

int compareEdges(Edge* left, Edge* right) {
	return left->length - right->length;
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	short i, spannedvertices;

	if ((!in) || (!out)) {
		return;
	}

	InitializationResult initResult = initialize(in);
	if (initResult.statusCode == INIT_SUCCESS) {
		qsort(initResult.edges, initResult.edgesN, sizeof(Edge), compareEdges);
		spannedvertices = makeSpanningTree(initResult, out);
		if (spannedvertices != initResult.verticesN) {
			rewind(out);
			fprintf(out, "no spanning tree\n");
		}

		free(initResult.edges);
		free(initResult.vertices);
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