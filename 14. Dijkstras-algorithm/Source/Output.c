#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Output.h"

void printDistances(Vertex* vertices, short verticesN, FILE* out) {
	short i;
	for (i = 0; i < verticesN; i++) {
		if (vertices[i].distance == INF) {
			fprintf(out, "oo ");
			continue;
		}
		if (vertices[i].distance > INT_MAX) {
			fprintf(out, "INT_MAX+ ");
			continue;
		}
		fprintf(out, "%lli ", vertices[i].distance);
	}
	fprintf(out, "\n");
}

void printPath(Vertex* vertices, short start, short end, FILE* out) {
	Vertex* currVert;
	Edge* buf;

	if (vertices[end - 1].distance == INF) {
		fprintf(out, "no path\n");
		return;
	}
	int intMaxCount = 0;
	if (start != end) {
		for (buf = vertices[end - 1].edges; buf; buf = buf->next) {
			if (vertices[buf->to - 1].distance + buf->length > INT_MAX) {
				intMaxCount++;
			}
		}
	}
	if (intMaxCount >= 2) {
		fprintf(out, "overflow\n");
		return;
	}

	currVert = &vertices[end - 1];
	fprintf(out, "%hi ", currVert->number);

	do {
		currVert = currVert->parent;
		fprintf(out, "%hi ", currVert->number);
	} while (currVert != currVert->parent);
}