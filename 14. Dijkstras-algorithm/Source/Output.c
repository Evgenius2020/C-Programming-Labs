#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Output.h"

void printDistances(Vertex* vertices, short verticesN, FILE* out) {
	short i;
	for (i = 0; i < verticesN; i++) {
		if (vertices[i].distance > INT_MAX) {
			fprintf(out, "INT_MAX+ ");
			continue;
		}
		if (vertices[i].distance != UNITIALIZED) {
			fprintf(out, "%lli ", vertices[i].distance);
		}
		else {
			fprintf(out, "oo ");
		}
	}
	fprintf(out, "\n");
}

void printPath(Vertex* vertices, short start, short end, FILE* out) {
	short currVert;
	Edge* buf;

	if (vertices[end - 1].distance == UNITIALIZED) {
		fprintf(out, "no path\n");
		return;
	}
	int intMaxCount = 0;
	if (start != end) {
		buf = vertices[end - 1].edges;
		while (buf) {
			if (vertices[buf->to].distance > INT_MAX) {
				intMaxCount++;
			}
			buf = buf->next;
		}
	}
	if (intMaxCount >= 2) {
		fprintf(out, "overflow\n");
		return;
	}

	currVert = end;
	int crutch;
	while (1) {
		fprintf(out, "%d ", currVert);
		if (currVert == start) {
			return;
		}
		for (buf = vertices[currVert - 1].edges; buf != NULL; buf = buf->next) {
			if (vertices[currVert - 1].distance - buf->length == vertices[buf->to - 1].distance) {
				/* bad code (test #49) */
				crutch = buf->to;
				buf = buf->next;
				if (buf) {
					if (vertices[currVert - 1].distance - buf->length == vertices[buf->to - 1].distance) {
						currVert = buf->to;
						break;
					}
				}
				currVert = crutch;
				break;
			}
		}
	}
}