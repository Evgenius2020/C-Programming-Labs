#ifndef DATA_TYPES
#define DATA_TYPES

#define COLOR_WHITE 1
#define COLOR_GREY 2
#define COLOR_BLACK 3

typedef struct Edge {
	short to;
	struct Edge* next;
} Edge;

typedef struct Vertex {
	short number;
	char color;
	Edge* edges;
} Vertex;

#define INIT_SUCCESS 1
#define INIT_BAD_LINES_NUMBER 2
#define INIT_BAD_VERTEX 3
#define INIT_BAD_VERTEX_NUMBER 4
#define INIT_BAD_EDGES_NUMBER 5

#define maxVertices 1000
#define maxEdges(n) n*(n-1)/2

typedef struct InitializationResult {
	char statusCode;
	Vertex* verticies;
	int verticiesN;
}InitializationResult;

#endif