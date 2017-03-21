#include <stdio.h>
#include <stdlib.h>
#include "Stack.h";

void main() {
	int* mass = (int*)malloc(sizeof(int) * 10);
	Stack* stack = stackCreate();
	for (int i = 0; i < 10; i++) {
		mass[i] = i + 1;
		printf("%d ", mass[i]);
		stackPush(stack, &mass[i]);
	}

	printf("\n%d\n", *((int*)stackPeek(stack)));

	while (!stackIsEmpty(stack)) {
		printf("%d ", *((int*)stackPop(stack)));
	}

	stackDestroy(stack);
	free(mass);
}