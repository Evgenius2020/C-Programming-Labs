#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define maxVertices 1000
#define maxEdges(n) n*(n-1)/2

#define COLOR_WHITE 1
#define COLOR_GREY 2
#define COLOR_BLACK 3

#define INIT_SUCCESS 1
#define INIT_BAD_LINES_NUMBER 2
#define INIT_BAD_VERTEX 3
#define INIT_BAD_VERTEX_NUMBER 4
#define INIT_BAD_EDGES_NUMBER 5

typedef struct Edge {
	short to;
	struct Edge* next;
} Edge;

typedef struct Vertex {
	short number;
	char color;
	Edge* edges;
} Vertex;

typedef struct InitializationResult {
	char statusCode;
	Vertex* verticies;
	int verticiesN;
}InitializationResult;

void destroyVerticies(Vertex* verticies, int vertriciesN) {
	if (!verticies) {
		return;
	}

	int i;
	Edge* buf;
	for (i = 0; i < vertriciesN; i++) {
		while (verticies[i].edges) {
			buf = verticies[i].edges->next;
			free(verticies[i].edges);
			verticies[i].edges = buf;
		}
	}
	free(verticies);
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

/* Parses input data, checks validation. Return verticies array and number of it with SUCCESS status code 
	or with another status code in case of parsing failure. */
InitializationResult initializeVerticies(FILE* in) {
	InitializationResult result;
	result.verticies = NULL;
	result.verticiesN = 0;

	int verticiesN, edgesN;
	short i, from;
	Vertex* verticies;
	Edge* buf;

	if (-1 == fscanf(in, "%d ", &verticiesN)) {
		result.statusCode = INIT_BAD_LINES_NUMBER;
		return result;
	}
	if ((verticiesN < 0) || (verticiesN > maxVertices)) {
		result.statusCode = INIT_BAD_VERTEX_NUMBER;
		return result;
	}
	verticies = (Vertex*)malloc(sizeof(Vertex)* verticiesN);
	for (i = 0; i < verticiesN; i++) {
		verticies[i].color = COLOR_WHITE;
		verticies[i].edges = NULL;
		verticies[i].number = i + 1;
	}

	if (-1 == fscanf(in, "%d ", &edgesN)) {
		result.statusCode = INIT_BAD_LINES_NUMBER;
		return result;
	}
	if ((edgesN < 0) || (edgesN > maxEdges(verticiesN))) {
		result.statusCode = INIT_BAD_EDGES_NUMBER;
		return result;
	}
	for (i = 0; i < edgesN; i++) {
		buf = (Edge*)malloc(sizeof(Edge));
		if (EOF == fscanf(in, "%d %d ", &from, &buf->to)) {
			result.statusCode = INIT_BAD_LINES_NUMBER;
			return result;
		}
		if (((from < 0) || (from > verticiesN)) ||
			((buf->to < 0) || (buf->to > verticiesN))) {
			result.statusCode = INIT_BAD_VERTEX;
			return result;
		}

		buf->next = verticies[from - 1].edges;
		verticies[from - 1].edges = buf;
	}

	result.verticies = verticies;
	result.verticiesN = verticiesN;
	result.statusCode = INIT_SUCCESS;

	return result;
}

/* Returns stack with ordered verticies if topological sorting is it possible or NULL if its not. */
Stack* topologicalSorting(Vertex* verticies, int verticiesN) {
	Stack* grey = stackCreate();
	Stack* black = stackCreate();
	short currVert, i;
	Edge* buf;

	for (i = 0; i < verticiesN; i++) {
		if (verticies[i].color == COLOR_WHITE) {
			stackPush(grey, i + 1);
			while (!stackIsEmpty(grey)) {
				currVert = stackPeek(grey);
				if (verticies[currVert - 1].color == COLOR_BLACK) {
					stackPop(grey);
					continue;
				}
				verticies[currVert - 1].color = COLOR_GREY;
				for (buf = verticies[currVert - 1].edges; buf; buf = buf->next) {
					if (verticies[buf->to - 1].color == COLOR_GREY) {
						stackDestroy(grey);
						stackDestroy(black);
						return NULL;
					}
					if (verticies[buf->to - 1].color == COLOR_WHITE) {
						stackPush(grey, buf->to);
					}
				}
				if (currVert == stackPeek(grey)) {
					verticies[currVert - 1].color = COLOR_BLACK;
					stackPush(black, currVert);
				}
			}
		}
	}

	stackDestroy(grey);
	return black;
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	if ((!in) || (!out)) {
		return;
	}

	InitializationResult result = initializeVerticies(in);

	if (result.statusCode == INIT_SUCCESS) {
		Stack* sortedVerticies = topologicalSorting(result.verticies, result.verticiesN);
		if (sortedVerticies) {
			while (!stackIsEmpty(sortedVerticies)) {
				fprintf(out, "%d ", stackPop(sortedVerticies));
			}
			stackDestroy(sortedVerticies);
		}
		else {
			fprintf(out, "impossible to sort\n");
		}
		destroyVerticies(result.verticies, result.verticiesN);
	}
	else {
		fprintf(out, getErrorString(result.statusCode));
	}

	fclose(in);
	fclose(out);
}