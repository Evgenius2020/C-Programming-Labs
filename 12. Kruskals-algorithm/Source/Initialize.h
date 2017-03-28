#include <stdio.h>
#include "DataTypes.h"

#define INIT_SUCCESS 1
#define INIT_BAD_VERTICES_NUMBER 2
#define INIT_BAD_EDGES_NUMBER 3
#define INIT_BAD_LINES_NUMBER 4
#define INIT_BAD_VERTEX 5
#define INIT_BAD_LENGTH 6

InitializationResult initialize(FILE* in);