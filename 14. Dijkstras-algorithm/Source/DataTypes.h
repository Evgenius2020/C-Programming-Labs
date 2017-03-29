#ifndef DATA_TYPES
#define DATA_TYPES

#define UNVIEWED 0
#define VIEWED 1
#define UNITIALIZED -1

typedef struct Edge {
	short from;
	short to;
	int length;
	struct Edge* next;
} Edge;

typedef struct Vertex {
	char viewed;
	long long distance;
	Edge* edges;
} Vertex;

typedef struct InitializationResult {
	char statusCode;
	Vertex* vertices;
	short verticesN;
}InitializationResult;

#endif