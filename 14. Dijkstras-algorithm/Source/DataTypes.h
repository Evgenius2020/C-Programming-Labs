#ifndef DATA_TYPES
#define DATA_TYPES

#include "PriorityQueue.h"
#define INF ULONG_MAX
#define UNVIEWED 0
#define VIEWED 1

typedef struct Edge {
	short to;
	int length;
	struct Edge* next;
} Edge;

typedef struct Vertex {
	t_index index;
	short number;
	struct Vertex* parent;
	char viewed;
	long long distance;
	Edge* edges;
} Vertex;

typedef struct InitializationResult {
	char statusCode;
	Vertex* vertices;
	short verticesN;
	short start;
	short end;
}InitializationResult;

#endif