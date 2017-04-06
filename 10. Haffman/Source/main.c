#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Encoding.h"
#include "Decoding.h"

char* makeFileName(int testNumber) {
	char buff[8];
	char* filename = (char*)calloc(25, sizeof(char));
	strcat(filename, "test/");
	strcat(filename, itoa(testNumber, buff, 10));
	strcat(filename, ".txt");
	return filename;
}

void main() {
	FILE* in = fopen("in.txt", "rb");
	FILE* out = fopen("out.txt", "wb");

	/*int currTest = 1;
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
	rewind(in);*/

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
}