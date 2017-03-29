#include <stdio.h>
#include "DataTypes.h"

/* Prints to the 'out' file row of a calculated distances by 'start' vertex. */
void printDistances(Vertex* vertices, short verticesN, FILE * out);

/* Prints all vertices of the shortest path from end to start. */
void printPath(Vertex * vertices, short start, short end, FILE * out);