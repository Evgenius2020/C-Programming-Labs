#include <stdlib.h>
#include "qSort.h"

static void* buf;
static void* pivot;

void qSortRec(void* base, size_t size, int l, int r, int(*cmp)(const void*, const void*)) {
	if (l >= r) {
		return;
	}

	int i = l;
	int j = r;
	memcpy(pivot, (char*)base + ((l + r) / 2) * size, size);
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