#include <stdlib.h>
#include "DataTypes.h"
#include "Stack.h"

/* Returns stack with ordered verticies if topological sorting is it possible or NULL if its not. */
Stack* topologicalSorting(Vertex* verticies, int verticiesN) {
	Stack* grey = stackCreate();
	Stack* black = stackCreate();
	short currVert, i;
	Edge* buf;

	for (i = 0; i < verticiesN; i++) {
		verticies[i].color = COLOR_WHITE;
	}

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