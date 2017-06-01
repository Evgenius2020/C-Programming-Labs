#include <stdlib.h>
#include "DataTypes.h"
#include "Stack.h"

/* Returns stack with ordered verticies if topological sorting is it possible or NULL if it's not. */
Stack* topologicalSorting(Vertex* vertices, int verticiesN) {
	Stack* grey = stackCreate();
	Stack* black = stackCreate();
	short currVert;
	Edge* buf;

	for (currVert = 1; currVert <= verticiesN; currVert++) {
		vertices[currVert - 1].color = COLOR_WHITE;
		stackPush(grey, currVert);
	}
	while (!stackIsEmpty(grey)) {
		currVert = stackPeek(grey);
		if (vertices[currVert - 1].color == COLOR_WHITE) {
			vertices[currVert - 1].color = COLOR_GREY;
			for (buf = vertices[currVert - 1].edges; buf; buf = buf->next) {
				if (vertices[buf->to - 1].color == COLOR_GREY) {
					stackDestroy(grey);
					stackDestroy(black);
					return NULL;
				}
				if (vertices[buf->to - 1].color == COLOR_WHITE) {
					stackPush(grey, buf->to);
				}
			}
		}
		if (currVert == stackPeek(grey)) {
			stackPop(grey);
			if (vertices[currVert - 1].color != COLOR_BLACK) {
				vertices[currVert - 1].color = COLOR_BLACK;
				stackPush(black, currVert);

			}
		}
	}

	stackDestroy(grey);
	return black;
}