#include <stdlib.h>
#include "Stack.h"

Stack* stackCreate() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = NULL;

	return stack;
}

void stackDestroy(Stack* stack) {
	while (!stackIsEmpty(stack)) {
		stackPop(stack);
	}

	free(stack);
}

void stackPush(Stack* stack, int data) {
	StackElement* element = (StackElement*)malloc(sizeof(StackElement));
	if (!element) {
		return;
	}
	element->data = data;

	if (stackIsEmpty(stack)) {
		stack->top = element;
		element->next = NULL;
	}
	else {
		element->next = stack->top;
		stack->top = element;
	}
}

int stackPop(Stack* stack) {
	if (stackIsEmpty(stack)) {
		return 0;
	}

	StackElement* element = stack->top;
	stack->top = element->next;
	int data = element->data;
	free(element);

	return data;
}

int stackPeek(Stack* stack) {
	if (stackIsEmpty(stack)) {
		return 0;
	}

	return stack->top->data;
}

char stackIsEmpty(Stack* stack) {
	if (stack->top == NULL) {
		return 1;
	}

	return 0;
}
