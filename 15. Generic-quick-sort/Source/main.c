#include <stdio.h>
#include "Row.h"
#include "Comparings.h"

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