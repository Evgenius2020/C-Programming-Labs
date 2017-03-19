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

	char max = 0;
	for (i = 0; i < strlen(permut); i++) {
		if (!isBetween('0', permut[i], '9')) { /* Wrong character */
			return 0;
		}
		if (entries[permut[i] - '0']++ != 0) { /* Number's repeat */
			return 0;
		}
		if (permut[i] - '0' > max) {
			max = permut[i] - '0';
		}
	}

	if (strlen(entries) != max + 1) { /* '104' (missed 2, 3) - like cases */
		return 0;
	}

	return 1;
}

char* getNextPermut(char* permut) {

}

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	char* permut = (char*)malloc(sizeof(char), 15);
	fscanf(in, "%s ", permut);

	if (!checkValidation(permut)) {
		fprintf(out, "bad input\n");
		exit;
	}

	int times;
	fscanf(in, "%d ", times);

	int i;
	char* nextPermut;
	for (i = 0; i < times; i++) {
		nextPermut = getNextPermut(permut);
		if (strcmp(permut, nextPermut) == 0) {
			break;
		}
		permut = nextPermut;
		fprintf(out, "%s\n", permut);
	}

	exit;
}