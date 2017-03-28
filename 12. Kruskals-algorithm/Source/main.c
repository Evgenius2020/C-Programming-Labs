#include <stdio.h>
#include <stdlib.h>
#include "Initialize.h"
#include "DataTypes.h"

Vertex* makeSet() {
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	vertex->leader = vertex;

	return vertex;
}

Vertex* findSet(Vertex* vertex) {
	Vertex* buf = vertex->leader;
	while (buf->leader != buf) {
		vertex->leader = buf->leader;
		buf = buf->leader;
	}

	return vertex->leader;
}

void unionSets(Vertex* of, Vertex* into) {
	findSet(of)->leader = findSet(into);
}

int compareEdges(Edge* left, Edge* right) {
	return left->length - right->length;
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	short i, spannedVerticies;

	if ((!in) || (!out)) {
		return;
	}

	InitializationResult result = initialize(in);
	if (result.statusCode == INIT_SUCCESS) {
		qsort(result.edges, result.edgesN, sizeof(Edge), compareEdges);
		spannedVerticies = makeSpanningTree(result);
		if (spannedVerticies == result.verticiesN) {
			for (i = 0; i < result.verticiesN; i++) {
				fprintf(out, "%d %d\n", result.edges[i].from, result.edges[i].to);
			}
		}
		else {
			fprintf(out, "no spanning tree\n");
		}

		free(result.edges);
		free(result.verticies);
	}
	else {
		/* erorrs */
		if (result.statusCode == INIT_BAD_EDGES_NUMBER) {
			fprintf(out, "bad number of edges\n");
		}
		if (result.statusCode == INIT_BAD_LENGTH) {
			fprintf(out, "bad length\n");
		}
		if (result.statusCode == INIT_BAD_LINES_NUMBER) { 
			fprintf(out, "bad number of lines\n");
		}
		if (result.statusCode == INIT_BAD_VERTEX) {
			fprintf(out, "bad vertex\n");
		}
		if (result.statusCode == INIT_BAD_VERTICIES_NUMBER) {
			fprintf(out, "bad number of vertex\n");
		}
	}

	fclose(in);
	fclose(out);

	///* Making a spanning tree.*/
	//while (queue->length) {
	//	buf = (Edge*)priorQueueExtractMin(queue);
	//	if (findSet(&vertices[buf->from - 1]) != (findSet(&vertices[buf->to - 1]))) {
	//		unionSets(findSet(&vertices[buf->from - 1]), findSet(&vertices[buf->to - 1]));
	//	}
	//	free(buf);
	//}
}