#include <stdlib.h>
#include "Heap.h"

Heap* heapCreate(unsigned int length) {
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->elements = calloc(length, sizeof(int));
	heap->length = 0;

	return heap;
}

void heapDestroy(Heap* heap) {
	free(heap);
}

void heapInsert(Heap* heap, int key) {
	heap->length++;
	unsigned int i = heap->length - 1;
	heap->elements[i] = key;
	int buf;
	while ((i > 0) &&
		(heap->elements[i / 2] > heap->elements[i])) {
		buf = heap->elements[i / 2];
		heap->elements[i / 2] = heap->elements[i];
		heap->elements[i] = buf;
		i /= 2;
	}
}

int heapExtractMin(Heap* heap) {
	if (!heap->length) {
		return 0;
	}

	int min = heap->elements[0];
	heap->length--;
	heap->elements[0] = heap->elements[heap->length];
	heap->elements[heap->length] = 0;

	/* Heapifying. */
	int buf;
	int i = 0;
	unsigned int smallest, left, right;
	while (1) {
		smallest = i;
		left = smallest * 2 + 1;
		right = smallest * 2 + 2;
		if ((left < heap->length) &&
			(heap->elements[left] < heap->elements[smallest])) {
			smallest = left;
		}
		if ((right < heap->length) &&
			(heap->elements[right] < heap->elements[smallest])) {
			smallest = right;
		}
		if (smallest != i) {
			buf = heap->elements[i];
			heap->elements[i] = heap->elements[smallest];
			heap->elements[smallest] = buf;
			i = smallest;
		}
		else {
			break;
		}
	}

	return min;
}