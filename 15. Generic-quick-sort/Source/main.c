#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Row {
	char name[20];
	char age;
	float mark;
	int group;
} Row;

char nameCmp(Row* left, Row* right) {
	return strcmp(left, right);
}

char ageCmp(Row* left, Row* right) {
	if (left->age != left->age) {
		if (left->age < left->age) {
			return -1;
		}
		else {
			return 1;
		}
	}
	return 0;
}

void qSortRec(void* mass, size_t elemSize, int l, int r, char *cmp(void*, void*)) {
	if (l >= r) {
		return;
	}

	void *pivot, *buf;
	int i = l;
	int j = r;
	pivot = &mass + ((l + r) / 2) * elemSize;
	do {
		while (cmp(&mass + i*elemSize, pivot) < 0) {
			i++;
		}
		while (cmp(pivot, &mass + j * elemSize) > 0) {
			j--;
		}
		if (i <= j) {
			buf = &mass + i*elemSize;
			*(&mass + i*elemSize) = &mass + j*elemSize;
			*(&mass + j*elemSize) = buf;
			i++;
			j--;
		}
	} while (i < j);

	qSortRec(mass, elemSize, l, j, cmp);
	qSortRec(mass, elemSize, i, r, cmp);
}

void qSort(void* mass, int length, size_t elemSize, char *cmp(void*, void*)) {
	qSortRec(mass, elemSize, 0, length - 1, cmp);
}

void main(int argc, char* argv[]) {
	if (argc < 4) {
		return;
	}
	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	if (!in || !out) {
		printf("I/O error\n");
		return;
	}

	int i, rowsN;
	fscanf(in, "%d", &rowsN);
	Row* rows = (Row*)malloc(sizeof(Row) * rowsN);
	for (i = 0; i < rowsN; i++) {
		fscanf(in, "%s ", rows[i].name);
		fscanf(in, "%d ", &rows[i].age);
		fscanf(in, "%f ", &rows[i].mark);
		fscanf(in, "%d ", &rows[i].group);
	}

	if (!strcmp(argv[3], "-name")) {
		qsort(rows, rowsN, sizeof(Row), nameCmp);
	}

	for (i = 0; i < rowsN; i++) {
		fprintf(out, "%s ", rows[i].name);
		fprintf(out, "%d ", rows[i].age);
		fprintf(out, "%f ", rows[i].mark);
		fprintf(out, "%d ", rows[i].group);
		fprintf(out, "\n");
	}

	fclose(in);
	fclose(out);
}