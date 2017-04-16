#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Row {
	char name[20];
	char age;
	float mark;
	int groupId;
} Row;

int nameCmp(Row* left, Row* right) {
	return strcmp(left->name, right->name);
}

static void* buf;
static void* pivot;

#define NUMCMP(left, right, fieldname) return (left->##fieldname == right->##fieldname) ? 0 : ((left->##fieldname < right->##fieldname) ? -1 : 1)

int ageCmp(Row* left, Row* right) {
	NUMCMP(left, right, age);
}
int markCmp(Row* left, Row* right) {
	NUMCMP(left, right, mark);
}
int groupCmp(Row* left, Row* right) {
	NUMCMP(left, right, groupId);
}

void qSortRec(void* base, size_t size, int l, int r, int (*cmp)(const void*, const void*)) {
	if (l >= r) {
		return;
	}

	int i = l;
	int j = r;
	memcpy(pivot, (char*)base + ((l + r) / 2) * size , size);
	do {
		while (cmp((char*)base + i*size, pivot) < 0) {
			i++;
		}
		while (cmp(pivot, (char*)base + j*size) < 0) {
			j--;
		}
		if (i <= j) {
			memcpy(buf, (char*)base + i*size, size);
			memcpy(((char*)base + i*size), ((char*)base + j*size), size);
			memcpy(((char*)base + j*size), buf, size);
			i++;
			j--;
		}
	} while (i < j);

	qSortRec(base, size, l, j, cmp);
	qSortRec(base, size, i, r, cmp);
}

void qSort(void* base, size_t num, size_t size, int(*cmp)(const void*, const void*)) {
	buf = malloc(size);
	pivot = malloc(size);
	qSortRec(base, size, 0, num - 1, cmp);
	free(pivot);
	free(buf);
}

void main(int argc, char* argv[]) {
	if (argc < 4) {
		return;
	}
	FILE* in = fopen(argv[2], "r");
	FILE* out = fopen(argv[3], "w");
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
		fscanf(in, "%d ", &rows[i].groupId);
	}

	if (!strcmp(argv[1], "-n")) {
		qSort(rows, rowsN, sizeof(Row), nameCmp);
	}
	if (!strcmp(argv[1], "-a")) {
		qSort(rows, rowsN, sizeof(Row), ageCmp);
	}
	if (!strcmp(argv[1], "-m")) {
		qSort(rows, rowsN, sizeof(Row), markCmp);
	}
	if (!strcmp(argv[1], "-g")) {
		qSort(rows, rowsN, sizeof(Row), groupCmp);
	}

	for (i = 0; i < rowsN; i++) {
		fprintf(out, "%s ", rows[i].name);
		fprintf(out, "%d ", rows[i].age);
		fprintf(out, "%f ", rows[i].mark);
		fprintf(out, "%d ", rows[i].groupId);
		fprintf(out, "\n");
	}

	fclose(in);
	fclose(out);
}