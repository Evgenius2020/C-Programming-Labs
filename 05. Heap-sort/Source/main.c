#include <stdio.h>
#include "Heap.h"

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	int length;
	fscanf(in, "%d ", &length);
	Heap* heap = heapCreate(length);
	int newNumber;
	while (length) {
		fscanf(in, "%d ", &newNumber);
		heapInsert(heap, newNumber);
		length--;
	}

	while (heap->length) {
		fprintf(out, "%d ", heapExtractMin(heap));
	}

	heapDestroy(heap);
	fclose(in);
	fclose(out);
	return 0;
}