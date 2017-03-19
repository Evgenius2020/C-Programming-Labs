#include <stdio.h>
#include <stdlib.h>

void quickSort(int* mass, int left, int right) {
	if (left >= right) {
		return;
	}
	int pivot = right;
	int i = left, j = right - 1;
	while (i != j) {
		if (mass[i] < mass[pivot]) {
			i++;
			continue;
		}
		if (mass[j] > mass[pivot]) {
			j--;
			continue;
		}
		mass[i] += mass[j];
		mass[j] = mass[i] - mass[j];
		mass[i] -= mass[j];
	}

	if (mass[pivot] < mass[j]) {
		mass[pivot] += mass[j];
		mass[j] = mass[pivot] - mass[j];
		mass[pivot] -= mass[j];
	}

	quickSort(mass, 0, i);
	quickSort(mass, j + 1, right);
}

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	int size;
	fscanf(in, "%d ", &size);

	int i;
	int* mass = (int*)malloc(sizeof(int)*size);
	for (i = 0; i < size; i++) {
		fscanf(in, "%d ", &mass[i]);
	}

	quickSort(mass, 0, size - 1);

	for (i = 0; i < size; i++) {
		fprintf(out, "%d ", mass[i]);
	}

	fclose(in);
	fclose(out);
	return 0;
}