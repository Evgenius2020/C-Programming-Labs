#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8

typedef struct Vector {
	unsigned char values[BOARD_SIZE];
	unsigned char length;
}Vector;

char checkVector(unsigned char newPos, Vector* vector) {
	unsigned char i;
	for (i = 0; i < vector->length; i++) {
		if (newPos == vector->values[i]) {
			return 0;
		}
		if (vector->values[i] == newPos + vector->length - i) {
			return 0;
		}
		if (vector->values[i] == newPos - vector->length + i) {
			return 0;
		}
	}

	return 1;
}

void printBoard(Vector* vector) {
	unsigned char i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (vector->values[i] == j) {
				printf("1 ");
			}
			else {
				printf("0 ");
			}
		}
		printf("\n");
	}
	printf("==========\n");
}

void solQueen(Vector* vector) {
	if (vector->length == BOARD_SIZE) {
		printBoard(vector);
	}

	unsigned char newPos;
	for (newPos = 0; newPos < BOARD_SIZE; newPos++) {
		if (checkVector(newPos, vector)) {
			vector->values[vector->length++] = newPos;
			solQueen(vector);
			vector->length--;
		}
	}
}

void main() {
	Vector* vector = malloc(sizeof(Vector));
	vector->length = 0;

	solQueen(vector);
}