#include <stdio.h>
#include <stdlib.h>
#include "Stack.h";

void main() {
	Stack* stack = stackCreate();
	for (int i = 0; i < 10; i++) {
		printf("%d ", i);
		stackPush(stack, i);
	}

	while (!stackIsEmpty(stack)) {
		printf("%d ", stackPop(stack));
	}

	stackDestroy(stack);
}