#include <stdio.h>
#include "DataTypes.h"
#include "MakeSpannigTree.h"

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

short makeSpanningTree(InitializationResult initResult, FILE* out) {
	short result = 1;
	int i;
	Edge currEdge;

	for (i = 0; i < initResult.edgesN; i++) {
		currEdge = initResult.edges[i];
		/* vertices are in different sets */
		if (findSet(&initResult.vertices[currEdge.from - 1]) != (findSet(&initResult.vertices[currEdge.to - 1]))) {
			unionSets(&initResult.vertices[currEdge.from - 1], findSet(&initResult.vertices[currEdge.to - 1]));
			fprintf(out, "%d %d\n", currEdge.from, currEdge.to);
			result++;
		}
	}
	
	return result;
}