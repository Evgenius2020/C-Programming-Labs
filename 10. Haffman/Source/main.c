#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Encoding.h"
#include "Decoding.h"

char* makeFileName(char testName) {
	char* filename = (char*)calloc(5 + 5 + 1, sizeof(char));
	strcat(filename, "test/");
	filename[5] = testName;
	strcat(filename, ".txt");
	return filename;
}

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	char currTest = 'a';
	FILE* copy;
	while (1){
		copy = fopen(makeFileName(currTest), "r");
		if (!copy) {
			break;
		}
		currTest++;
	}
	copy = fopen(makeFileName(currTest), "w");
	short curr;
	while(1) {
		curr = fgetc(in);
		if (curr == -1) {
			break;
		}
		fputc(curr, copy);
	}
	fclose(copy);
	rewind(in);

	char buf[5];
	fgets(&buf, 5, in);
	char cmd = buf[0];
	if (cmd == 'd') {
		decode(in, out);
	}
	if (cmd == 'c') {
		encode(in, out);
	}

	fclose(in);
	fclose(out);
	return 0;
}