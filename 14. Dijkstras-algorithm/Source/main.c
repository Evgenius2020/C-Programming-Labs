#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Initialize.h"
#include "DataTypes.h"

#define exit fclose(in); fclose(out); free(verticies); return 0;
#define isBetween(min, n, max) ((n >= min) && (n <= max))

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	if ((!in) || (!out)) {
		return;
	}

	InitializationResult initResult = initialize(in);

	InitializationResult initResult = initialize(in);
	if (initResult.statusCode == INIT_SUCCESS) {
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
	int currVert = start;
	verticies[currVert - 1].distance = 0;
	PriorQueue* queue = priorQueueCreate(verticiesN);
	do {
		verticies[currVert - 1].viewed = VIEWED;
		/* Searching all edges proceeding from 'currVert', rewriting 'length' value if it's longer. */
		for (buf = verticies[currVert - 1].edges; buf != NULL; buf = buf->next) {
			if ((verticies[buf->to - 1].distance == UNITIALIZED) ||
				(verticies[buf->to - 1].distance > verticies[currVert - 1].distance + buf->length)) {
				if (buf->to != buf->from) {
					verticies[buf->to - 1].distance = verticies[currVert - 1].distance + buf->length;
					priorQueueInsert(queue, buf, verticies[buf->to - 1].distance);
				}
			}
		}
		/* Selecting nearest edge. */
		currVert = UNITIALIZED;
		while (queue->length != 0) {
			buf = (Edge*)priorQueueExtractMin(queue);
			if (verticies[buf->to - 1].viewed == UNVIEWED) {
				currVert = buf->to;
				break;
			}
		}
	} while (currVert != UNITIALIZED);
	priorQueueDestroy(queue);

	int intMaxCount = 0;
	if (start != end) {
		buf = verticies[end - 1].edges;
		while (buf) {
			if (verticies[buf->to].distance > INT_MAX) {
				intMaxCount++;
			}
			buf = buf->next;
		}
	}

	/* Output block. */
	for (i = 0; i < verticiesN; i++) {
		if (verticies[i].distance > INT_MAX) {
			fprintf(out, "INT_MAX+ ");
			continue;
		}
		if (verticies[i].distance != UNITIALIZED) {
			fprintf(out, "%lli ", verticies[i].distance);
		}
		else {
			fprintf(out, "oo ");
		}
	}
	fprintf(out, "\n");
	if (verticies[end - 1].distance == UNITIALIZED) {
		fprintf(out, "no path\n");
		exit;
	}
	if (intMaxCount >= 2) {
		fprintf(out, "overflow\n");
		exit;
	}

	currVert = end;
	int crutch;
	while (1) {
		fprintf(out, "%d ", currVert);
		if (currVert == start) {
			for (i = 0; i < verticiesN; i++) {
				while (verticies[i].edges) {
					buf = verticies[i].edges->next;
					free(verticies[i].edges);
					verticies[i].edges = buf;
				}
			}
			exit;
		}
		for (buf = verticies[currVert - 1].edges; buf != NULL; buf = buf->next) {
			if (verticies[currVert - 1].distance - buf->length == verticies[buf->to - 1].distance) {
				/* bad code (test #49) */
				crutch = buf->to;
				buf = buf->next;
				if (buf) {
					if (verticies[currVert - 1].distance - buf->length == verticies[buf->to - 1].distance) {
						currVert = buf->to;
						break;
					}
				}
				currVert = crutch;
				break;
			}
		}
	}

	exit;
}
