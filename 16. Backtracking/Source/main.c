#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
	unsigned char* values;
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

void printBoard(Vector* vector, FILE* out, unsigned char boardSize) {
	unsigned char i, j;
	for (i = 0; i < boardSize; i++) {
		for (j = 0; j < boardSize; j++) {
			if (vector->values[i] == j) {
				fprintf(out, "1 ");
			}
			else {
				fprintf(out, "0 ");
			}
		}
		fprintf(out, "\n");
	}
	fprintf(out, "==========\n");
}

void solQueen(Vector* vector, FILE* out, unsigned char boardSize) {
	if (vector->length == boardSize) {
		printBoard(vector, out, boardSize);
	}

	unsigned char newPos;
	for (newPos = 0; newPos < boardSize; newPos++) {
		if (checkVector(newPos, vector)) {
			vector->values[vector->length++] = newPos;
			solQueen(vector, out, boardSize);
			vector->length--;
		}
	}
}

void main(int argc, char* argv[]) {
	if (argc < 3) {
		return;
	}
	Vector* vector = malloc(sizeof(Vector));
	unsigned char boardSize = atoi(argv[1]);
	vector->values = malloc(sizeof(char) * boardSize);
	vector->length = 0;
	FILE* out = fopen(argv[2], "w");
	if (!out) {
		printf("bad filename\n");
		return;
	}

	solQueen(vector, out, boardSize);
	fclose(out);
	free(vector);
}