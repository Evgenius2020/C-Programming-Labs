#include "MaxHeap.h"

void heapHeapify(key* mass, int length, int i) {
	int left = 2 * i;
	int right = 2 * i + 1;
	key largest = i;
	if ((left <= length) && (mass[left - 1] > mass[largest - 1])) {
		largest = left;
	}
	if ((right <= length) && (mass[right - 1] > mass[largest - 1])) {
		largest = right;
	}
	if (largest != i) {
		mass[i - 1] += mass[largest - 1];
		mass[largest - 1] = mass[i - 1] - mass[largest - 1];
		mass[i - 1] -= mass[largest - 1];
		heapHeapify(mass, length, largest);
	}
}

void heapBuild(key* mass, int length) {
	int i;
	for (i = length / 2; i > 0; i--) {
		heapHeapify(mass, length, i);
	}
}

void heapChangeKey(key* mass, int i, key val) {
	if (val < mass[i]) {
		return;
	}
	mass[i] = val;
	while ((i > 0) && (mass[i / 2] < mass[i])) {
		mass[i / 2] += mass[i];
		mass[i] = mass[i / 2] - mass[i];
		mass[i / 2] -= mass[i];
		i /= 2;
	}
}