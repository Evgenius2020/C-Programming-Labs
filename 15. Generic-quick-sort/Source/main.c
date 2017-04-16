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
	return strcmp(left->name, right->name);
}

static void* buf;
static void* pivot;

#define NUMCMP(left, right, fieldname) return (left->##fieldname == right->##fieldname) ? 0 : ((left->##fieldname < right->##fieldname) ? -1 : 1)

char ageCmp(Row* left, Row* right) {
	NUMCMP(left, right, age);
}
char markCmp(Row* left, Row* right) {
	NUMCMP(left, right, mark);
}
char groupCmp(Row* left, Row* right) {
	NUMCMP(left, right, group);
}

void qSortRec(void* mass, size_t elemSize, int l, int r, char *cmp(void*, void*)) {
	if (l >= r) {
		return;
	}

	int i = l;
	int j = r;
	memcpy(pivot, (char*)mass + ((l + r) / 2) * elemSize , elemSize);
	do {
		while (strcmp((char*)mass + i*elemSize, pivot) < 0) {
			i++;
		}
		while (strcmp(pivot, (char*)mass + j*elemSize) < 0) {
			j--;
		}
		if (i <= j) {
			memcpy(buf, (char*)mass + i*elemSize, elemSize);
			memcpy(((char*)mass + i*elemSize), ((char*)mass + j*elemSize), elemSize);
			memcpy(((char*)mass + j*elemSize), buf, elemSize);
			i++;
			j--;
		}
	} while (i < j);

	qSortRec(mass, elemSize, l, j, cmp);
	qSortRec(mass, elemSize, i, r, cmp);
}

void qSort(void* mass, int length, size_t elemSize, char *cmp(void*, void*)) {
	buf = malloc(elemSize);
	pivot = malloc(elemSize);
	qSortRec(mass, elemSize, 0, length - 1, cmp);
	free(pivot);
	free(buf);
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
		qSort(rows, rowsN, sizeof(Row), nameCmp);
	}
	if (!strcmp(argv[3], "-age")) {
		qSort(rows, rowsN, sizeof(Row), ageCmp);
	}
	if (!strcmp(argv[3], "-mark")) {
		qSort(rows, rowsN, sizeof(Row), markCmp);
	}
	if (!strcmp(argv[3], "-group")) {
		qSort(rows, rowsN, sizeof(Row), groupCmp);
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