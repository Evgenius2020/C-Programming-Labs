#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define exit fclose(in); fclose(out); return 0;
#define isBetween(left, val, right) ((left <= val) && (val <= right))

char checkValidation(char* permut) {
	if (strlen(permut) == 0) {
		return 0;
	}
	char entries[10];
	char i;
	for (i = 0; i < 10; i++) {
		entries[i] = 0;
	}

	for (i = 0; i < strlen(permut); i++) {
		if (!isBetween('0', permut[i], '9')) { /* Wrong character */
			return 0;
		}
		if (entries[permut[i] - '0']++ != 0) { /* Number's repeat */
			return 0;
		}
	}

	return 1;
}

char* getNextPermut(char* permut) {
	char* nextPermut = (char*)malloc(sizeof(char) * 10);
	strcpy(nextPermut, permut);
	char tail = strlen(nextPermut) - 1;

	char i;
	char next;
	while (tail > 0) {
		if (nextPermut[tail - 1] < nextPermut[tail]) {
			next = -1;
			for (i = tail; i < strlen(nextPermut); i++) {
				if (((next == -1) || (nextPermut[i] < nextPermut[next])) &&
					(nextPermut[i] > nextPermut[tail - 1])) {
					next = i;
				}
			}
			nextPermut[tail - 1] += nextPermut[next];
			nextPermut[next] = nextPermut[tail - 1] - nextPermut[next];
			nextPermut[tail - 1] -= nextPermut[next];

			/* reversing tail */
			for (i = 0; i < (strlen(nextPermut) - tail) / 2; i++) {
				nextPermut[tail + i] += nextPermut[strlen(nextPermut) - i - 1];
				nextPermut[strlen(nextPermut) - i - 1] = nextPermut[tail + i] - nextPermut[strlen(nextPermut) - i - 1];
				nextPermut[tail + i] -= nextPermut[strlen(nextPermut) - i - 1];
			}
			return nextPermut;
		}

		tail--;
	}

	return nextPermut;
}

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	char* permut = (char*)malloc(sizeof(char) * 10);
	fscanf(in, "%s ", permut);

	if (!checkValidation(permut)) {
		fprintf(out, "bad input\n");
		exit;
	}

	int times;
	fscanf(in, "%d ", &times);

	int i;
	char* nextPermut;
	for (i = 0; i < times; i++) {
		nextPermut = getNextPermut(permut);
		if (strcmp(permut, nextPermut) == 0) {
			break;
		}
		free(permut);
		permut = nextPermut;
		fprintf(out, "%s\n", permut);
	}

	exit;
}