#include <stdio.h>
#include <stdlib.h>
#include "MaxHeap.h"

void heapsort(key* mass, int length) {
	heapBuild(mass, length);
	int i;
	for (i = length; i > 1; i--) {
		mass[0] += mass[i - 1];
		mass[i - 1] = mass[0] - mass[i - 1];
		mass[0] -= mass[i - 1];
		length--;
		heapHeapify(mass, length, 1);
	}
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	if ((!in) || (!out)) {
		return;
	}

	int length, i;
	key* mass;

	fscanf(in, "%d ", &length);
	mass = malloc(sizeof(key)* length);
	for (i = 0; i < length; i++) {
		fscanf(in, "%d ", &mass[i]);
	}

	heapsort(mass, length);

	for (i = 0; i < length; i++) {
		fprintf(out, "%d ", mass[i]);
	}

	fclose(in);
	fclose(out);
}