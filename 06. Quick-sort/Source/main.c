#include <stdio.h>
#include <stdlib.h>

void quickSort(int* mass, int l, int r) {
	if (l >= r) {
		return;
	}

	int pivot, buf;
	int i = l;
	int j = r;
	pivot = mass[(l + r) / 2];
	do {
		while (mass[i] < pivot) {
			i++;
		}
		while (pivot < mass[j]) {
			j--;
		}
		if (i <= j) {
			buf = mass[i];
			mass[i] = mass[j];
			mass[j] = buf;
			i++;
			j--;
		}
	} while (i < j);

	quickSort(mass, l, j);
	quickSort(mass, i, r);
}

void main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	if ((!in) || (!out)) {
		return;
	}

	int size, i;
	int* mass;

	fscanf(in, "%d ", &size);
	mass = (int*)malloc(sizeof(int)*size);
	for (i = 0; i < size; i++) {
		fscanf(in, "%d ", &mass[i]);
	}

	quickSort(mass, 0, size - 1);

	for (i = 0; i < size; i++) {
		fprintf(out, "%d ", mass[i]);
	}

	fclose(in);
	fclose(out);
}