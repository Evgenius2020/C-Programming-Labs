#ifndef DATA_TYPES
#define DATA_TYPES

#include "PriorityQueue.h"
#include <stdlib.h>
#define INF ULONG_MAX
#define VIEWED 1
#define UNVIEWED 0
#define NO_NEAREST -1

typedef struct Edge {
	short to;
	int length;
	struct Edge* next;
} Edge;

typedef struct Vertex {
	short nearest;
	char viewed;
	Edge* edges;
	short number;
	t_index queueIndex;
} Vertex;

typedef struct InitializationResult {
	char statusCode;
	short verticesN;
	Vertex* vertices;
} InitializationResult;

#endif